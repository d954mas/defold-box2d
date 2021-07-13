// include the Defold SDK
#include <dmsdk/sdk.h>

#define EXTENSION_NAME box2d
#define EXTENSION_NAME_STRING "box2d"

#include <box2d/box2d.h>
#include <utils.h>
#include <extra_utils.h>
#include <world.h>
#include <fixture.h>
#include <body_def.h>
#include <body.h>
#include <joint.h>
#include <draw.h>
#include <joint_def.h>
#include <contact.h>

using  namespace box2dDefoldNE;

static int extension_new_world(lua_State *L) {
    DM_LUA_STACK_CHECK(L, 1);

	utils::check_arg_count(L, 0, 1);
	b2Vec2 gravity(0.0f, 0.0f);

	if (lua_isuserdata(L, 1)) {
		gravity = extra_utils::get_b2vec_safe(L,1, "gravity not vector");
	}

	World *world = new World(gravity);
	world->Push(L);
	return 1;
}

static int extension_new_debug_draw(lua_State *L) {
    DM_LUA_STACK_CHECK(L, 1);
    utils::check_arg_count(L, 1);

	Draw* draw = Draw_from_table(L);
	draw->Push(L);
	return 1;
}

static int b2LinearStiffnessLua(lua_State *L) {
    utils::check_arg_count(L, 4);
    float frequencyHertz = luaL_checknumber(L,1);
    float dampingRatio = luaL_checknumber(L,2);
    Body* bodyA = Body_get_userdata_safe(L, 3);
    Body* bodyB = Body_get_userdata_safe(L, 4);

    float stiffness, damping;
    b2LinearStiffness(stiffness, damping, frequencyHertz, dampingRatio, bodyA->body, bodyB->body);

    lua_pushnumber(L, stiffness);
    lua_pushnumber(L, damping);
	return 2;
}

static int b2AngularStiffnessLua(lua_State *L) {
    utils::check_arg_count(L, 4);
    float frequencyHertz = luaL_checknumber(L,1);
    float dampingRatio = luaL_checknumber(L,2);
    Body* bodyA = Body_get_userdata_safe(L, 3);
    Body* bodyB = Body_get_userdata_safe(L, 4);

    float stiffness, damping;
    b2AngularStiffness(stiffness, damping, frequencyHertz, dampingRatio, bodyA->body, bodyB->body);

    lua_pushnumber(L, stiffness);
    lua_pushnumber(L, damping);
	return 2;
}

static int InitializeRevoluteJointDef(lua_State *L) {
    utils::check_arg_count(L, 3);
    b2RevoluteJointDef def;

    Body* bodyA = Body_get_userdata_safe(L, 1);
    Body* bodyB = Body_get_userdata_safe(L, 2);
    b2Vec2 anchor = extra_utils::get_b2vec_safe(L, 3, "anchor not vector");
    def.Initialize(bodyA->body,bodyB->body,anchor);
    b2JointDef_to_table(L,&def);
	return 1;
}

static int InitializePrismaticJointDef(lua_State *L) {
    utils::check_arg_count(L, 4);
    b2PrismaticJointDef def;

    Body* bodyA = Body_get_userdata_safe(L, 1);
    Body* bodyB = Body_get_userdata_safe(L, 2);
    b2Vec2 anchor = extra_utils::get_b2vec_safe(L, 3, "anchor not vector");
    b2Vec2 axis = extra_utils::get_b2vec_safe(L, 4, "axis not vector");

    def.Initialize(bodyA->body,bodyB->body,anchor,axis);
    b2JointDef_to_table(L,&def);
	return 1;
}

static int InitializeDistanceJointDef(lua_State *L) {
    utils::check_arg_count(L, 4);
    b2DistanceJointDef def;

    Body* bodyA = Body_get_userdata_safe(L, 1);
    Body* bodyB = Body_get_userdata_safe(L, 2);
    b2Vec2 anchorA = extra_utils::get_b2vec_safe(L, 3, "anchorA not vector");
    b2Vec2 anchorB = extra_utils::get_b2vec_safe(L, 4, "anchorB not vector");

    def.Initialize(bodyA->body,bodyB->body,anchorA,anchorB);
    b2JointDef_to_table(L,&def);
	return 1;
}

static int InitializePulleyJointDef(lua_State *L) {
    utils::check_arg_count(L, 7);
    b2PulleyJointDef def;

    Body* bodyA = Body_get_userdata_safe(L, 1);
    Body* bodyB = Body_get_userdata_safe(L, 2);
    b2Vec2 groundAnchorA = extra_utils::get_b2vec_safe(L, 3, "groundAnchorA not vector");
    b2Vec2 groundAnchorB = extra_utils::get_b2vec_safe(L, 4, "groundAnchorB not vector");
    b2Vec2 anchorA = extra_utils::get_b2vec_safe(L, 5, "anchorA not vector");
    b2Vec2 anchorB = extra_utils::get_b2vec_safe(L, 6, "anchorB not vector");
    float ratio = luaL_checknumber(L,7);

    def.Initialize(bodyA->body,bodyB->body,groundAnchorA,groundAnchorB,anchorA,anchorB,ratio);
    b2JointDef_to_table(L,&def);
	return 1;
}

static int InitializeMouseJointDef(lua_State *L) {
    utils::check_arg_count(L, 2);
    b2MouseJointDef def;

    def.bodyA = Body_get_userdata_safe(L, 1)->body;
    def.bodyB = Body_get_userdata_safe(L, 2)->body;

    b2JointDef_to_table(L,&def);
	return 1;
}

static int InitializeGearJointDef(lua_State *L) {
    utils::check_arg_count(L, 4);
    b2GearJointDef def;
    def.bodyA = Body_get_userdata_safe(L, 1)->body;
    def.bodyB = Body_get_userdata_safe(L, 2)->body;
    def.joint1 = Joint_get_userdata_safe(L, 3)->joint;
    def.joint2 = Joint_get_userdata_safe(L, 4)->joint;
    b2JointDef_to_table(L,&def);
	return 1;
}

static int InitializeWheelJointDef(lua_State *L) {
    utils::check_arg_count(L, 4);
    b2WheelJointDef def;

    Body* bodyA = Body_get_userdata_safe(L, 1);
    Body* bodyB = Body_get_userdata_safe(L, 2);
    b2Vec2 anchor = extra_utils::get_b2vec_safe(L, 3, "anchor not vector");
    b2Vec2 axis = extra_utils::get_b2vec_safe(L, 4, "axis not vector");

    def.Initialize(bodyA->body,bodyB->body,anchor,axis);
    b2JointDef_to_table(L,&def);
	return 1;
}

static int InitializeWeldJointDef(lua_State *L) {
    utils::check_arg_count(L, 3);
    b2WeldJointDef def;

    Body* bodyA = Body_get_userdata_safe(L, 1);
    Body* bodyB = Body_get_userdata_safe(L, 2);
    b2Vec2 anchor = extra_utils::get_b2vec_safe(L, 3, "anchor not vector");

    def.Initialize(bodyA->body,bodyB->body,anchor);
    b2JointDef_to_table(L,&def);
	return 1;
}

static int InitializeFrictionJointDef(lua_State *L) {
    utils::check_arg_count(L, 3);
    b2FrictionJointDef def;

    Body* bodyA = Body_get_userdata_safe(L, 1);
    Body* bodyB = Body_get_userdata_safe(L, 2);
    b2Vec2 anchor = extra_utils::get_b2vec_safe(L, 3, "anchor not vector");

    def.Initialize(bodyA->body,bodyB->body,anchor);
    b2JointDef_to_table(L,&def);
	return 1;
}

static int InitializeMotorJointDef(lua_State *L) {
    utils::check_arg_count(L, 2);
    b2MotorJointDef def;

    Body* bodyA = Body_get_userdata_safe(L, 1);
    Body* bodyB = Body_get_userdata_safe(L, 2);

    def.Initialize(bodyA->body,bodyB->body);
    b2JointDef_to_table(L,&def);
	return 1;
}

static const luaL_reg lua_functions[] = {
    {"NewWorld", extension_new_world},
    {"NewDebugDraw", extension_new_debug_draw},
    {"b2LinearStiffness", b2LinearStiffnessLua},
    {"b2AngularStiffness", b2AngularStiffnessLua},
    {"InitializeRevoluteJointDef", InitializeRevoluteJointDef},
    {"InitializePrismaticJointDef", InitializePrismaticJointDef},
    {"InitializeDistanceJointDef", InitializeDistanceJointDef},
    {"InitializePulleyJointDef", InitializePulleyJointDef},
    {"InitializeMouseJointDef", InitializeMouseJointDef},
    {"InitializeGearJointDef", InitializeGearJointDef},
    {"InitializeWheelJointDef", InitializeWheelJointDef},
    {"InitializeWeldJointDef", InitializeWeldJointDef},
    {"InitializeFrictionJointDef", InitializeFrictionJointDef},
    {"InitializeMotorJointDef", InitializeMotorJointDef},
	{0, 0}
};




dmExtension::Result APP_INITIALIZE(dmExtension::AppParams *params) {
	return dmExtension::RESULT_OK;
}

dmExtension::Result APP_FINALIZE(dmExtension::AppParams *params) {
	return dmExtension::RESULT_OK;
}

dmExtension::Result INITIALIZE(dmExtension::Params *params) {
	dmLogInfo("Box2D NE version %d.%d.%d", b2_version.major, b2_version.minor, b2_version.revision);
	
   	lua_State *L = params->m_L;
	luaL_register(L, EXTENSION_NAME_STRING, lua_functions);

	lua_newtable(L);
	    lua_pushnumber(L, b2Shape::e_circle);
        lua_setfield(L, -2, "e_circle");
        lua_pushnumber(L, b2Shape::e_edge);
        lua_setfield(L, -2, "e_edge");
        lua_pushnumber(L, b2Shape::e_polygon);
        lua_setfield(L, -2, "e_polygon");
        lua_pushnumber(L, b2Shape::e_chain);
        lua_setfield(L, -2, "e_chain");
    lua_setfield(L, -2, "b2Shape");

    lua_newtable(L);
        lua_pushnumber(L, b2BodyType::b2_staticBody);
        lua_setfield(L, -2, "b2_staticBody");
        lua_pushnumber(L, b2BodyType::b2_kinematicBody);
        lua_setfield(L, -2, "b2_kinematicBody");
        lua_pushnumber(L, b2BodyType::b2_dynamicBody);
        lua_setfield(L, -2, "b2_dynamicBody");
    lua_setfield(L, -2, "b2BodyType");

    lua_newtable(L);
        lua_pushnumber(L, b2JointType::e_unknownJoint);
        lua_setfield(L, -2, "e_unknownJoint");
        lua_pushnumber(L, b2JointType::e_revoluteJoint);
        lua_setfield(L, -2, "e_revoluteJoint");
        lua_pushnumber(L, b2JointType::e_prismaticJoint);
        lua_setfield(L, -2, "e_prismaticJoint");
        lua_pushnumber(L, b2JointType::e_distanceJoint);
        lua_setfield(L, -2, "e_distanceJoint");
        lua_pushnumber(L, b2JointType::e_pulleyJoint);
        lua_setfield(L, -2, "e_pulleyJoint");
        lua_pushnumber(L, b2JointType::e_mouseJoint);
        lua_setfield(L, -2, "e_mouseJoint");
        lua_pushnumber(L, b2JointType::e_gearJoint);
        lua_setfield(L, -2, "e_gearJoint");
        lua_pushnumber(L, b2JointType::e_wheelJoint);
        lua_setfield(L, -2, "e_wheelJoint");
        lua_pushnumber(L, b2JointType::e_weldJoint);
        lua_setfield(L, -2, "e_weldJoint");
        lua_pushnumber(L, b2JointType::e_frictionJoint);
        lua_setfield(L, -2, "e_frictionJoint");
        lua_pushnumber(L, b2JointType::e_ropeJoint);
        lua_setfield(L, -2, "e_ropeJoint");
        lua_pushnumber(L, b2JointType::e_motorJoint);
        lua_setfield(L, -2, "e_motorJoint");
    lua_setfield(L, -2, "b2JointType");


    lua_newtable(L);
        lua_pushnumber(L, b2Draw::e_shapeBit);
        lua_setfield(L, -2, "e_shapeBit");
        lua_pushnumber(L, b2Draw::e_jointBit);
        lua_setfield(L, -2, "e_jointBit");
        lua_pushnumber(L, b2Draw::e_aabbBit);
        lua_setfield(L, -2, "e_aabbBit");
        lua_pushnumber(L, b2Draw::e_pairBit);
        lua_setfield(L, -2, "e_pairBit");
        lua_pushnumber(L, b2Draw::e_centerOfMassBit);
        lua_setfield(L, -2, "e_centerOfMassBit");
    lua_setfield(L, -2, "b2Draw");

    lua_newtable(L);
        lua_pushnumber(L, b2Manifold::Type::e_circles);
        lua_setfield(L, -2, "e_circles");
        lua_pushnumber(L, b2Manifold::Type::e_faceA);
        lua_setfield(L, -2, "e_faceA");
        lua_pushnumber(L, b2Manifold::Type::e_faceB);
        lua_setfield(L, -2, "e_faceB");
    lua_setfield(L, -2, "b2Manifold_Type");



	lua_pop(params->m_L, 1);

    WorldInitMetaTable(L);
    FixtureInitMetaTable(L);
    BodyInitMetaTable(L);
    JointInitMetaTable(L);
    DrawInitMetaTable(L);
    ContactInitMetaTable(L);

	return dmExtension::RESULT_OK;
}

dmExtension::Result FINALIZE(dmExtension::Params *params) {
	return dmExtension::RESULT_OK;
}

dmExtension::Result UPDATE(dmExtension::Params *params) {
	return dmExtension::RESULT_OK;
}

void EXTENSION_ON_EVENT(dmExtension::Params *params, const dmExtension::Event *event) {
	switch (event->m_Event) {
		case dmExtension::EVENT_ID_ACTIVATEAPP:
			break;
		case dmExtension::EVENT_ID_DEACTIVATEAPP:
			break;
	}
}



DM_DECLARE_EXTENSION(EXTENSION_NAME, EXTENSION_NAME_STRING, APP_INITIALIZE, APP_FINALIZE, INITIALIZE, UPDATE, EXTENSION_ON_EVENT, FINALIZE)