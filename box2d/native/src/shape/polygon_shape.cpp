#include "shape/polygon_shape.h"
#include "utils.h"
#include "extra_utils.h"
#include "allocators.h"

#define META_NAME_POLYGON_SHAPE "Box2d::PolygonShapeClass"

namespace box2dDefoldNE {

PolygonShape* PolygonShape_get_userdata(lua_State* L, int index){
    if(luaL_checkudata(L, index, META_NAME_POLYGON_SHAPE) == NULL){
        utils::error(L,"not polygon shape");
    }
    PolygonShape *shape =  *static_cast<PolygonShape**>(luaL_checkudata(L, index, META_NAME_POLYGON_SHAPE));
    return shape;
}

static int PolygonShape_destroy(lua_State* L){
    delete *static_cast<PolygonShape**>(luaL_checkudata(L, 1, META_NAME_POLYGON_SHAPE));
    return 0;
}

//region BASE METHODS

static int GetType(lua_State* L){
    utils::check_arg_count(L, 1);
    PolygonShape *shape =  PolygonShape_get_userdata(L,1);
    lua_pushnumber(L, shape->shape->GetType());
    return 1;
}

static int GetRadius(lua_State* L){
    utils::check_arg_count(L, 1);
    PolygonShape *shape =  PolygonShape_get_userdata(L,1);
    lua_pushnumber(L, shape->shape->m_radius);
    return 1;
}

static int SetRadius(lua_State* L){
    utils::check_arg_count(L, 2);
    PolygonShape *shape =  PolygonShape_get_userdata(L,1);
    shape->shape->m_radius = luaL_checknumber(L,2);
    return 0;
}

static int Clone(lua_State* L){
    utils::check_arg_count(L, 1);
    PolygonShape *shape =  PolygonShape_get_userdata(L,1);
    b2PolygonShape_push(L,shape->shape);
    return 1;
}

static int GetChildCount(lua_State* L){
    utils::check_arg_count(L, 1);
    PolygonShape *shape =  PolygonShape_get_userdata(L,1);
    lua_pushnumber(L, shape->shape->GetChildCount());
    return 1;
}

static int TestPoint(lua_State* L){
    utils::check_arg_count(L, 3);
    PolygonShape *shape =  PolygonShape_get_userdata(L,1);
    b2Transform transform = extra_utils::get_b2Transform_safe(L,2,"not transform");
    b2Vec2 point = extra_utils::get_b2vec_safe(L,3,"point not vector3");
    lua_pushboolean(L, shape->shape->TestPoint(transform, point));
    return 1;
}

static int RayCast(lua_State* L){
    utils::check_arg_count(L, 3,4);
    PolygonShape *shape =  PolygonShape_get_userdata(L,1);
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
    PolygonShape *shape =  PolygonShape_get_userdata(L,1);
    b2Transform transform = extra_utils::get_b2Transform_safe(L,2,"not transform");
    b2AABB aabb;
    shape->shape->ComputeAABB(&aabb,transform,0);
    extra_utils::b2AABB_push(L,aabb);
    return 1;
}

static int ComputeMass(lua_State* L){
    utils::check_arg_count(L, 2);
    PolygonShape *shape =  PolygonShape_get_userdata(L,1);
    float density =  luaL_checknumber(L,2);
    b2MassData massData;
    shape->shape->ComputeMass(&massData,density);
    extra_utils::massData_to_table(L,massData);
    return 1;
}
//endregion

//region functions
static int Set(lua_State* L){
    utils::check_arg_count(L, 2);
    PolygonShape *shape =  PolygonShape_get_userdata(L,1);
    int verticesSize = 0;
    b2Vec2* vertices = extra_utils::parse_vertices(L,2,&verticesSize);
    shape->shape->Set(vertices,verticesSize);
    delete[] vertices;
    return 0;
}

static int SetAsBox(lua_State* L){
    int count = lua_gettop(L);
    utils::check_arg_count(L, 3,5);
    if (count != 3 && count != 5) {
        luaL_error(L, "SetAsBox requires 3 or 5 arguments. Got %d.", count);
    }

    PolygonShape *shape =  PolygonShape_get_userdata(L,1);
    float hx = luaL_checknumber(L,2);
    float hy = luaL_checknumber(L,3);
    if(count == 3){
        shape->shape->SetAsBox(hx,hy);
    }else{
        b2Vec2 center = extra_utils::get_b2vec_safe(L,4,"center not vector3");
        float angle = luaL_checknumber(L,5);
        shape->shape->SetAsBox(hx,hy,center,angle);
    }
    return 0;
}

static int Validate(lua_State* L){
    utils::check_arg_count(L, 1);
    PolygonShape *shape =  PolygonShape_get_userdata(L,1);
    lua_pushboolean(L,shape->shape->Validate());
    return 1;
}

static int GetCentroid(lua_State* L){
    utils::check_arg_count(L, 1);
    PolygonShape *shape =  PolygonShape_get_userdata(L,1);
    b2Vec2 centroid = shape->shape->m_centroid;
    utils::push_vector(L, centroid.x, centroid.y, 0);
    return 1;
}

static int GetVertices(lua_State* L){
    utils::check_arg_count(L, 1);
    PolygonShape *shape =  PolygonShape_get_userdata(L,1);
    lua_newtable(L);
    for (int32 i = 0; i < shape->shape->m_count; ++i){
        b2Vec2 vertex = shape->shape->m_vertices[i];
        utils::push_vector(L, vertex.x, vertex.y, 0);
        lua_rawseti(L, -2, i+1);
    }
    return 1;
}

static int GetNormals(lua_State* L){
    utils::check_arg_count(L, 1);
    PolygonShape *shape =  PolygonShape_get_userdata(L,1);
    lua_newtable(L);
    for (int32 i = 0; i < shape->shape->m_count; ++i){
        b2Vec2 normal = shape->shape->m_normals[i];
        utils::push_vector(L, normal.x, normal.y, 0);
        lua_rawseti(L, -2, i+1);
    }
    return 1;
}

static int GetCount(lua_State* L){
    utils::check_arg_count(L, 1);
    PolygonShape *shape =  PolygonShape_get_userdata(L,1);
    lua_pushnumber(L,shape->shape->m_count);
    return 1;
}


//endregion

PolygonShape* b2PolygonShape_push(lua_State *L, b2PolygonShape* b2Shape){
    PolygonShape *shape = new PolygonShape(b2Shape);
    *static_cast<PolygonShape**>(lua_newuserdata(L, sizeof(PolygonShape*))) = shape;
    if(luaL_newmetatable(L, META_NAME_POLYGON_SHAPE)){
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
            {"Set", Set},
            {"SetAsBox", SetAsBox},
            {"Validate", Validate},
            {"GetCentroid", GetCentroid},
            {"GetVertices", GetVertices},
            {"GetNormals", GetNormals},
            {"GetCount", GetCount},
            {"__gc", PolygonShape_destroy},
            {0, 0}
        };
        luaL_register(L, NULL,functions);
        lua_pushvalue(L, -1);
        lua_setfield(L, -1, "__index");
    }
    lua_setmetatable(L, -2);
    return shape;
}

PolygonShape::PolygonShape(b2PolygonShape* shape){
    this->shape = (b2PolygonShape*) b2Shape_clone(shape);
}

PolygonShape::~PolygonShape(){
    b2Shape_free(this->shape);
}


}