#include "joint.h"
#include "utils.h"
#include "body.h"

#define META_NAME "Box2d::JointClass"
#define USERDATA_TYPE "joint"

namespace box2dDefoldNE {

Joint::Joint(b2Joint *j): BaseUserData(USERDATA_TYPE){
    user_data_ref = LUA_REFNIL;
    joint = j;
    b2JointUserData& userdata = joint->GetUserData();
    userdata.pointer = (uintptr_t)(void*) this;

    this->box2dObj = j;
    this->metatable_name = META_NAME;
}

Joint::~Joint() {

}

Joint* Joint_get_userdata_safe(lua_State *L, int index) {
    Joint *lua_joint = (Joint*) BaseUserData_get_userdata(L, index, USERDATA_TYPE);
	return lua_joint;
}

/// Get the type of the concrete joint.
static int GetType(lua_State *L){ //b2JointType GetType() const;
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    lua_pushnumber(L, joint->joint->GetType());
    return 1;
};

/// Get the first body attached to this joint.
static int GetBodyA(lua_State *L){ //b2Body* GetBodyA();
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    Body *body = (Body *)joint->joint->GetBodyA()->GetUserData().pointer;
    body->Push(L);
    return 1;
};

/// Get the second body attached to this joint.
static int GetBodyB(lua_State *L){ //b2Body* GetBodyB();
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    Body *body = (Body *)joint->joint->GetBodyB()->GetUserData().pointer;
    body->Push(L);
    return 1;
};

/// Get the anchor point on bodyA in world coordinates.
static int GetAnchorA(lua_State *L){ //virtual b2Vec2 GetAnchorA() const = 0;
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    b2Vec2 result = joint->joint->GetAnchorA();
    utils::push_vector(L, result.x, result.y, 0);
    return 1;
};

/// Get the anchor point on bodyB in world coordinates.
static int GetAnchorB(lua_State *L){ //virtual b2Vec2 GetAnchorB() const = 0;
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    b2Vec2 result = joint->joint->GetAnchorB();
    utils::push_vector(L, result.x, result.y, 0);
    return 1;
};

/// Get the reaction force on bodyB at the joint anchor in Newtons.
static int GetReactionForce(lua_State *L){ ////virtual b2Vec2 GetReactionForce(float inv_dt) const = 0;
    utils::check_arg_count(L, 2);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float inv_dt = luaL_checknumber(L,2);
    b2Vec2 result = joint->joint->GetReactionForce(inv_dt);
    utils::push_vector(L, result.x, result.y, 0);
    return 1;
};

/// Get the reaction force on bodyB at the joint anchor in Newtons.
static int GetReactionTorque(lua_State *L){ ////virtual float GetReactionTorque(float inv_dt) const = 0;
    utils::check_arg_count(L, 2);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float inv_dt = luaL_checknumber(L,2);
    lua_pushnumber(L, joint->joint->GetReactionTorque(inv_dt));
    return 1;
};


/// Get the next joint the world joint list.
static int GetNext(lua_State *L){ //const b2Joint* GetNext() const;
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    b2Joint *joint_new = joint->joint->GetNext();
    if(joint_new == NULL){
        lua_pushnil(L);
    }else{
        Joint* lua_joint = (Joint *)joint_new->GetUserData().pointer;
        lua_joint->Push(L);
    }
    return 1;
};

static int GetUserData(lua_State *L){//b2BodyUserData& GetUserData () Get the user data pointer that was provided in the body definition.
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    lua_rawgeti(L,LUA_REGISTRYINDEX,joint->user_data_ref);
    return 1;
}

static int SetUserData(lua_State *L){//void SetUserData(void *data) Set the user data. Use this to store your application specific data.
    utils::check_arg_count(L, 2);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    if (lua_istable(L, 2)) {
        utils::unref(L, joint->user_data_ref);
        joint->user_data_ref = luaL_ref(L,LUA_REGISTRYINDEX);
    }else if (lua_isnil(L, 2)){
        utils::unref(L, joint->user_data_ref);
        joint->user_data_ref = LUA_REFNIL;
    }else {
        utils::error(L,"userdata can be only table or nil");
    }
    return 0;
}

/// Short-cut function to determine if either body is enabled.
static int IsEnabled(lua_State *L){ //bool IsEnabled() const;
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    lua_pushboolean(L,joint->joint->IsEnabled());
    return 1;
}

/// Get collide connected.
/// Note: modifying the collide connect flag won't work correctly because
/// the flag is only checked when fixture AABBs begin to overlap.
static int GetCollideConnected(lua_State *L){ //bool GetCollideConnected() const;
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    lua_pushboolean(L,joint->joint->GetCollideConnected());
    return 1;
}

/// Dump this joint to the log file.
static int Dump(lua_State *L){ //virtual void Dump() { b2Dump("// Dump is not supported for this joint type.\n"); }
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    joint->joint->Dump();
    return 0;
}

/// Shift the origin for any points stored in world coordinates.
static int ShiftOrigin(lua_State *L){ //virtual void ShiftOrigin(const b2Vec2& newOrigin) { B2_NOT_USED(newOrigin);  }
    utils::check_arg_count(L, 2);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    b2Vec2 newOrigin = extra_utils::get_b2vec_safe(L,-1,"newOrigin not vector3");
    joint->joint->ShiftOrigin(newOrigin);
    return 0;
}

//NOT IMPL
/// Debug draw this joint
//virtual void Draw(b2Draw* draw) const;


///ALL JOINTS FUNCTIONS

/// The local anchor point relative to bodyA's origin.
static int SwitchExample(lua_State *L){ //const b2Vec2& GetLocalAnchorA() const { return m_localAnchorA; }
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    b2JointType result;
    switch(joint->joint->GetType()){
        case b2JointType::e_revoluteJoint:
            result = ((b2RevoluteJoint*)joint->joint)->GetType();
            break;
        case b2JointType::e_prismaticJoint:
            result = ((b2PrismaticJoint*)joint->joint)->GetType();
            break;
        case b2JointType::e_distanceJoint:
            result = ((b2DistanceJoint*)joint->joint)->GetType();
            break;
        case b2JointType::e_pulleyJoint:
            result = ((b2PulleyJoint*)joint->joint)->GetType();
            break;
        case b2JointType::e_mouseJoint:
            result = ((b2MouseJoint*)joint->joint)->GetType();
            break;
        case b2JointType::e_gearJoint:
            result = ((b2GearJoint*)joint->joint)->GetType();
            break;
        case b2JointType::e_wheelJoint:
            result = ((b2WheelJoint*)joint->joint)->GetType();
            break;
        case b2JointType::e_weldJoint:
            result = ((b2WeldJoint*)joint->joint)->GetType();
            break;
        case b2JointType::e_frictionJoint:
            result = ((b2FrictionJoint*)joint->joint)->GetType();
            break;
        case b2JointType::e_motorJoint:
            result = ((b2MotorJoint*)joint->joint)->GetType();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    return 1;
}

/// The local anchor point relative to bodyA's origin.
static int GetLocalAnchorA(lua_State *L){ //const b2Vec2& GetLocalAnchorA() const { return m_localAnchorA; }
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    b2Vec2 result;
    switch(joint->joint->GetType()){
        case b2JointType::e_revoluteJoint:
            result = ((b2RevoluteJoint*)joint->joint)->GetLocalAnchorA();
            break;
        case b2JointType::e_prismaticJoint:
            result = ((b2PrismaticJoint*)joint->joint)->GetLocalAnchorA();
            break;
        case b2JointType::e_distanceJoint:
            result = ((b2DistanceJoint*)joint->joint)->GetLocalAnchorA();
            break;
        case b2JointType::e_wheelJoint:
            result = ((b2WheelJoint*)joint->joint)->GetLocalAnchorA();
            break;
        case b2JointType::e_weldJoint:
            result = ((b2WeldJoint*)joint->joint)->GetLocalAnchorA();
            break;
        case b2JointType::e_frictionJoint:
            result = ((b2FrictionJoint*)joint->joint)->GetLocalAnchorA();
            break;
        default:
            utils::error(L,"function not supported");
            break;
        }

    utils::push_vector(L, result.x, result.y, 0);
    return 1;
}

/// The local anchor point relative to bodyA's origin.
static int GetLocalAnchorB(lua_State *L){ //const b2Vec2& GetLocalAnchorA() const { return m_localAnchorA; }
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    b2Vec2 result;
    switch(joint->joint->GetType()){
        case b2JointType::e_revoluteJoint:
            result = ((b2RevoluteJoint*)joint->joint)->GetLocalAnchorB();
            break;
        case b2JointType::e_prismaticJoint:
            result = ((b2PrismaticJoint*)joint->joint)->GetLocalAnchorB();
            break;
        case b2JointType::e_distanceJoint:
            result = ((b2DistanceJoint*)joint->joint)->GetLocalAnchorB();
            break;
        case b2JointType::e_wheelJoint:
            result = ((b2WheelJoint*)joint->joint)->GetLocalAnchorB();
            break;
        case b2JointType::e_weldJoint:
            result = ((b2WeldJoint*)joint->joint)->GetLocalAnchorB();
            break;
        case b2JointType::e_frictionJoint:
            result = ((b2FrictionJoint*)joint->joint)->GetLocalAnchorB();
            break;
        default:
            utils::error(L,"function not supported");
            break;
        }

    utils::push_vector(L, result.x, result.y, 0);
    return 1;
}

static int GetReferenceAngle(lua_State *L){ //float GetReferenceAngle()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_revoluteJoint:
            result = ((b2RevoluteJoint*)joint->joint)->GetReferenceAngle();
            break;
        case b2JointType::e_prismaticJoint:
            result = ((b2PrismaticJoint*)joint->joint)->GetReferenceAngle();
            break;
        case b2JointType::e_weldJoint:
            result = ((b2WeldJoint*)joint->joint)->GetReferenceAngle();
            break;
        default:
            utils::error(L,"function not supported");
            break;
        }

    lua_pushnumber(L, result);
    return 1;
}

static int GetJointAngle(lua_State *L){ //float GetJointAngle()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_revoluteJoint:
            result = ((b2RevoluteJoint*)joint->joint)->GetJointAngle();
            break;
        case b2JointType::e_wheelJoint:
            result = ((b2WheelJoint*)joint->joint)->GetJointAngle();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}

static int GetJointSpeed(lua_State *L){ //float GetJointSpeed()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_revoluteJoint:
            result = ((b2RevoluteJoint*)joint->joint)->GetJointSpeed();
            break;
        case b2JointType::e_prismaticJoint:
            result = ((b2PrismaticJoint*)joint->joint)->GetJointSpeed();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}


static int IsLimitEnabled(lua_State *L){ //bool IsLimitEnabled()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    bool result;
    switch(joint->joint->GetType()){
        case b2JointType::e_revoluteJoint:
            result = ((b2RevoluteJoint*)joint->joint)->IsLimitEnabled();
            break;
        case b2JointType::e_prismaticJoint:
            result = ((b2PrismaticJoint*)joint->joint)->IsLimitEnabled();
            break;
        case b2JointType::e_wheelJoint:
            result = ((b2WheelJoint*)joint->joint)->IsLimitEnabled();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushboolean(L, result);
    return 1;
}

static int EnableLimit(lua_State *L){ //bool EnableLimit()
    utils::check_arg_count(L, 2);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    bool limit = lua_toboolean(L, 2);
    switch(joint->joint->GetType()){
        case b2JointType::e_revoluteJoint:
            ((b2RevoluteJoint*)joint->joint)->EnableLimit(limit);
            break;
        case b2JointType::e_prismaticJoint:
            ((b2PrismaticJoint*)joint->joint)->EnableLimit(limit);
            break;
        case b2JointType::e_wheelJoint:
            ((b2WheelJoint*)joint->joint)->EnableLimit(limit);
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    return 0;
}

static int GetLowerLimit(lua_State *L){ //float GetLowerLimit()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_revoluteJoint:
            result = ((b2RevoluteJoint*)joint->joint)->GetLowerLimit();
            break;
        case b2JointType::e_prismaticJoint:
            result = ((b2PrismaticJoint*)joint->joint)->GetLowerLimit();
            break;
        case b2JointType::e_wheelJoint:
            result = ((b2WheelJoint*)joint->joint)->GetLowerLimit();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}

static int GetUpperLimit(lua_State *L){ //float GetUpperLimit()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_revoluteJoint:
            result = ((b2RevoluteJoint*)joint->joint)->GetUpperLimit();
            break;
        case b2JointType::e_prismaticJoint:
            result = ((b2PrismaticJoint*)joint->joint)->GetUpperLimit();
            break;
        case b2JointType::e_wheelJoint:
            result = ((b2WheelJoint*)joint->joint)->GetUpperLimit();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}

static int SetLimits(lua_State *L){ //void SetLimits(float lower, float upper)
    utils::check_arg_count(L, 3);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float lower = luaL_checknumber(L, 2);
    float upper = luaL_checknumber(L, 3);
    switch(joint->joint->GetType()){
        case b2JointType::e_revoluteJoint:
            ((b2RevoluteJoint*)joint->joint)->SetLimits(lower, upper);
            break;
        case b2JointType::e_prismaticJoint:
            ((b2PrismaticJoint*)joint->joint)->SetLimits(lower, upper);
            break;
        case b2JointType::e_wheelJoint:
            ((b2WheelJoint*)joint->joint)->SetLimits(lower, upper);
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    return 0;
}

static int IsMotorEnabled(lua_State *L){ //bool IsMotorEnabled()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    bool result;
    switch(joint->joint->GetType()){
        case b2JointType::e_revoluteJoint:
            result = ((b2RevoluteJoint*)joint->joint)->IsMotorEnabled();
            break;
        case b2JointType::e_prismaticJoint:
            result = ((b2PrismaticJoint*)joint->joint)->IsMotorEnabled();
            break;
        case b2JointType::e_wheelJoint:
            result = ((b2WheelJoint*)joint->joint)->IsMotorEnabled();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushboolean(L, result);
    return 1;
}

static int EnableMotor(lua_State *L){ //EnableMotor(bool flag)
    utils::check_arg_count(L, 2);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    bool flag = lua_toboolean(L, 2);
    switch(joint->joint->GetType()){
        case b2JointType::e_revoluteJoint:
            ((b2RevoluteJoint*)joint->joint)->EnableMotor(flag);
            break;
        case b2JointType::e_prismaticJoint:
            ((b2PrismaticJoint*)joint->joint)->EnableMotor(flag);
            break;
        case b2JointType::e_wheelJoint:
            ((b2WheelJoint*)joint->joint)->EnableMotor(flag);
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    return 0;
}

static int SetMotorSpeed(lua_State *L){ //SetMotorSpeed(float speed)
    utils::check_arg_count(L, 2);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float speed = luaL_checknumber(L, 2);
    switch(joint->joint->GetType()){
        case b2JointType::e_revoluteJoint:
            ((b2RevoluteJoint*)joint->joint)->SetMotorSpeed(speed);
            break;
        case b2JointType::e_prismaticJoint:
            ((b2PrismaticJoint*)joint->joint)->SetMotorSpeed(speed);
            break;
        case b2JointType::e_wheelJoint:
            ((b2WheelJoint*)joint->joint)->SetMotorSpeed(speed);
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    return 0;
}

static int GetMotorSpeed(lua_State *L){ //float GetMotorSpeed()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_revoluteJoint:
            result = ((b2RevoluteJoint*)joint->joint)->GetMotorSpeed();
            break;
        case b2JointType::e_prismaticJoint:
            result = ((b2PrismaticJoint*)joint->joint)->GetMotorSpeed();
            break;
        case b2JointType::e_wheelJoint:
            result = ((b2WheelJoint*)joint->joint)->GetMotorSpeed();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}

static int SetMaxMotorTorque(lua_State *L){ //SetMaxMotorTorque(float torque)
    utils::check_arg_count(L, 2);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float torque = luaL_checknumber(L, 2);
    switch(joint->joint->GetType()){
        case b2JointType::e_revoluteJoint:
            ((b2RevoluteJoint*)joint->joint)->SetMaxMotorTorque(torque);
            break;
        case b2JointType::e_wheelJoint:
            ((b2WheelJoint*)joint->joint)->SetMaxMotorTorque(torque);
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    return 0;
}

static int GetMaxMotorTorque(lua_State *L){ //float GetMaxMotorTorque()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_revoluteJoint:
            result = ((b2RevoluteJoint*)joint->joint)->GetMaxMotorTorque();
            break;
        case b2JointType::e_wheelJoint:
            result = ((b2WheelJoint*)joint->joint)->GetMaxMotorTorque();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}

static int GetMotorTorque(lua_State *L){ //float GetMotorTorque(float inv_dt)
    utils::check_arg_count(L, 2);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float inv_dt = luaL_checknumber(L, 2);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_revoluteJoint:
            result = ((b2RevoluteJoint*)joint->joint)->GetMotorTorque(inv_dt);
            break;
        case b2JointType::e_wheelJoint:
            result = ((b2WheelJoint*)joint->joint)->GetMotorTorque(inv_dt);
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}

static int GetLocalAxisA(lua_State *L){ //b2Vec2& GetLocalAxisA()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    b2Vec2 result;
    switch(joint->joint->GetType()){
        case b2JointType::e_prismaticJoint:
            result = ((b2PrismaticJoint*)joint->joint)->GetLocalAxisA();
            break;
        case b2JointType::e_wheelJoint:
            result = ((b2WheelJoint*)joint->joint)->GetLocalAxisA();
            break;
        default:
            utils::error(L,"function not supported");
            break;
        }

    utils::push_vector(L, result.x, result.y, 0);
    return 1;
}

static int GetJointTranslation(lua_State *L){ //float GetJointTranslation()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_prismaticJoint:
            result = ((b2PrismaticJoint*)joint->joint)->GetJointTranslation();
            break;
        case b2JointType::e_wheelJoint:
            result = ((b2WheelJoint*)joint->joint)->GetJointTranslation();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}

static int SetMaxMotorForce(lua_State *L){ //SetMaxMotorForce(float force)
    utils::check_arg_count(L, 2);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float force = luaL_checknumber(L, 2);
    switch(joint->joint->GetType()){
        case b2JointType::e_prismaticJoint:
            ((b2PrismaticJoint*)joint->joint)->SetMaxMotorForce(force);
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    return 0;
}

static int GetMaxMotorForce(lua_State *L){ //float GetMaxMotorForce()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_prismaticJoint:
            result = ((b2PrismaticJoint*)joint->joint)->GetMaxMotorForce();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}

static int GetMotorForce(lua_State *L){ //float GetMotorForce(float inv_dt)
    utils::check_arg_count(L, 2);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float inv_dt = luaL_checknumber(L, 2);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_prismaticJoint:
            result = ((b2PrismaticJoint*)joint->joint)->GetMotorForce(inv_dt);
            break;;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}

static int GetLength(lua_State *L){ //float GetLength()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_distanceJoint:
            result = ((b2DistanceJoint*)joint->joint)->GetLength();
            break;;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}
static int SetLength(lua_State *L){ //float SetLength(float length)
    utils::check_arg_count(L, 2);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float length = luaL_checknumber(L, 2);
    switch(joint->joint->GetType()){
        case b2JointType::e_distanceJoint:
            ((b2DistanceJoint*)joint->joint)->SetLength(length);
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    return 0;
}

static int GetMinLength(lua_State *L){ //float GetMinLength()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_distanceJoint:
            result = ((b2DistanceJoint*)joint->joint)->GetMinLength();
            break;;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}
static int SetMinLength(lua_State *L){ //float SetMinLength(float minLength)
    utils::check_arg_count(L, 2);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float length = luaL_checknumber(L, 2);
    switch(joint->joint->GetType()){
        case b2JointType::e_distanceJoint:
            ((b2DistanceJoint*)joint->joint)->SetMinLength(length);
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    return 0;
}

static int GetMaxLength(lua_State *L){ //float GetMaxLength()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_distanceJoint:
            result = ((b2DistanceJoint*)joint->joint)->GetMaxLength();
            break;;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}
static int SetMaxLength(lua_State *L){ //float SetMaxLength(float maxLength)
    utils::check_arg_count(L, 2);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float length = luaL_checknumber(L, 2);
    switch(joint->joint->GetType()){
        case b2JointType::e_distanceJoint:
            ((b2DistanceJoint*)joint->joint)->SetMaxLength(length);
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    return 0;
}

static int GetCurrentLength(lua_State *L){ //float GetCurrentLength()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_distanceJoint:
            result = ((b2DistanceJoint*)joint->joint)->GetCurrentLength();
            break;;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}

static int GetStiffness(lua_State *L){ //float GetStiffness()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_distanceJoint:
            result = ((b2DistanceJoint*)joint->joint)->GetStiffness();
            break;
        case b2JointType::e_mouseJoint:
            result = ((b2MouseJoint*)joint->joint)->GetStiffness();
            break;
        case b2JointType::e_wheelJoint:
            result = ((b2WheelJoint*)joint->joint)->GetStiffness();
            break;
        case b2JointType::e_weldJoint:
            result = ((b2WeldJoint*)joint->joint)->GetStiffness();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}
static int SetStiffness(lua_State *L){ //float SetStiffness(float stiffness)
    utils::check_arg_count(L, 2);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float stiffness = luaL_checknumber(L, 2);
    switch(joint->joint->GetType()){
        case b2JointType::e_distanceJoint:
            ((b2DistanceJoint*)joint->joint)->SetStiffness(stiffness);
            break;
        case b2JointType::e_mouseJoint:
            ((b2MouseJoint*)joint->joint)->SetStiffness(stiffness);
            break;
        case b2JointType::e_wheelJoint:
            ((b2WheelJoint*)joint->joint)->SetStiffness(stiffness);
            break;
        case b2JointType::e_weldJoint:
            ((b2WeldJoint*)joint->joint)->SetStiffness(stiffness);
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    return 0;
}

static int GetDamping(lua_State *L){ //float GetDamping()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_distanceJoint:
            result = ((b2DistanceJoint*)joint->joint)->GetDamping();
            break;
        case b2JointType::e_mouseJoint:
                result = ((b2MouseJoint*)joint->joint)->GetDamping();
                break;
        case b2JointType::e_wheelJoint:
                result = ((b2WheelJoint*)joint->joint)->GetDamping();
                break;
        case b2JointType::e_weldJoint:
                result = ((b2WeldJoint*)joint->joint)->GetDamping();
                break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}
static int SetDamping(lua_State *L){ //float SetDamping(float damping)
    utils::check_arg_count(L, 2);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float damping = luaL_checknumber(L, 2);
    switch(joint->joint->GetType()){
        case b2JointType::e_distanceJoint:
            ((b2DistanceJoint*)joint->joint)->SetDamping(damping);
            break;
        case b2JointType::e_mouseJoint:
            ((b2MouseJoint*)joint->joint)->SetDamping(damping);
            break;
        case b2JointType::e_wheelJoint:
            ((b2WheelJoint*)joint->joint)->SetDamping(damping);
            break;
        case b2JointType::e_weldJoint:
            ((b2WeldJoint*)joint->joint)->SetDamping(damping);
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    return 0;
}

static int GetGroundAnchorA(lua_State *L){ //const b2Vec2& GetGroundAnchorA()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    b2Vec2 result;
    switch(joint->joint->GetType()){
        case b2JointType::e_pulleyJoint:
            result = ((b2PulleyJoint*)joint->joint)->GetGroundAnchorA();
            break;
        default:
            utils::error(L,"function not supported");
            break;
        }

    utils::push_vector(L, result.x, result.y, 0);
    return 1;
}

static int GetGroundAnchorB(lua_State *L){ //const b2Vec2& GetGroundAnchorB()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    b2Vec2 result;
    switch(joint->joint->GetType()){
        case b2JointType::e_pulleyJoint:
            result = ((b2PulleyJoint*)joint->joint)->GetGroundAnchorB();
            break;
        default:
            utils::error(L,"function not supported");
            break;
        }

    utils::push_vector(L, result.x, result.y, 0);
    return 1;
}

static int SetMaxForce(lua_State *L){ //SetMaxForce(float force)
    utils::check_arg_count(L, 2);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float force = luaL_checknumber(L, 2);
    switch(joint->joint->GetType()){
        case b2JointType::e_mouseJoint:
            ((b2MouseJoint*)joint->joint)->SetMaxForce(force);
            break;
        case b2JointType::e_frictionJoint:
            ((b2FrictionJoint*)joint->joint)->SetMaxForce(force);
            break;
        case b2JointType::e_motorJoint:
            ((b2MotorJoint*)joint->joint)->SetMaxForce(force);
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    return 0;
}

static int GetMaxForce(lua_State *L){ //float GetMaxForce()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_mouseJoint:
            result = ((b2MouseJoint*)joint->joint)->GetMaxForce();
            break;
        case b2JointType::e_frictionJoint:
            result = ((b2FrictionJoint*)joint->joint)->GetMaxForce();
            break;
        case b2JointType::e_motorJoint:
            result = ((b2MotorJoint*)joint->joint)->GetMaxForce();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}


static int GetLengthA(lua_State *L){ //float GetLengthA()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_pulleyJoint:
            result = ((b2PulleyJoint*)joint->joint)->GetLengthA();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}

static int GetLengthB(lua_State *L){ //float GetLengthB()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_pulleyJoint:
            result = ((b2PulleyJoint*)joint->joint)->GetLengthB();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}

static int SetRatio(lua_State *L){ //float SetRatio()
    utils::check_arg_count(L, 2);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float ratio = luaL_checknumber(L, 2);
    switch(joint->joint->GetType()){
        case b2JointType::e_gearJoint:
            ((b2GearJoint*)joint->joint)->SetRatio(ratio);
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    return 0;
}

static int GetRatio(lua_State *L){ //float GetRatio()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_pulleyJoint:
            result = ((b2PulleyJoint*)joint->joint)->GetRatio();
            break;
        case b2JointType::e_gearJoint:
            result = ((b2GearJoint*)joint->joint)->GetRatio();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}

static int GetCurrentLengthA(lua_State *L){ //float GetCurrentLengthA()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_pulleyJoint:
            result = ((b2PulleyJoint*)joint->joint)->GetCurrentLengthA();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}

static int GetCurrentLengthB(lua_State *L){ //float GetCurrentLengthB()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_pulleyJoint:
            result = ((b2PulleyJoint*)joint->joint)->GetCurrentLengthB();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}

static int SetTarget(lua_State *L){ //SetTarget(const b2Vec2& target)
    utils::check_arg_count(L, 2);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    b2Vec2 target = extra_utils::get_b2vec_safe(L,2,"target not vector3");
    switch(joint->joint->GetType()){
        case b2JointType::e_mouseJoint:
            ((b2MouseJoint*)joint->joint)->SetTarget(target);
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    return 0;
}

static int GetTarget(lua_State *L){ //const b2Vec2& GetTarget()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    b2Vec2 result;
    switch(joint->joint->GetType()){
        case b2JointType::e_mouseJoint:
            result = ((b2MouseJoint*)joint->joint)->GetTarget();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }

    utils::push_vector(L, result.x, result.y, 0);
    return 1;
}

static int GetJoint1(lua_State *L){ //b2Joint*& GetJoint1()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    b2Joint* result = NULL;
    switch(joint->joint->GetType()){
        case b2JointType::e_gearJoint:
            result = ((b2GearJoint*)joint->joint)->GetJoint1();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    if(result == NULL){
        lua_pushnil(L);
    }else{
        Joint* lua_joint = (Joint *)result->GetUserData().pointer;
        lua_joint->Push(L);
    }
    return 1;
}

static int GetJoint2(lua_State *L){ //b2Joint*& GetJoint2()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    b2Joint* result = NULL;
    switch(joint->joint->GetType()){
        case b2JointType::e_gearJoint:
            result = ((b2GearJoint*)joint->joint)->GetJoint2();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    if(result == NULL){
        lua_pushnil(L);
    }else{
        Joint* lua_joint = (Joint *)result->GetUserData().pointer;
        lua_joint->Push(L);
    }
    return 1;
}

static int GetJointLinearSpeed(lua_State *L){ //float GetJointLinearSpeed()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_wheelJoint:
            result = ((b2WheelJoint*)joint->joint)->GetJointLinearSpeed();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}

static int GetJointAngularSpeed(lua_State *L){ //float GetJointAngularSpeed()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_wheelJoint:
            result = ((b2WheelJoint*)joint->joint)->GetJointAngularSpeed();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}

static int SetMaxTorque(lua_State *L){ //SetMaxTorque(float torque)
    utils::check_arg_count(L, 2);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float torque = luaL_checknumber(L, 2);
    switch(joint->joint->GetType()){
        case b2JointType::e_frictionJoint:
            ((b2FrictionJoint*)joint->joint)->SetMaxTorque(torque);
            break;
        case b2JointType::e_motorJoint:
                ((b2MotorJoint*)joint->joint)->SetMaxTorque(torque);
                break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    return 0;
}

static int GetMaxTorque(lua_State *L){ //float GetMaxTorque()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_frictionJoint:
            result = ((b2FrictionJoint*)joint->joint)->GetMaxTorque();
            break;
        case b2JointType::e_motorJoint:
            result = ((b2MotorJoint*)joint->joint)->GetMaxTorque();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}

static int SetLinearOffset(lua_State *L){ //SetLinearOffset(const b2Vec2& linearOffset)
    utils::check_arg_count(L, 2);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    b2Vec2 linearOffset = extra_utils::get_b2vec_safe(L,2,"linearOffset not vector3");
    switch(joint->joint->GetType()){
        case b2JointType::e_motorJoint:
            ((b2MotorJoint*)joint->joint)->SetLinearOffset(linearOffset);
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    return 0;
}

static int GetLinearOffset(lua_State *L){ //const b2Vec2& GetLinearOffset()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    b2Vec2 result;
    switch(joint->joint->GetType()){
        case b2JointType::e_motorJoint:
            result = ((b2MotorJoint*)joint->joint)->GetLinearOffset();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }

    utils::push_vector(L, result.x, result.y, 0);
    return 1;
}

static int SetAngularOffset(lua_State *L){ //SetAngularOffset(float angularOffset)
    utils::check_arg_count(L, 2);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float angularOffset = luaL_checknumber(L, 2);
    switch(joint->joint->GetType()){
        case b2JointType::e_motorJoint:
            ((b2MotorJoint*)joint->joint)->SetAngularOffset(angularOffset);
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    return 0;
}

static int GetAngularOffset(lua_State *L){ //float GetAngularOffset()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_motorJoint:
            result = ((b2MotorJoint*)joint->joint)->GetAngularOffset();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}

static int SetCorrectionFactor(lua_State *L){ //SetCorrectionFactor(float factor)
    utils::check_arg_count(L, 2);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float factor = luaL_checknumber(L, 2);
    switch(joint->joint->GetType()){
        case b2JointType::e_motorJoint:
            ((b2MotorJoint*)joint->joint)->SetCorrectionFactor(factor);
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    return 0;
}

static int GetCorrectionFactor(lua_State *L){ //float GetCorrectionFactor()
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    float result;
    switch(joint->joint->GetType()){
        case b2JointType::e_motorJoint:
            result = ((b2MotorJoint*)joint->joint)->GetCorrectionFactor();
            break;
        default:
            utils::error(L,"function not supported");
            break;
    }
    lua_pushnumber(L, result);
    return 1;
}

static int ToString(lua_State *L){
    utils::check_arg_count(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 1);
    lua_pushfstring( L, "b2Joint[%p]",(void *) joint->joint);
	return 1;
}

void JointInitMetaTable(lua_State *L){
    int top = lua_gettop(L);

    luaL_Reg functions[] = {
        {"GetType",GetType},
        {"GetBodyA",GetBodyA},
        {"GetBodyB",GetBodyB},
        {"GetAnchorA",GetAnchorA},
        {"GetAnchorB",GetAnchorB},
        {"GetReactionForce",GetReactionForce},
        {"GetReactionTorque",GetReactionTorque},
        {"GetNext",GetNext},
        {"GetUserData",GetUserData},
        {"SetUserData",SetUserData},
        {"IsEnabled",IsEnabled},
        {"GetCollideConnected",GetCollideConnected},
        {"Dump",Dump},
        {"ShiftOrigin",ShiftOrigin},

        {"GetLocalAnchorA",GetLocalAnchorA},
        {"GetLocalAnchorB",GetLocalAnchorB},
        {"GetReferenceAngle",GetReferenceAngle},
        {"GetJointSpeed",GetJointSpeed},
        {"GetJointAngle",GetJointAngle},
        {"IsLimitEnabled",IsLimitEnabled},
        {"EnableLimit",EnableLimit},
        {"GetLowerLimit",GetLowerLimit},
        {"GetUpperLimit",GetUpperLimit},
        {"SetLimits",SetLimits},
        {"IsMotorEnabled",IsMotorEnabled},
        {"EnableMotor",EnableMotor},
        {"GetMotorSpeed",GetMotorSpeed},
        {"SetMotorSpeed",SetMotorSpeed},
        {"SetMaxMotorTorque",SetMaxMotorTorque},
        {"GetMaxMotorTorque",GetMaxMotorTorque},
        {"GetMotorTorque",GetMotorTorque},
        {"GetLocalAxisA",GetLocalAxisA},
        {"GetJointTranslation",GetJointTranslation},
        {"SetMaxMotorForce",SetMaxMotorForce},
        {"GetMaxMotorForce",GetMaxMotorForce},
        {"GetMotorForce",GetMotorForce},
        {"GetLength",GetLength},
        {"SetLength",SetLength},
        {"GetMinLength",GetMinLength},
        {"SetMinLength",SetMinLength},
        {"GetMaxLength",GetMaxLength},
        {"SetMaxLength",SetMaxLength},
        {"GetCurrentLength",GetCurrentLength},
        {"SetStiffness",SetStiffness},
        {"GetStiffness",GetStiffness},
        {"SetDamping",SetDamping},
        {"GetDamping",GetDamping},
        {"GetGroundAnchorA",GetGroundAnchorA},
        {"GetGroundAnchorB",GetGroundAnchorB},
        {"GetLengthA",GetLengthA},
        {"GetLengthB",GetLengthB},
        {"GetRatio",GetRatio},
        {"SetRatio",SetRatio},
        {"GetCurrentLengthA",GetCurrentLengthA},
        {"GetCurrentLengthB",GetCurrentLengthB},
        {"SetTarget",SetTarget},
        {"GetTarget",GetTarget},
        {"SetMaxForce",SetMaxForce},
        {"GetMaxForce",GetMaxForce},
        {"GetJoint1",GetJoint1},
        {"GetJoint2",GetJoint2},
        {"GetJointLinearSpeed",GetJointLinearSpeed},
        {"GetJointAngularSpeed",GetJointAngularSpeed},
        {"GetMaxTorque",GetMaxTorque},
        {"SetMaxTorque",SetMaxTorque},
        {"SetLinearOffset",SetLinearOffset},
        {"GetLinearOffset",GetLinearOffset},
        {"SetAngularOffset",SetAngularOffset},
        {"GetAngularOffset",GetAngularOffset},
        {"SetCorrectionFactor",SetCorrectionFactor},
        {"GetCorrectionFactor",GetCorrectionFactor},
        {"__tostring",ToString},
        { 0, 0 }
    };
    luaL_newmetatable(L, META_NAME);
    luaL_register (L, NULL,functions);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_pop(L, 1);


    assert(top == lua_gettop(L));
}


void Joint::Destroy(lua_State *L) {
    utils::unref(L, user_data_ref);
    user_data_ref = LUA_REFNIL;

    BaseUserData::Destroy(L);
    delete this;
}

}


