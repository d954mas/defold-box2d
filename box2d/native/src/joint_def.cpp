#include "joint_def.h"
#include "joint.h"
#include "utils.h"
#include "shape.h"
#include "body.h"
#include <extra_utils.h>
#include <static_hash.h>

namespace box2dDefoldNE {

b2RevoluteJointDef* b2RevoluteJointDef_from_table(lua_State *L){
    if (lua_istable(L, -1)) {
        b2RevoluteJointDef* def = new b2RevoluteJointDef();
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
                    luaL_error(L, "unknown key:%s", key);
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

b2PrismaticJointDef* b2PrismaticJointDef_from_table(lua_State *L){
    if (lua_istable(L, -1)) {
        b2PrismaticJointDef* def = new b2PrismaticJointDef();
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
                    luaL_error(L, "unknown key:%s", key);
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

b2DistanceJointDef* b2DistanceJointDef_from_table(lua_State *L){
    if (lua_istable(L, -1)) {
        b2DistanceJointDef* def = new b2DistanceJointDef();
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
                    luaL_error(L, "unknown key:%s", key);
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

b2PulleyJointDef* b2PulleyJointDef_from_table(lua_State *L){
    if (lua_istable(L, -1)) {
        b2PulleyJointDef* def = new b2PulleyJointDef();
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
                    luaL_error(L, "unknown key:%s", key);
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
                    luaL_error(L, "unknown key:%s", key);
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
                    luaL_error(L, "unknown key:%s", key);
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
                    luaL_error(L, "unknown key:%s", key);
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

b2WeldJointDef* b2WeldJointDef_from_table(lua_State *L){
    if (lua_istable(L, -1)) {
        b2WeldJointDef* def = new b2WeldJointDef();
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
                    luaL_error(L, "unknown key:%s", key);
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

b2FrictionJointDef* b2FrictionJointDef_from_table(lua_State *L){
    if (lua_istable(L, -1)) {
        b2FrictionJointDef* def = new b2FrictionJointDef();
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
                    luaL_error(L, "unknown key:%s", key);
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
                    luaL_error(L, "unknown key:%s", key);
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



void b2JointDef_to_table(lua_State *L, b2JointDef* defBase){
    lua_newtable(L);

    lua_pushnumber(L, defBase->type);
    lua_setfield(L, -2, "type");

    b2Body *bodyA = defBase->bodyA;
    b2Body *bodyB = defBase->bodyB;
    uintptr_t bodyAPointer = NULL;
    uintptr_t bodyBPointer = NULL;
    if(bodyA != NULL){
        bodyAPointer = bodyA->GetUserData().pointer;
    }
    if(bodyB != NULL){
        bodyBPointer = bodyB->GetUserData().pointer;
    }

    if(bodyAPointer != NULL){
        ((Body*)bodyAPointer)->Push(L);
        lua_setfield(L, -2, "bodyA");
    }
    if(bodyBPointer != NULL){
        ((Body*)bodyBPointer)->Push(L);
        lua_setfield(L, -2, "bodyB");
    }

    lua_pushboolean(L,defBase->collideConnected);
    lua_setfield(L, -2, "collideConnected");

    //no add push for userdata. It can't exist here :)

    switch(defBase->type){
        case b2JointType::e_unknownJoint:
            utils::error(L,"e_unknownJoint not supported");
            break;
        case b2JointType::e_revoluteJoint:{
            b2RevoluteJointDef* def = (b2RevoluteJointDef*) defBase;
            utils::push_vector(L, def->localAnchorA.x, def->localAnchorA.y, 0);
            lua_setfield(L, -2, "localAnchorA");
            utils::push_vector(L, def->localAnchorB.x, def->localAnchorB.y, 0);
            lua_setfield(L, -2, "localAnchorB");
            lua_pushnumber(L,def->referenceAngle);
            lua_setfield(L, -2, "referenceAngle");
            lua_pushnumber(L,def->lowerAngle);
            lua_setfield(L, -2, "lowerAngle");
            lua_pushnumber(L,def->upperAngle);
            lua_setfield(L, -2, "upperAngle");
            lua_pushnumber(L,def->maxMotorTorque);
            lua_setfield(L, -2, "maxMotorTorque");
            lua_pushnumber(L,def->motorSpeed);
            lua_setfield(L, -2, "motorSpeed");
        	lua_pushboolean(L,def->enableLimit);
            lua_setfield(L, -2, "enableLimit");
        	lua_pushboolean(L,def->enableMotor);
            lua_setfield(L, -2, "enableMotor");
            break;
        }
        case b2JointType::e_prismaticJoint:{
            b2PrismaticJointDef* def = (b2PrismaticJointDef*) defBase;
            utils::push_vector(L, def->localAnchorA.x, def->localAnchorA.y, 0);
            lua_setfield(L, -2, "localAnchorA");
            utils::push_vector(L, def->localAnchorB.x, def->localAnchorB.y, 0);
            lua_setfield(L, -2, "localAnchorB");
            utils::push_vector(L, def->localAxisA.x, def->localAxisA.y, 0);
            lua_setfield(L, -2, "localAxisA");
            lua_pushnumber(L,def->referenceAngle);
            lua_setfield(L, -2, "referenceAngle");
        	lua_pushboolean(L,def->enableLimit);
            lua_setfield(L, -2, "enableLimit");
            lua_pushnumber(L,def->lowerTranslation);
            lua_setfield(L, -2, "lowerTranslation");
            lua_pushnumber(L,def->upperTranslation);
            lua_setfield(L, -2, "upperTranslation");
        	lua_pushboolean(L,def->enableMotor);
            lua_setfield(L, -2, "enableMotor");
            lua_pushnumber(L,def->maxMotorForce);
            lua_setfield(L, -2, "maxMotorForce");
            lua_pushnumber(L,def->motorSpeed);
            lua_setfield(L, -2, "motorSpeed");
            break;
        }
        case b2JointType::e_distanceJoint:{
            b2DistanceJointDef* def = (b2DistanceJointDef*) defBase;
            utils::push_vector(L, def->localAnchorA.x, def->localAnchorA.y, 0);
            lua_setfield(L, -2, "localAnchorA");
            utils::push_vector(L, def->localAnchorB.x, def->localAnchorB.y, 0);
            lua_setfield(L, -2, "localAnchorB");
            lua_pushnumber(L,def->length);
            lua_setfield(L, -2, "length");
            lua_pushnumber(L,def->minLength);
            lua_setfield(L, -2, "minLength");
            lua_pushnumber(L,def->maxLength);
            lua_setfield(L, -2, "maxLength");
            lua_pushnumber(L,def->stiffness);
            lua_setfield(L, -2, "stiffness");
            lua_pushnumber(L,def->damping);
            lua_setfield(L, -2, "damping");
            break;
        }
        case b2JointType::e_pulleyJoint:{
            b2PulleyJointDef* def = (b2PulleyJointDef*) defBase;
            utils::push_vector(L, def->groundAnchorA.x, def->groundAnchorA.y, 0);
            lua_setfield(L, -2, "groundAnchorA");
            utils::push_vector(L, def->groundAnchorB.x, def->groundAnchorB.y, 0);
            lua_setfield(L, -2, "groundAnchorB");
            utils::push_vector(L, def->localAnchorA.x, def->localAnchorA.y, 0);
            lua_setfield(L, -2, "localAnchorA");
            utils::push_vector(L, def->localAnchorB.x, def->localAnchorB.y, 0);
            lua_setfield(L, -2, "localAnchorB");
            lua_pushnumber(L,def->lengthA);
            lua_setfield(L, -2, "lengthA");
            lua_pushnumber(L,def->lengthB);
            lua_setfield(L, -2, "lengthB");
            lua_pushnumber(L,def->ratio);
            lua_setfield(L, -2, "ratio");
            break;
        }

        case b2JointType::e_mouseJoint:{
            b2MouseJointDef* def = (b2MouseJointDef*) defBase;
            utils::push_vector(L, def->target.x, def->target.y, 0);
            lua_setfield(L, -2, "target");
            lua_pushnumber(L,def->maxForce);
            lua_setfield(L, -2, "maxForce");
            lua_pushnumber(L,def->stiffness);
            lua_setfield(L, -2, "stiffness");
            lua_pushnumber(L,def->damping);
            lua_setfield(L, -2, "damping");
            break;
        }
        case b2JointType::e_gearJoint:{
            b2GearJointDef* def = (b2GearJointDef*) defBase;
            if(def->joint1 != nullptr){
                Joint* lua_joint = (Joint *)def->joint1->GetUserData().pointer;
                lua_joint->Push(L);
                lua_setfield(L, -2, "joint1");
            }
            if(def->joint2 != nullptr){
                Joint* lua_joint = (Joint *)def->joint2->GetUserData().pointer;
                lua_joint->Push(L);
                lua_setfield(L, -2, "joint2");
            }
            
            lua_pushnumber(L,def->ratio);
            lua_setfield(L, -2, "ratio");
            break;
        }
        case b2JointType::e_wheelJoint:{
            b2WheelJointDef* def = (b2WheelJointDef*) defBase;
            utils::push_vector(L, def->localAnchorA.x, def->localAnchorA.y, 0);
            lua_setfield(L, -2, "localAnchorA");
            utils::push_vector(L, def->localAnchorB.x, def->localAnchorB.y, 0);
            lua_setfield(L, -2, "localAnchorB");
            utils::push_vector(L, def->localAxisA.x, def->localAxisA.y, 0);
            lua_setfield(L, -2, "localAxisA");
            lua_pushboolean(L,def->enableLimit);
            lua_setfield(L, -2, "enableLimit");
            lua_pushnumber(L,def->lowerTranslation);
            lua_setfield(L, -2, "lowerTranslation");
            lua_pushnumber(L,def->upperTranslation);
            lua_setfield(L, -2, "upperTranslation");
            lua_pushboolean(L, def->enableMotor);
            lua_setfield(L, -2, "enableMotor");
            lua_pushnumber(L,def->maxMotorTorque);
            lua_setfield(L, -2, "maxMotorTorque");
            lua_pushnumber(L,def->motorSpeed);
            lua_setfield(L, -2, "motorSpeed");
            lua_pushnumber(L,def->stiffness);
            lua_setfield(L, -2, "stiffness");
            lua_pushnumber(L,def->damping);
            lua_setfield(L, -2, "damping");
            break;
        }
        case b2JointType::e_weldJoint:{
            b2WeldJointDef* def = (b2WeldJointDef*) defBase;
            utils::push_vector(L, def->localAnchorA.x, def->localAnchorA.y, 0);
            lua_setfield(L, -2, "localAnchorA");
            utils::push_vector(L, def->localAnchorB.x, def->localAnchorB.y, 0);
            lua_setfield(L, -2, "localAnchorB");
            lua_pushnumber(L,def->referenceAngle);
            lua_setfield(L, -2, "referenceAngle");
            lua_pushnumber(L,def->stiffness);
            lua_setfield(L, -2, "stiffness");
            lua_pushnumber(L,def->damping);
            lua_setfield(L, -2, "damping");
            break;
        }
        case b2JointType::e_frictionJoint:{
            b2FrictionJointDef* def = (b2FrictionJointDef*) defBase;
            utils::push_vector(L, def->localAnchorA.x, def->localAnchorA.y, 0);
            lua_setfield(L, -2, "localAnchorA");
            utils::push_vector(L, def->localAnchorB.x, def->localAnchorB.y, 0);
            lua_setfield(L, -2, "localAnchorB");
            lua_pushnumber(L,def->maxForce);
            lua_setfield(L, -2, "maxForce");
            lua_pushnumber(L,def->maxTorque);
            lua_setfield(L, -2, "maxTorque");
            break;
        }
        case b2JointType::e_motorJoint:{
            b2MotorJointDef* def = (b2MotorJointDef*) defBase;
            utils::push_vector(L, def->linearOffset.x, def->linearOffset.y, 0);
            lua_setfield(L, -2, "linearOffset");
            lua_pushnumber(L,def->angularOffset);
            lua_setfield(L, -2, "angularOffset");
            lua_pushnumber(L,def->maxForce);
            lua_setfield(L, -2, "maxForce");
            lua_pushnumber(L,def->maxTorque);
            lua_setfield(L, -2, "maxTorque");
            lua_pushnumber(L,def->correctionFactor);
            lua_setfield(L, -2, "correctionFactor");
            break;
        }
        case b2JointType::e_ropeJoint:
            utils::error(L,"e_ropeJoint not supported");
            break;
        default:
            utils::error(L,"bad joint type");
            break;
    }
}

}

