#include "joint_def.h"
#include "joint.h"
#include "utils.h"
#include "shape.h"
#include "body.h"
#include <extra_utils.h>
#include <static_hash.h>

b2RevoluteJointDef* b2RevoluteJointDef_from_table(lua_State *L){
    if (lua_istable(L, -1)) {
        b2RevoluteJointDef* def = new b2RevoluteJointDef();
        b2Vec2 anchor = extra_utils::table_get_b2vec_safe(L,"anchor","no anchor");
        lua_pushnil(L);  /* first key */
        while (lua_next(L, -2) != 0) {
            const char* key = lua_tostring(L, -2);
            switch (hash_string(key)) {
                case HASH_collideConnected:
                    def->collideConnected = lua_toboolean(L,-1);
                    break;
                case HASH_userData:
                    if (lua_istable(L ,-1)) {
                        lua_pushvalue(L, -1);
                        def->userData.pointer = luaL_ref(L,LUA_REGISTRYINDEX);
                    }else{
                        utils::error(L,"userdata can be only table or nil");
                    }
                    break;
                case HASH_bodyA:
                    def->bodyA = Body_get_userdata_safe(L,-1)->body;
                    break;
                case HASH_bodyB:
                    def->bodyB = Body_get_userdata_safe(L,-1)->body;
                    break;
                case HASH_type:
                    break;
                case HASH_anchor:
                    break;
                case HASH_localAnchorA:
                     def->localAnchorA = extra_utils::get_b2vec_safe(L,-1,"localAnchorA not v3");
                    break;
                case HASH_localAnchorB:
                    def->localAnchorB = extra_utils::get_b2vec_safe(L,-1,"localAnchorB not v3");
                    break;
                case HASH_referenceAngle:
                    def->referenceAngle = luaL_checknumber(L,-1);
                    break;
                case HASH_lowerAngle:
                    def->lowerAngle = luaL_checknumber(L,-1);
                    break;
                case HASH_upperAngle:
                    def->upperAngle = luaL_checknumber(L,-1);
                    break;
               case HASH_maxMotorTorque:
                    def->maxMotorTorque = luaL_checknumber(L,-1);
                    break;
               case HASH_motorSpeed:
                    def->motorSpeed = luaL_checknumber(L,-1);
                    break;
               case HASH_enableLimit:
                    def->enableLimit = lua_toboolean(L,-1);
                    break;
               case HASH_enableMotor:
                    def->enableMotor = lua_toboolean(L,-1);
                    break;
               default:
                    lua_pushfstring(L, "unknown key:%s", key);
                    lua_error(L);
                    break;
            }
            /* removes 'value'; keeps 'key' for next iteration */
            lua_pop(L, 1);
        }
        if(def->bodyA == NULL) utils::error(L,"no bodyA");
        if(def->bodyB == NULL) utils::error(L,"no bodyB");
        def->Initialize(def->bodyA, def->bodyB, anchor);
        return def;
    }else{
        utils::error(L,"JointDef should be table");
    }
}

b2PrismaticJointDef* b2PrismaticJointDef_from_table(lua_State *L){
    if (lua_istable(L, -1)) {
        b2PrismaticJointDef* def = new b2PrismaticJointDef();
        b2Vec2 anchor = extra_utils::table_get_b2vec_safe(L,"anchor","no anchor");
        b2Vec2 axis = extra_utils::table_get_b2vec_safe(L,"axis","no axis");
        lua_pushnil(L);  /* first key */
        while (lua_next(L, -2) != 0) {
            const char* key = lua_tostring(L, -2);
            switch (hash_string(key)) {
                case HASH_collideConnected:
                    def->collideConnected = lua_toboolean(L,-1);
                    break;
                case HASH_userData:
                    if (lua_istable(L ,-1)) {
                        lua_pushvalue(L, -1);
                        def->userData.pointer = luaL_ref(L,LUA_REGISTRYINDEX);
                    }else{
                        utils::error(L,"userdata can be only table or nil");
                    }
                    break;
                case HASH_bodyA:
                    def->bodyA = Body_get_userdata_safe(L,-1)->body;
                    break;
                case HASH_bodyB:
                    def->bodyB = Body_get_userdata_safe(L,-1)->body;
                    break;
                case HASH_type:
                    break;
                case HASH_anchor:
                    break;
                case HASH_axis:
                    break;
                case HASH_localAnchorA:
                    def->localAnchorA = extra_utils::get_b2vec_safe(L,-1,"localAnchorA not v3");
                    break;
                case HASH_localAnchorB:
                    def->localAnchorB = extra_utils::get_b2vec_safe(L,-1,"localAnchorB  not v3");
                    break;
                case HASH_referenceAngle:
                    def->referenceAngle = luaL_checknumber(L,-1);
                    break;
                case HASH_motorSpeed:
                    def->motorSpeed = luaL_checknumber(L,-1);
                    break;
                case HASH_enableLimit:
                    def->enableLimit = lua_toboolean(L,-1);
                    break;
                case HASH_enableMotor:
                    def->enableMotor = lua_toboolean(L,-1);
                    break;
                case HASH_localAxisA:
                    def->localAxisA = extra_utils::get_b2vec_safe(L,-1,"localAxisA  not v3");
                    break;
                case HASH_lowerTranslation:
                    def->lowerTranslation = luaL_checknumber(L,-1);
                    break;
                case HASH_upperTranslation:
                    def->upperTranslation = luaL_checknumber(L,-1);
                    break;
                case HASH_maxMotorForce:
                    def->maxMotorForce = luaL_checknumber(L,-1);
                    break;
                default:
                    lua_pushfstring(L, "unknown key:%s", key);
                    lua_error(L);
                    break;
            }
            /* removes 'value'; keeps 'key' for next iteration */
            lua_pop(L, 1);
        }
        if(def->bodyA == NULL) utils::error(L,"no bodyA");
        if(def->bodyB == NULL) utils::error(L,"no bodyB");
        def->Initialize(def->bodyA, def->bodyB, anchor, axis);
        return def;
    }else{
        utils::error(L,"JointDef should be table");
    }
}

b2DistanceJointDef* b2DistanceJointDef_from_table(lua_State *L){
    if (lua_istable(L, -1)) {
        b2DistanceJointDef* def = new b2DistanceJointDef();
        b2Vec2 anchorA = extra_utils::table_get_b2vec_safe(L,"anchorA","no anchorA");
        b2Vec2 anchorB = extra_utils::table_get_b2vec_safe(L,"anchorB","no anchorB");
        lua_pushnil(L);  /* first key */
        while (lua_next(L, -2) != 0) {
            const char* key = lua_tostring(L, -2);
            switch (hash_string(key)) {
                case HASH_collideConnected:
                   def->collideConnected = lua_toboolean(L,-1);
                   break;
                case HASH_userData:
                   if (lua_istable(L ,-1)) {
                       lua_pushvalue(L, -1);
                       def->userData.pointer = luaL_ref(L,LUA_REGISTRYINDEX);
                   }else{
                       utils::error(L,"userdata can be only table or nil");
                   }
                   break;
                case HASH_bodyA:
                   def->bodyA = Body_get_userdata_safe(L,-1)->body;
                   break;
                case HASH_bodyB:
                   def->bodyB = Body_get_userdata_safe(L,-1)->body;
                   break;
                case HASH_type:
                   break;
                case HASH_anchorA:
                   break;
                case HASH_anchorB:
                   break;
                case HASH_localAnchorA:
                   def->localAnchorA = extra_utils::get_b2vec_safe(L,-1,"localAnchorA not v3");
                   break;
                case HASH_localAnchorB:
                   def->localAnchorB = extra_utils::get_b2vec_safe(L,-1,"localAnchorB  not v3");
                   break;
                case HASH_length:
                    def->length = luaL_checknumber(L,-1);
                    break;
                case HASH_minLength:
                    def->minLength = luaL_checknumber(L,-1);
                    break;
                case HASH_maxLength:
                    def->maxLength = luaL_checknumber(L,-1);
                    break;
                case HASH_stiffness:
                    def->stiffness = luaL_checknumber(L,-1);
                    break;
                case HASH_damping:
                    def->damping = luaL_checknumber(L,-1);
                    break;
                default:
                    lua_pushfstring(L, "unknown key:%s", key);
                    lua_error(L);
                    break;
            }
            /* removes 'value'; keeps 'key' for next iteration */
            lua_pop(L, 1);
        }
        if(def->bodyA == NULL) utils::error(L,"no bodyA");
        if(def->bodyB == NULL) utils::error(L,"no bodyB");
        def->Initialize(def->bodyA, def->bodyB, anchorA, anchorB);
        return def;
    }else{
        utils::error(L,"JointDef should be table");
    }
}

b2PulleyJointDef* b2PulleyJointDef_from_table(lua_State *L){
    if (lua_istable(L, -1)) {
        b2PulleyJointDef* def = new b2PulleyJointDef();
        b2Vec2 groundAnchorA = extra_utils::table_get_b2vec_safe(L,"groundAnchorA","no groundAnchorA");
        b2Vec2 groundAnchorB = extra_utils::table_get_b2vec_safe(L,"groundAnchorB","no groundAnchorB");
        b2Vec2 anchorA = extra_utils::table_get_b2vec_safe(L,"anchorA","no anchorA");
        b2Vec2 anchorB = extra_utils::table_get_b2vec_safe(L,"anchorB","no anchorB");
        if(utils::table_is_nil(L,"ratio")){
            utils::error(L,"no ratio");
        }
        lua_pushnil(L);  /* first key */
        while (lua_next(L, -2) != 0) {
            const char* key = lua_tostring(L, -2);
            switch (hash_string(key)) {
                case HASH_collideConnected:
                   def->collideConnected = lua_toboolean(L,-1);
                   break;
                case HASH_userData:
                   if (lua_istable(L ,-1)) {
                       lua_pushvalue(L, -1);
                       def->userData.pointer = luaL_ref(L,LUA_REGISTRYINDEX);
                   }else{
                       utils::error(L,"userdata can be only table or nil");
                   }
                   break;
                case HASH_bodyA:
                   def->bodyA = Body_get_userdata_safe(L,-1)->body;
                   break;
                case HASH_bodyB:
                   def->bodyB = Body_get_userdata_safe(L,-1)->body;
                   break;
                case HASH_type:
                   break;
                case HASH_anchorA:
                   break;
                case HASH_anchorB:
                   break;
                case HASH_groundAnchorA:
                   break;
                case HASH_groundAnchorB:
                   break;
                case HASH_ratio:
                    def->ratio = luaL_checknumber(L,-1);
                   break;
                case HASH_localAnchorA:
                   def->localAnchorA = extra_utils::get_b2vec_safe(L,-1,"localAnchorA not v3");
                   break;
                case HASH_localAnchorB:
                   def->localAnchorB = extra_utils::get_b2vec_safe(L,-1,"localAnchorB  not v3");
                   break;
                case HASH_lengthA:
                    def->lengthA = luaL_checknumber(L,-1);
                    break;
                case HASH_lengthB:
                    def->lengthB = luaL_checknumber(L,-1);
                    break;
                default:
                    lua_pushfstring(L, "unknown key:%s", key);
                    lua_error(L);
                    break;
            }
            /* removes 'value'; keeps 'key' for next iteration */
            lua_pop(L, 1);
        }
        if(def->bodyA == NULL) utils::error(L,"no bodyA");
        if(def->bodyB == NULL) utils::error(L,"no bodyB");
        def->Initialize(def->bodyA, def->bodyB, groundAnchorA,
                        groundAnchorB,anchorA, anchorB, def->ratio);
        return def;
    }else{
        utils::error(L,"JointDef should be table");
    }
}

b2MouseJointDef* b2MouseJointDef_from_table(lua_State *L){
    if (lua_istable(L, -1)) {
        b2MouseJointDef* def = new b2MouseJointDef();
        lua_pushnil(L);  /* first key */
        while (lua_next(L, -2) != 0) {
            const char* key = lua_tostring(L, -2);
            switch (hash_string(key)) {
                case HASH_collideConnected:
                   def->collideConnected = lua_toboolean(L,-1);
                   break;
                case HASH_userData:
                   if (lua_istable(L ,-1)) {
                       lua_pushvalue(L, -1);
                       def->userData.pointer = luaL_ref(L,LUA_REGISTRYINDEX);
                   }else{
                       utils::error(L,"userdata can be only table or nil");
                   }
                   break;
                case HASH_bodyA:
                   def->bodyA = Body_get_userdata_safe(L,-1)->body;
                   break;
                case HASH_bodyB:
                   def->bodyB = Body_get_userdata_safe(L,-1)->body;
                   break;
                case HASH_type:
                   break;
                case HASH_target:
                    def->target = extra_utils::get_b2vec_safe(L,-1,"target  not v3");
                    break;
                case HASH_maxForce:
                    def->maxForce = luaL_checknumber(L,-1);
                    break;
                case HASH_stiffness:
                    def->stiffness = luaL_checknumber(L,-1);
                    break;
                case HASH_damping:
                    def->damping = luaL_checknumber(L,-1);
                    break;
                default:
                    lua_pushfstring(L, "unknown key:%s", key);
                    lua_error(L);
                    break;
            }
            /* removes 'value'; keeps 'key' for next iteration */
            lua_pop(L, 1);
        }
        if(def->bodyA == NULL) utils::error(L,"no bodyA");
        if(def->bodyB == NULL) utils::error(L,"no bodyB");
        return def;
    }else{
        utils::error(L,"JointDef should be table");
    }
}

b2GearJointDef* b2GearJointDef_from_table(lua_State *L){
    if (lua_istable(L, -1)) {
        b2GearJointDef* def = new b2GearJointDef();
        lua_pushnil(L);  /* first key */
        while (lua_next(L, -2) != 0) {
            const char* key = lua_tostring(L, -2);
            switch (hash_string(key)) {
                case HASH_collideConnected:
                   def->collideConnected = lua_toboolean(L,-1);
                   break;
                case HASH_userData:
                   if (lua_istable(L ,-1)) {
                       lua_pushvalue(L, -1);
                       def->userData.pointer = luaL_ref(L,LUA_REGISTRYINDEX);
                   }else{
                       utils::error(L,"userdata can be only table or nil");
                   }
                   break;
                case HASH_bodyA:
                   def->bodyA = Body_get_userdata_safe(L,-1)->body;
                   break;
                case HASH_bodyB:
                   def->bodyB = Body_get_userdata_safe(L,-1)->body;
                   break;
                case HASH_joint1:
                    def->joint1 = Joint_get_userdata_safe(L,-1)->joint;
                   break;
                case HASH_joint2:
                    def->joint2 = Joint_get_userdata_safe(L,-1)->joint;
                   break;
                case HASH_type:
                   break;
                case HASH_ratio:
                    def->ratio = luaL_checknumber(L,-1);
                    break;
                default:
                    lua_pushfstring(L, "unknown key:%s", key);
                    lua_error(L);
                    break;
            }
            /* removes 'value'; keeps 'key' for next iteration */
            lua_pop(L, 1);
        }
        if(def->bodyA == NULL) utils::error(L,"no bodyA");
        if(def->bodyB == NULL) utils::error(L,"no bodyB");
        if(def->joint1 == NULL) utils::error(L,"no joint1");
        if(def->joint2 == NULL) utils::error(L,"no joint2");
        return def;
    }else{
        utils::error(L,"JointDef should be table");
    }
}

b2WheelJointDef* b2WheelJointDef_from_table(lua_State *L){
    if (lua_istable(L, -1)) {
        b2WheelJointDef* def = new b2WheelJointDef();
        b2Vec2 anchor = extra_utils::table_get_b2vec_safe(L,"anchor","no anchor");
        b2Vec2 axis = extra_utils::table_get_b2vec_safe(L,"axis","no axis");
        lua_pushnil(L);  /* first key */
        while (lua_next(L, -2) != 0) {
            const char* key = lua_tostring(L, -2);
            switch (hash_string(key)) {
                case HASH_collideConnected:
                   def->collideConnected = lua_toboolean(L,-1);
                   break;
                case HASH_userData:
                   if (lua_istable(L ,-1)) {
                       lua_pushvalue(L, -1);
                       def->userData.pointer = luaL_ref(L,LUA_REGISTRYINDEX);
                   }else{
                       utils::error(L,"userdata can be only table or nil");
                   }
                   break;
                case HASH_bodyA:
                   def->bodyA = Body_get_userdata_safe(L,-1)->body;
                   break;
                case HASH_bodyB:
                   def->bodyB = Body_get_userdata_safe(L,-1)->body;
                   break;
                case HASH_axis:
                   break;
                case HASH_anchor:
                   break;
                case HASH_type:
                   break;
                case HASH_localAnchorA:
                   def->localAnchorA = extra_utils::get_b2vec_safe(L,-1,"localAnchorA not v3");
                   break;
                case HASH_localAnchorB:
                   def->localAnchorB = extra_utils::get_b2vec_safe(L,-1,"localAnchorB  not v3");
                   break;
                case HASH_enableLimit:
                    def->enableLimit = lua_toboolean(L,-1);
                    break;
                case HASH_enableMotor:
                    def->enableMotor = lua_toboolean(L,-1);
                    break;
                case HASH_motorSpeed:
                    def->motorSpeed = luaL_checknumber(L,-1);
                    break;
                case HASH_maxMotorTorque:
                    def->maxMotorTorque = luaL_checknumber(L,-1);
                    break;
                case HASH_localAxisA:
                    def->localAxisA = extra_utils::get_b2vec_safe(L,-1,"localAxisA  not v3");
                    break;
                case HASH_lowerTranslation:
                    def->lowerTranslation = luaL_checknumber(L,-1);
                    break;
                case HASH_upperTranslation:
                    def->upperTranslation = luaL_checknumber(L,-1);
                    break;
                case HASH_stiffness:
                    def->stiffness = luaL_checknumber(L,-1);
                    break;
                case HASH_damping:
                    def->damping = luaL_checknumber(L,-1);
                    break;
                default:
                    lua_pushfstring(L, "unknown key:%s", key);
                    lua_error(L);
                    break;
            }
            /* removes 'value'; keeps 'key' for next iteration */
            lua_pop(L, 1);
        }
        if(def->bodyA == NULL) utils::error(L,"no bodyA");
        if(def->bodyB == NULL) utils::error(L,"no bodyB");
        def->Initialize(def->bodyA, def->bodyB,anchor, axis);
        return def;
    }else{
        utils::error(L,"JointDef should be table");
    }
}

b2WeldJointDef* b2WeldJointDef_from_table(lua_State *L){
    if (lua_istable(L, -1)) {
        b2WeldJointDef* def = new b2WeldJointDef();
        b2Vec2 anchor = extra_utils::table_get_b2vec_safe(L,"anchor","no anchor");
        lua_pushnil(L);  /* first key */
        while (lua_next(L, -2) != 0) {
            const char* key = lua_tostring(L, -2);
            switch (hash_string(key)) {
                case HASH_collideConnected:
                   def->collideConnected = lua_toboolean(L,-1);
                   break;
                case HASH_userData:
                   if (lua_istable(L ,-1)) {
                       lua_pushvalue(L, -1);
                       def->userData.pointer = luaL_ref(L,LUA_REGISTRYINDEX);
                   }else{
                       utils::error(L,"userdata can be only table or nil");
                   }
                   break;
                case HASH_bodyA:
                   def->bodyA = Body_get_userdata_safe(L,-1)->body;
                   break;
                case HASH_bodyB:
                   def->bodyB = Body_get_userdata_safe(L,-1)->body;
                   break;
                case HASH_type:
                   break;
                case HASH_anchor:
                   break;
                case HASH_localAnchorA:
                   def->localAnchorA = extra_utils::get_b2vec_safe(L,-1,"localAnchorA not v3");
                   break;
                case HASH_localAnchorB:
                   def->localAnchorB = extra_utils::get_b2vec_safe(L,-1,"localAnchorB  not v3");
                   break;
                case HASH_referenceAngle:
                    def->referenceAngle = luaL_checknumber(L,-1);
                    break;
                case HASH_stiffness:
                    def->stiffness = luaL_checknumber(L,-1);
                    break;
                case HASH_damping:
                    def->damping = luaL_checknumber(L,-1);
                    break;
                default:
                    lua_pushfstring(L, "unknown key:%s", key);
                    lua_error(L);
                    break;
            }
            /* removes 'value'; keeps 'key' for next iteration */
            lua_pop(L, 1);
        }
        if(def->bodyA == NULL) utils::error(L,"no bodyA");
        if(def->bodyB == NULL) utils::error(L,"no bodyB");
        def->Initialize(def->bodyA, def->bodyB, anchor);
        return def;
    }else{
        utils::error(L,"JointDef should be table");
    }
}

b2FrictionJointDef* b2FrictionJointDef_from_table(lua_State *L){
    if (lua_istable(L, -1)) {
        b2FrictionJointDef* def = new b2FrictionJointDef();
        b2Vec2 anchor = extra_utils::table_get_b2vec_safe(L,"anchor","no anchor");
        lua_pushnil(L);  /* first key */
        while (lua_next(L, -2) != 0) {
            const char* key = lua_tostring(L, -2);
            switch (hash_string(key)) {
                case HASH_collideConnected:
                   def->collideConnected = lua_toboolean(L,-1);
                   break;
                case HASH_userData:
                   if (lua_istable(L ,-1)) {
                       lua_pushvalue(L, -1);
                       def->userData.pointer = luaL_ref(L,LUA_REGISTRYINDEX);
                   }else{
                       utils::error(L,"userdata can be only table or nil");
                   }
                   break;
                case HASH_bodyA:
                   def->bodyA = Body_get_userdata_safe(L,-1)->body;
                   break;
                case HASH_bodyB:
                   def->bodyB = Body_get_userdata_safe(L,-1)->body;
                   break;
                case HASH_type:
                   break;
                case HASH_anchor:
                   break;
                case HASH_localAnchorA:
                   def->localAnchorA = extra_utils::get_b2vec_safe(L,-1,"localAnchorA not v3");
                   break;
                case HASH_localAnchorB:
                   def->localAnchorB = extra_utils::get_b2vec_safe(L,-1,"localAnchorB  not v3");
                   break;
                case HASH_maxForce:
                    def->maxForce = luaL_checknumber(L,-1);
                    break;
                case HASH_maxTorque:
                    def->maxTorque = luaL_checknumber(L,-1);
                    break;
                default:
                    lua_pushfstring(L, "unknown key:%s", key);
                    lua_error(L);
                    break;
            }
            /* removes 'value'; keeps 'key' for next iteration */
            lua_pop(L, 1);
        }
        if(def->bodyA == NULL) utils::error(L,"no bodyA");
        if(def->bodyB == NULL) utils::error(L,"no bodyB");
        def->Initialize(def->bodyA, def->bodyB, anchor);
        return def;
    }else{
        utils::error(L,"JointDef should be table");
    }
}

b2MotorJointDef* b2MotorJointDef_from_table(lua_State *L){
    if (lua_istable(L, -1)) {
        b2MotorJointDef* def = new b2MotorJointDef();
        lua_pushnil(L);  /* first key */
        while (lua_next(L, -2) != 0) {
            const char* key = lua_tostring(L, -2);
            switch (hash_string(key)) {
                case HASH_collideConnected:
                   def->collideConnected = lua_toboolean(L,-1);
                   break;
                case HASH_userData:
                   if (lua_istable(L ,-1)) {
                       lua_pushvalue(L, -1);
                       def->userData.pointer = luaL_ref(L,LUA_REGISTRYINDEX);
                   }else{
                       utils::error(L,"userdata can be only table or nil");
                   }
                   break;
                case HASH_bodyA:
                   def->bodyA = Body_get_userdata_safe(L,-1)->body;
                   break;
                case HASH_bodyB:
                   def->bodyB = Body_get_userdata_safe(L,-1)->body;
                   break;
                case HASH_type:
                   break;
                case HASH_linearOffset:
                    def->linearOffset = extra_utils::get_b2vec_safe(L,-1,"linearOffset not v3");
                    break;
                case HASH_angularOffset:
                    def->angularOffset = luaL_checknumber(L,-1);
                    break;
                case HASH_maxForce:
                    def->maxForce = luaL_checknumber(L,-1);
                    break;
                case HASH_maxTorque:
                    def->maxTorque = luaL_checknumber(L,-1);
                    break;
                case HASH_correctionFactor:
                    def->correctionFactor = luaL_checknumber(L,-1);
                    break;
                default:
                    lua_pushfstring(L, "unknown key:%s", key);
                    lua_error(L);
                    break;
            }
            /* removes 'value'; keeps 'key' for next iteration */
            lua_pop(L, 1);
        }
        if(def->bodyA == NULL) utils::error(L,"no bodyA");
        if(def->bodyB == NULL) utils::error(L,"no bodyB");
        def->Initialize(def->bodyA, def->bodyB);
        return def;
    }else{
        utils::error(L,"JointDef should be table");
    }
}

b2JointDef* b2JointDef_from_table(lua_State *L, int index){
    b2JointDef* def = NULL;
    if (lua_istable(L, index)) {
         lua_pushvalue(L,index);//def on top
        if(utils::table_is_number(L,"type")){
             b2JointType jointType =  static_cast<b2JointType>(utils::table_get_integer(L,"type",(int)b2JointType::e_unknownJoint));
             switch(jointType){
                case b2JointType::e_unknownJoint:
                    utils::error(L,"e_unknownJoint not supported");
                    break;
                case b2JointType::e_revoluteJoint:
                    def = b2RevoluteJointDef_from_table(L);
                    break;
                case b2JointType::e_prismaticJoint:
                    def = b2PrismaticJointDef_from_table(L);
                    break;
                case b2JointType::e_distanceJoint:
                    def = b2DistanceJointDef_from_table(L);
                    break;
                case b2JointType::e_pulleyJoint:
                    def = b2PulleyJointDef_from_table(L);
                    break;
                case b2JointType::e_mouseJoint:
                    def = b2MouseJointDef_from_table(L);
                    break;
                case b2JointType::e_gearJoint:
                    def = b2GearJointDef_from_table(L);
                    break;
                case b2JointType::e_wheelJoint:
                    def = b2WheelJointDef_from_table(L);
                    break;
                case b2JointType::e_weldJoint:
                    def = b2WeldJointDef_from_table(L);
                    break;
                case b2JointType::e_frictionJoint:
                    def = b2FrictionJointDef_from_table(L);
                    break;
                case b2JointType::e_motorJoint:
                    def = b2MotorJointDef_from_table(L);
                    break;
                case b2JointType::e_ropeJoint:
                    utils::error(L,"e_ropeJoint not supported");
                    break;
                default:
                    utils::error(L,"bad joint type");
                    break;
             }

        }else{
            utils::error(L,"JointDef should have type");
        }
        lua_pop(L,1);//remove def on top
    }else{
        utils::error(L,"JointDef should be table");
    }
    return def;
}



