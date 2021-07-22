#include "shape.h"
#include "utils.h"
#include "extra_utils.h"
#include "allocators.h"

namespace box2dDefoldNE {

b2Vec2* parse_vertices(lua_State *L, const char* key,const char* error,int* b2vecSize){
    lua_getfield(L, -1, key);
    b2Vec2* vertices = NULL;
    if(lua_istable(L,-1)){
        vertices = extra_utils::parse_vertices(L,-1,b2vecSize);
    }else{
        utils::error(L,error);
    }
    lua_pop(L,1);
    return vertices;
}


b2CircleShape* b2CircleShape_from_table(lua_State *L){
    b2CircleShape* shape = b2CircleShape_new();
    shape->m_radius = utils::table_get_double_safe(L,"circle_radius","no circle_radius");
    if(utils::table_is_not_nil(L,"circle_position")){
        b2Vec2 position = extra_utils::table_get_b2vec_safe(L,"circle_position","circle_position not vector3");
        shape->m_p.Set(position.x, position.y);
    }
    return shape;
}

b2EdgeShape* b2EdgeShape_from_table(lua_State *L){
    b2EdgeShape* shape = b2EdgeShape_new();
    b2Vec2 v1 = extra_utils::table_get_b2vec_safe(L,"edge_v1","edge_v1 not vector3");
    b2Vec2 v2 = extra_utils::table_get_b2vec_safe(L,"edge_v2","edge_v2 not vector3");
    if(utils::table_get_boolean(L,"edge_two_sided",false)){
        shape->SetTwoSided(v1,v2);
    }else{
        b2Vec2 v0 = extra_utils::table_get_b2vec_safe(L,"edge_v0","edge_v0 not vector3");
        b2Vec2 v3 = extra_utils::table_get_b2vec_safe(L,"edge_v3","edge_v3 not vector3");
        shape->SetOneSided(v0,v1,v2,v3);

    }
    return shape;
}

b2PolygonShape* b2PolygonShape_from_table(lua_State *L){
    b2PolygonShape* shape = b2PolygonShape_new();
    if(utils::table_get_boolean(L,"box",false)){
        double box_hx = utils::table_get_double_safe(L,"box_hx","no box_hx");
        double box_hy = utils::table_get_double_safe(L,"box_hy","no box_hy");
        bool box_angle_exist = utils::table_is_not_nil(L,"box_angle");
        bool box_center_exist = utils::table_is_not_nil(L,"box_center");
        if(box_angle_exist && box_center_exist){
            double box_angle = utils::table_get_double_safe(L,"box_angle","no box_angle");
            b2Vec2 box_center = extra_utils::table_get_b2vec_safe(L,"box_center","box_center not vector3");
            shape->SetAsBox(box_hx,box_hy,box_center,box_angle);
        }else if(box_angle_exist != box_center_exist){
            if(box_angle_exist){
                utils::error(L,"box_angle exist but box_center not exist");
            }else{
                utils::error(L,"box_center exist but box_angle not exist");
            }
        }else{
            shape->SetAsBox(box_hx,box_hy);
        }
    }else{
        int verticesSize = 0;
        b2Vec2* vertices = parse_vertices(L,"polygon_vertices","no polygon_vertices",&verticesSize);
        shape->Set(vertices,verticesSize);
        delete[] vertices;
    }
    return shape;
}

b2ChainShape* b2ChainShape_from_table(lua_State *L){
    b2ChainShape* shape = b2ChainShape_new();
    int verticesSize = 0;
    b2Vec2* vertices = parse_vertices(L,"chain_vertices","no chain_vertices",&verticesSize);
    if(utils::table_get_boolean(L,"chain_loop",false)){
        shape->CreateLoop(vertices,verticesSize);
    }else{
        b2Vec2 vPrev = extra_utils::table_get_b2vec_safe(L,"chain_prev_vertex","chain_prev_vertex not vector3");
        b2Vec2 vNext = extra_utils::table_get_b2vec_safe(L,"chain_next_vertex","chain_next_vertex not vector3");
        shape->CreateChain(vertices,verticesSize,vPrev,vNext);
    }
    delete[] vertices;
    return shape;
}

//free b2Shape after use
b2Shape* b2Shape_from_lua(lua_State *L, int index){
    if (lua_istable(L, index)) {
        lua_pushvalue(L,index);
        b2Shape* result = NULL;

        b2Shape::Type shapeType = static_cast<b2Shape::Type>(utils::table_get_integer_safe(L,"shape","no shape"));
        switch(shapeType){
            case b2Shape::e_circle:{
                result = b2CircleShape_from_table(L);
                break;
            }
            case b2Shape::e_polygon:{
                result = b2PolygonShape_from_table(L);
                break;
            }
            case b2Shape::e_edge:{
                result = b2EdgeShape_from_table(L);
                break;
            }
            case b2Shape::e_chain:{
                result = b2ChainShape_from_table(L);
                break;
            }
        }
        lua_pop(L,1);
        return result;
    }else if(lua_isuserdata(L, index)){
        if(utils::test_userdata(L, index, "Box2d::CircleShapeClass")){
            CircleShape* shape = CircleShape_get_userdata(L,index);
            return b2Shape_clone(shape->shape);
        }else if(utils::test_userdata(L, index, "Box2d::PolygonShapeClass")){
            PolygonShape* shape = PolygonShape_get_userdata(L,index);
            return b2Shape_clone(shape->shape);
        }else if(utils::test_userdata(L, index, "Box2d::EdgeShapeClass")){
            EdgeShape* shape = EdgeShape_get_userdata(L,index);
           return b2Shape_clone(shape->shape);
        }else if(utils::test_userdata(L, index, "Box2d::ChainShapeClass")){
            ChainShape* shape = ChainShape_get_userdata(L,index);
            return b2Shape_clone(shape->shape);
        }else {
            utils::error(L,"b2Shape unknown userdata");
        }
    }else{
        utils::error(L,"b2Shape should be table or userdata");
    }
}

void b2Shape_push(lua_State *L, b2Shape* shape){
    switch(shape->GetType()){
        case b2Shape::e_circle:{
            b2CircleShape_push(L,(b2CircleShape*)shape);
            break;
        }
        case b2Shape::e_polygon:{
            b2PolygonShape_push(L,(b2PolygonShape*)shape);
            break;
        }
        case b2Shape::e_edge:{
            b2EdgeShape_push(L,(b2EdgeShape*)shape);
            break;
        }
        case b2Shape::e_chain:{
            b2ChainShape_push(L,(b2ChainShape*)shape);
            break;
        }
    }
}

}