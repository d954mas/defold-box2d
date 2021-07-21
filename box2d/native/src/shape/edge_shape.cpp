#include "shape/edge_shape.h"
#include "utils.h"
#include "extra_utils.h"
#include "allocators.h"

#define META_NAME_EDGE_SHAPE "Box2d::EdgeShapeClass"

namespace box2dDefoldNE {

EdgeShape* EdgeShape_get_userdata(lua_State* L, int index){
    if(luaL_checkudata(L, index, META_NAME_EDGE_SHAPE) == NULL){
        utils::error(L,"not edge shape");
    }
    EdgeShape *shape =  *static_cast<EdgeShape**>(luaL_checkudata(L, index, META_NAME_EDGE_SHAPE));
    return shape;
}

static int EdgeShape_destroy(lua_State* L){
    delete *static_cast<EdgeShape**>(luaL_checkudata(L, 1, META_NAME_EDGE_SHAPE));
    return 0;
}

//region BASE METHODS

static int GetType(lua_State* L){
    utils::check_arg_count(L, 1);
    EdgeShape *shape =  EdgeShape_get_userdata(L,1);
    lua_pushnumber(L, shape->shape->GetType());
    return 1;
}

static int GetRadius(lua_State* L){
    utils::check_arg_count(L, 1);
    EdgeShape *shape =  EdgeShape_get_userdata(L,1);
    lua_pushnumber(L, shape->shape->m_radius);
    return 1;
}

static int SetRadius(lua_State* L){
    utils::check_arg_count(L, 2);
    EdgeShape *shape =  EdgeShape_get_userdata(L,1);
    shape->shape->m_radius = luaL_checknumber(L,2);
    return 0;
}


static int Clone(lua_State* L){
    utils::check_arg_count(L, 1);
    EdgeShape *shape =  EdgeShape_get_userdata(L,1);
    b2EdgeShape_push(L,shape->shape);
    return 1;
}

static int GetChildCount(lua_State* L){
    utils::check_arg_count(L, 1);
    EdgeShape *shape =  EdgeShape_get_userdata(L,1);
    lua_pushnumber(L, shape->shape->GetChildCount());
    return 1;
}

static int TestPoint(lua_State* L){
    utils::check_arg_count(L, 3);
    EdgeShape *shape =  EdgeShape_get_userdata(L,1);
    b2Transform transform = extra_utils::get_b2Transform_safe(L,2,"not transform");
    b2Vec2 point = extra_utils::get_b2vec_safe(L,3,"point not vector3");
    lua_pushboolean(L, shape->shape->TestPoint(transform, point));
    return 1;
}

static int RayCast(lua_State* L){
    utils::check_arg_count(L, 3,4);
    EdgeShape *shape =  EdgeShape_get_userdata(L,1);
    b2RayCastInput  input = extra_utils::get_b2RayCastInput_safe(L,2);
    b2Transform transform = extra_utils::get_b2Transform_safe(L,3,"not transform");
    b2RayCastOutput output;
    output.fraction = -1;
    output.normal.x = 0;
    output.normal.y = 0;
    bool result = shape->shape->RayCast(&output,input,transform,0);
    if(result){
        extra_utils::b2RayCastOutput_push(L,output);
    }else{
        lua_pushnil(L);
    }
    return 1;
}

static int ComputeAABB(lua_State* L){
    utils::check_arg_count(L, 2, 3);
    EdgeShape *shape =  EdgeShape_get_userdata(L,1);
    b2Transform transform = extra_utils::get_b2Transform_safe(L,2,"not transform");
    b2AABB aabb;
    shape->shape->ComputeAABB(&aabb,transform,0);
    extra_utils::b2AABB_push(L,aabb);
    return 1;
}

static int ComputeMass(lua_State* L){
    utils::check_arg_count(L, 2);
    EdgeShape *shape =  EdgeShape_get_userdata(L,1);
    float density =  luaL_checknumber(L,2);
    b2MassData massData;
    shape->shape->ComputeMass(&massData,density);
    extra_utils::massData_to_table(L,massData);
    return 1;
}
//endregion

//region functions

static int SetOneSided(lua_State* L){
    utils::check_arg_count(L, 5);
    EdgeShape *shape =  EdgeShape_get_userdata(L,1);
    b2Vec2 v0 = extra_utils::get_b2vec_safe(L,2,"v0 not vector3");
    b2Vec2 v1 = extra_utils::get_b2vec_safe(L,3,"v1 not vector3");
    b2Vec2 v2 = extra_utils::get_b2vec_safe(L,4,"v2 not vector3");
    b2Vec2 v3 = extra_utils::get_b2vec_safe(L,5,"v3 not vector3");
    shape->shape->SetOneSided(v0,v1,v2,v3);
    return 0;
}

static int SetTwoSided(lua_State* L){
    utils::check_arg_count(L, 3);
    EdgeShape *shape =  EdgeShape_get_userdata(L,1);
    b2Vec2 v1 = extra_utils::get_b2vec_safe(L,2,"v1 not vector3");
    b2Vec2 v2 = extra_utils::get_b2vec_safe(L,3,"v2 not vector3");
    shape->shape->SetTwoSided(v1,v2);
    return 0;
}

static int GetVertex0(lua_State* L){
    utils::check_arg_count(L, 1);
    EdgeShape *shape =  EdgeShape_get_userdata(L,1);
    b2Vec2 vertex = shape->shape->m_vertex0;
    utils::push_vector(L, vertex.x, vertex.y, 0);
    return 1;
}

static int GetVertex1(lua_State* L){
    utils::check_arg_count(L, 1);
    EdgeShape *shape =  EdgeShape_get_userdata(L,1);
    b2Vec2 vertex = shape->shape->m_vertex1;
    utils::push_vector(L, vertex.x, vertex.y, 0);
    return 1;
}

static int GetVertex2(lua_State* L){
    utils::check_arg_count(L, 1);
    EdgeShape *shape =  EdgeShape_get_userdata(L,1);
    b2Vec2 vertex = shape->shape->m_vertex2;
    utils::push_vector(L, vertex.x, vertex.y, 0);
    return 1;
}

static int GetVertex3(lua_State* L){
    utils::check_arg_count(L, 1);
    EdgeShape *shape =  EdgeShape_get_userdata(L,1);
    b2Vec2 vertex = shape->shape->m_vertex3;
    utils::push_vector(L, vertex.x, vertex.y, 0);
    return 1;
}

static int IsOneSided(lua_State* L){
    utils::check_arg_count(L, 1);
    EdgeShape *shape =  EdgeShape_get_userdata(L,1);
    lua_pushboolean(L, shape->shape->m_oneSided);
    return 1;
}


//endregion

EdgeShape* b2EdgeShape_push(lua_State *L, b2EdgeShape* b2Shape){
    EdgeShape *shape = new EdgeShape(b2Shape);
    *static_cast<EdgeShape**>(lua_newuserdata(L, sizeof(EdgeShape*))) = shape;
    if(luaL_newmetatable(L, META_NAME_EDGE_SHAPE)){
        static const luaL_Reg functions[] =
        {
            {"GetType", GetType},
            {"GetRadius", GetRadius},
            {"SetRadius", SetRadius},
            {"Clone", Clone},
            {"GetChildCount", GetChildCount},
            {"TestPoint", TestPoint},
            {"RayCast", RayCast},
            {"ComputeAABB", ComputeAABB},
            {"ComputeMass", ComputeMass},
            {"SetOneSided", SetOneSided},
            {"SetTwoSided", SetTwoSided},
            {"GetVertex0", GetVertex0},
            {"GetVertex1", GetVertex1},
            {"GetVertex2", GetVertex2},
            {"GetVertex3", GetVertex3},
            {"IsOneSided", IsOneSided},
            {"__gc", EdgeShape_destroy},
            {0, 0}
        };
        luaL_register(L, NULL,functions);
        lua_pushvalue(L, -1);
        lua_setfield(L, -1, "__index");
    }
    lua_setmetatable(L, -2);
    return shape;
}

EdgeShape::EdgeShape(b2EdgeShape* shape){
     this->shape = (b2EdgeShape*) b2Shape_clone(shape);
}

EdgeShape::~EdgeShape(){
    b2Shape_free(this->shape);
}

}