#include "shape/chain_shape.h"
#include "shape/edge_shape.h"
#include "utils.h"
#include "extra_utils.h"
#include "allocators.h"

#define META_NAME_CHAIN_SHAPE "Box2d::ChainShapeClass"

namespace box2dDefoldNE {

ChainShape* ChainShape_get_userdata(lua_State* L, int index){
    if(luaL_checkudata(L, index, META_NAME_CHAIN_SHAPE) == NULL){
        utils::error(L,"not chain shape");
    }
    ChainShape *shape =  *static_cast<ChainShape**>(luaL_checkudata(L, index, META_NAME_CHAIN_SHAPE));
    return shape;
}

static int ChainShape_destroy(lua_State* L){
    delete *static_cast<ChainShape**>(luaL_checkudata(L, 1, META_NAME_CHAIN_SHAPE));
    return 0;
}

//region BASE METHODS

static int GetType(lua_State* L){
    utils::check_arg_count(L, 1);
    ChainShape *shape =  ChainShape_get_userdata(L,1);
    lua_pushnumber(L, shape->shape->GetType());
    return 1;
}

static int GetRadius(lua_State* L){
    utils::check_arg_count(L, 1);
    ChainShape *shape =  ChainShape_get_userdata(L,1);
    lua_pushnumber(L, shape->shape->m_radius);
    return 1;
}

static int SetRadius(lua_State* L){
    utils::check_arg_count(L, 2);
    ChainShape *shape =  ChainShape_get_userdata(L,1);
    shape->shape->m_radius = luaL_checknumber(L,2);
    return 0;
}


static int Clone(lua_State* L){
    utils::check_arg_count(L, 1);
    ChainShape *shape =  ChainShape_get_userdata(L,1);
    b2ChainShape_push(L,shape->shape);
    return 1;
}

static int GetChildCount(lua_State* L){
    utils::check_arg_count(L, 1);
    ChainShape *shape =  ChainShape_get_userdata(L,1);
    lua_pushnumber(L, shape->shape->GetChildCount());
    return 1;
}

static int TestPoint(lua_State* L){
    utils::check_arg_count(L, 3);
    ChainShape *shape =  ChainShape_get_userdata(L,1);
    b2Transform transform = extra_utils::get_b2Transform_safe(L,2,"not transform");
    b2Vec2 point = extra_utils::get_b2vec_safe(L,3,"point not vector3");
    lua_pushboolean(L, shape->shape->TestPoint(transform, point));
    return 1;
}

static int RayCast(lua_State* L){
    utils::check_arg_count(L, 4);
    ChainShape *shape =  ChainShape_get_userdata(L,1);
    b2RayCastInput  input = extra_utils::get_b2RayCastInput_safe(L,2);
    b2Transform transform = extra_utils::get_b2Transform_safe(L,3,"not transform");
    int childIndex = luaL_checknumber(L,4);
    b2RayCastOutput output;
    output.fraction = -1;
    output.normal.x = 0;
    output.normal.y = 0;
    bool result = shape->shape->RayCast(&output,input,transform,childIndex);
    if(result){
        extra_utils::b2RayCastOutput_push(L,output);
    }else{
        lua_pushnil(L);
    }
    return 1;
}

static int ComputeAABB(lua_State* L){
    utils::check_arg_count(L, 3);
    ChainShape *shape =  ChainShape_get_userdata(L,1);
    b2Transform transform = extra_utils::get_b2Transform_safe(L,2,"not transform");
    int childIndex = luaL_checknumber(L,3);
    b2AABB aabb;
    shape->shape->ComputeAABB(&aabb,transform,childIndex);
    extra_utils::b2AABB_push(L,aabb);
    return 1;
}

static int ComputeMass(lua_State* L){
    utils::check_arg_count(L, 2);
    ChainShape *shape =  ChainShape_get_userdata(L,1);
    float density =  luaL_checknumber(L,2);
    b2MassData massData;
    shape->shape->ComputeMass(&massData,density);
    extra_utils::massData_to_table(L,massData);
    return 1;
}
//endregion

//region functions

static int Clear(lua_State* L){
    utils::check_arg_count(L, 1);
    ChainShape *shape =  ChainShape_get_userdata(L,1);
    shape->shape->Clear();
    return 0;
}

static int CreateLoop(lua_State* L){
    utils::check_arg_count(L, 2);
    ChainShape *shape =  ChainShape_get_userdata(L,1);
    int verticesSize = 0;
    b2Vec2* vertices = extra_utils::parse_vertices(L,2,&verticesSize);
    shape->shape->CreateLoop(vertices,verticesSize);
    delete[] vertices;
    return 0;
}

static int CreateChain(lua_State* L){
    utils::check_arg_count(L, 4);
    ChainShape *shape =  ChainShape_get_userdata(L,1);
    int verticesSize = 0;
    b2Vec2* vertices = extra_utils::parse_vertices(L,2,&verticesSize);
    b2Vec2 prevVertex = extra_utils::get_b2vec_safe(L,3,"prevVertex not vector3");
    b2Vec2 nextVertex = extra_utils::get_b2vec_safe(L,4,"nextVertex not vector3");
    shape->shape->CreateChain(vertices,verticesSize,prevVertex,nextVertex);
    delete[] vertices;
    return 0;
}

/// Get a child edge.
static int GetChildEdge(lua_State* L){
    utils::check_arg_count(L, 2);
    ChainShape *shape =  ChainShape_get_userdata(L,1);
    int childIndex = luaL_checknumber(L,2);
    b2EdgeShape edge;
    shape->shape->GetChildEdge(&edge,childIndex);
    b2EdgeShape_push(L, &edge);
    return 1;
}

static int GetVertices(lua_State* L){
    utils::check_arg_count(L, 1);
    ChainShape *shape =  ChainShape_get_userdata(L,1);
    lua_newtable(L);
    for (int32 i = 0; i < shape->shape->m_count; ++i){
        b2Vec2 vertex = shape->shape->m_vertices[i];
        utils::push_vector(L, vertex.x, vertex.y, 0);
        lua_rawseti(L, -2, i+1);
    }
    return 1;
}

static int GetNextVertex(lua_State* L){
    utils::check_arg_count(L, 1);
    ChainShape *shape =  ChainShape_get_userdata(L,1);
    b2Vec2 vertex = shape->shape->m_nextVertex;
    utils::push_vector(L, vertex.x, vertex.y, 0);
    return 1;
}

static int GetPrevVertex(lua_State* L){
    utils::check_arg_count(L, 1);
    ChainShape *shape =  ChainShape_get_userdata(L,1);
    b2Vec2 vertex = shape->shape->m_prevVertex;
    utils::push_vector(L, vertex.x, vertex.y, 0);
    return 1;
}

static int GetCount(lua_State* L){
    utils::check_arg_count(L, 1);
    ChainShape *shape =  ChainShape_get_userdata(L,1);
    lua_pushnumber(L,shape->shape->m_count);
    return 1;
}

//endregion

ChainShape* b2ChainShape_push(lua_State *L, b2ChainShape* b2Shape){
    ChainShape *shape = new ChainShape(b2Shape);
    *static_cast<ChainShape**>(lua_newuserdata(L, sizeof(ChainShape*))) = shape;
    if(luaL_newmetatable(L, META_NAME_CHAIN_SHAPE)){
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
            {"Clear", Clear},
            {"CreateLoop", CreateLoop},
            {"CreateChain", CreateChain},
            {"GetChildEdge", GetChildEdge},
            {"GetVertices", GetVertices},
            {"GetNextVertex", GetNextVertex},
            {"GetPrevVertex", GetPrevVertex},
            {"GetCount", GetCount},
            {"__gc", ChainShape_destroy},
            {0, 0}
        };
        luaL_register(L, NULL,functions);
        lua_pushvalue(L, -1);
        lua_setfield(L, -1, "__index");
    }
    lua_setmetatable(L, -2);
    return shape;
}

ChainShape::ChainShape(b2ChainShape* shape){
    this->shape = (b2ChainShape*)b2Shape_clone(shape);
}

ChainShape::~ChainShape() {
    b2Shape_free(this->shape);
}

}