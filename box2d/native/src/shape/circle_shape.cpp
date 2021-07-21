#include "shape/circle_shape.h"
#include "utils.h"
#include "extra_utils.h"
#include "allocators.h"

#define META_NAME_CIRCLE_SHAPE "Box2d::CircleShapeClass"

namespace box2dDefoldNE {

CircleShape* CircleShape_get_userdata(lua_State* L, int index){
    if(luaL_checkudata(L, index, META_NAME_CIRCLE_SHAPE) == NULL){
        utils::error(L,"not circle shape");
    }
    CircleShape *shape =  *static_cast<CircleShape**>(luaL_checkudata(L, index, META_NAME_CIRCLE_SHAPE));
    return shape;
}

static int CircleShape_destroy(lua_State* L){
    delete *static_cast<CircleShape**>(luaL_checkudata(L, 1, META_NAME_CIRCLE_SHAPE));
    return 0;
}

//region BASE METHODS

static int GetType(lua_State* L){
    utils::check_arg_count(L, 1);
    CircleShape *shape =  CircleShape_get_userdata(L,1);
    lua_pushnumber(L, shape->shape->GetType());
    return 1;
}

static int GetRadius(lua_State* L){
    utils::check_arg_count(L, 1);
    CircleShape *shape =  CircleShape_get_userdata(L,1);
    lua_pushnumber(L, shape->shape->m_radius);
    return 1;
}

static int SetRadius(lua_State* L){
    utils::check_arg_count(L, 2);
    CircleShape *shape =  CircleShape_get_userdata(L,1);
    shape->shape->m_radius = luaL_checknumber(L,2);
    return 0;
}


static int Clone(lua_State* L){
    utils::check_arg_count(L, 1);
    CircleShape *shape =  CircleShape_get_userdata(L,1);
    b2CircleShape_push(L,shape->shape);
    return 1;
}

static int GetChildCount(lua_State* L){
    utils::check_arg_count(L, 1);
    CircleShape *shape =  CircleShape_get_userdata(L,1);
    lua_pushnumber(L, shape->shape->GetChildCount());
    return 1;
}

static int TestPoint(lua_State* L){
    utils::check_arg_count(L, 3);
    CircleShape *shape =  CircleShape_get_userdata(L,1);
    b2Transform transform = extra_utils::get_b2Transform_safe(L,2,"not transform");
    b2Vec2 point = extra_utils::get_b2vec_safe(L,3,"point not vector3");
    lua_pushboolean(L, shape->shape->TestPoint(transform, point));
    return 1;
}

static int RayCast(lua_State* L){
    utils::check_arg_count(L, 3,4);
    CircleShape *shape =  CircleShape_get_userdata(L,1);
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
    CircleShape *shape =  CircleShape_get_userdata(L,1);
    b2Transform transform = extra_utils::get_b2Transform_safe(L,2,"not transform");
    b2AABB aabb;
    shape->shape->ComputeAABB(&aabb,transform,0);
    extra_utils::b2AABB_push(L,aabb);
    return 1;
}

static int ComputeMass(lua_State* L){
    utils::check_arg_count(L, 2);
    CircleShape *shape =  CircleShape_get_userdata(L,1);
    float density =  luaL_checknumber(L,2);
    b2MassData massData;
    shape->shape->ComputeMass(&massData,density);
    extra_utils::massData_to_table(L,massData);
    return 1;
}
//endregion

//region functions
static int SetPosition(lua_State* L){
    utils::check_arg_count(L, 2);
    CircleShape *shape = CircleShape_get_userdata(L,1);
    shape->shape->m_p = extra_utils::get_b2vec_safe(L,2, "position not vector");
    return 0;
}

static int GetPosition(lua_State* L){
    utils::check_arg_count(L, 1);
    CircleShape *shape = CircleShape_get_userdata(L,1);
    b2Vec2 position = shape->shape->m_p;
    utils::push_vector(L, position.x, position.y, 0);
    return 1;
}

//endregion

CircleShape* b2CircleShape_push(lua_State *L, b2CircleShape* b2Shape){
    CircleShape *shape = new CircleShape(b2Shape);
    *static_cast<CircleShape**>(lua_newuserdata(L, sizeof(CircleShape*))) = shape;
    if(luaL_newmetatable(L, META_NAME_CIRCLE_SHAPE)){
        static const luaL_Reg functions[] =
        {
            {"GetType", GetType},
            {"GetRadius", GetRadius},
            {"Clone", Clone},
            {"GetChildCount", GetChildCount},
            {"TestPoint", TestPoint},
            {"RayCast", RayCast},
            {"ComputeAABB", ComputeAABB},
            {"ComputeMass", ComputeMass},
            {"SetRadius", SetRadius},
            {"SetPosition", SetPosition},
            {"GetPosition", GetPosition},
            {"__gc", CircleShape_destroy},
            {0, 0}
        };
        luaL_register(L, NULL,functions);
        lua_pushvalue(L, -1);
        lua_setfield(L, -1, "__index");
    }
    lua_setmetatable(L, -2);
    return shape;
}

CircleShape::CircleShape(b2CircleShape* shape){
    this->shape = (b2CircleShape*) b2Shape_clone(shape);
}

CircleShape::~CircleShape() {
    b2Shape_free(this->shape);
}


}