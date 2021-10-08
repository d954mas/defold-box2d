#include "world.h"
#include "utils.h"
#include "body_def.h"
#include "joint_def.h"
#include "body.h"
#include "joint.h"
#include "draw.h"
#include "fixture.h"
#include "static_hash.h"

#include <map>

#define META_NAME "Box2d::WorldClass"
#define USERDATA_TYPE "world"


namespace box2dDefoldNE {

extern lua_State * GLOBAL_L;

//TODO add userdata field to b2world
std::map<b2World*, World*> WORLD_BY_POINTER; //to get world from body:GetWorld().

World::World(b2Vec2 gravity): BaseUserData(USERDATA_TYPE)
{
	world = new b2World(gravity);
	this->box2dObj = world;
	this->metatable_name = META_NAME;
	draw = NULL;
    contactListener = NULL;
    destructionListener = NULL;

    WORLD_BY_POINTER[world] = this;

    world->SetContactListener(this);
    world->SetDestructionListener(this);
}


World::~World() {
	if (world != NULL) {
	    WORLD_BY_POINTER.erase(world);
		delete world;
		world = NULL;
	}
}


World* World_get_userdata_safe(lua_State *L, int index) {
    World *lua_world = (World*) BaseUserData_get_userdata(L, index, USERDATA_TYPE);
	return lua_world;
}

World* World_find_by_pointer(b2World* world){
    return WORLD_BY_POINTER.at(world);
}

//region box2d API
//void 	SetDestructionListener (b2DestructionListener *listener)
static int SetDestructionListener(lua_State *L){
    utils::check_arg_count(L, 2);
    World *world = World_get_userdata_safe(L, 1);
    if (!(lua_isnil(L, 2) || lua_istable(L, 2))) {
         utils::error(L,"listener can be only table or nil");
    }

    if(world->destructionListener != NULL){
        world->destructionListener->Destroy(L);
        world->destructionListener = NULL;
    }


    if(lua_istable(L, 2)){
        world->destructionListener = new LuaDestructionListener();
        world->destructionListener->InitFromTable(L,2);
    }

   return 0;
}


    //const b2ContactManager &GetContactManager () const NOT IMPL

static int GetProfile(lua_State *L){//const b2Profile &GetProfile () const
    DM_LUA_STACK_CHECK(L, 1);

    utils::check_arg_count(L, 1);

    World *lua_world = World_get_userdata_safe(L, 1);
    const b2Profile profile = lua_world->world->GetProfile();

    lua_newtable(L);
    lua_pushnumber(L, profile.step);
    lua_setfield(L, -2, "step");
    lua_pushnumber(L, profile.collide);
    lua_setfield(L, -2, "collide");
    lua_pushnumber(L, profile.solve);
    lua_setfield(L, -2, "solve");
    lua_pushnumber(L, profile.solveInit);
    lua_setfield(L, -2, "solveInit");
    lua_pushnumber(L, profile.solveVelocity);
    lua_setfield(L, -2, "solveVelocity");
    lua_pushnumber(L, profile.solvePosition);
    lua_setfield(L, -2, "solvePosition");
    lua_pushnumber(L, profile.broadphase);
    lua_setfield(L, -2, "broadphase");
    lua_pushnumber(L, profile.solveTOI);
    lua_setfield(L, -2, "solveTOI");

    return 1;
}
//  static int SetContactFilter(lua_State *L); // void SetContactFilter(b2ContactFilter *filter)

// void SetContactListener (b2ContactListener *listener)
static int SetContactListener(lua_State *L){
    utils::check_arg_count(L, 2);
    World *world = World_get_userdata_safe(L, 1);
    if (!(lua_isnil(L, 2) || lua_istable(L, 2))) {
         utils::error(L,"listener can be only table or nil");
    }

    if(world->contactListener != NULL){
        world->contactListener->Destroy(L);
        world->contactListener = NULL;
    }


    if(lua_istable(L, 2)){
        world->contactListener = new LuaContactListener();
        world->contactListener->InitFromTable(L,2);
    }

   return 0;
}
static int SetDebugDraw(lua_State *L){//void SetDebugDraw (b2Draw *debugDraw)
    utils::check_arg_count(L, 2);
    World *world = World_get_userdata_safe(L, 1);
    if (lua_isnil(L, 2)) {
        world->world->SetDebugDraw(NULL);
        world->draw = NULL;
    }else{
        Draw *draw = Draw_get_userdata_safe(L, 2);
        world->world->SetDebugDraw(draw);
        world->draw = draw;
    }
    return 0;
}
static int CreateBody(lua_State *L){ //b2Body * CreateBody (const b2BodyDef *def)
    utils::check_arg_count(L, 1,2);
    World *world = World_get_userdata_safe(L, 1);
    b2BodyDef bodyDef;
    if (lua_gettop(L) == 1 || lua_isnil(L, 2)) {
        //use default
    }else if (lua_istable(L, 2)) {
        bodyDef = b2BodyDef_from_table(L,2);
    }else{
        utils::error(L,"bodyDef should be a table or nil");
    }

    b2Body* body = world->world->CreateBody(&bodyDef);

    Body* lua_body = new Body(body);
    //Set user data
    if(bodyDef.userData.pointer != 0){
        lua_rawgeti(L,LUA_REGISTRYINDEX,bodyDef.userData.pointer);
        int ref = luaL_ref(L,LUA_REGISTRYINDEX);
        utils::unref(L, bodyDef.userData.pointer);
        lua_body->user_data_ref = ref;
    }

    lua_body->Push(L);
    return 1;
};
static int DestroyBody(lua_State *L){ //void DestroyBody (b2Body *body)
    utils::check_arg_count(L, 2);

    World *lua_world = World_get_userdata_safe(L, 1);
    Body *body = Body_get_userdata_safe(L, 2);

    lua_world->world->DestroyBody(body->body);
    body->Destroy(L);

    return 0;
}

static int CreateJoint(lua_State *L){//static int CreateJoint(lua_State *L);//b2Joint * CreateJoint (const b2JointDef *def)
    utils::check_arg_count(L, 2);
    World *world = World_get_userdata_safe(L, 1);

    b2JointDef* def = b2JointDef_from_table(L,2);

    b2Joint* joint = world->world->CreateJoint(def);
    Joint* lua_joint = new Joint(joint);
    delete def;

    lua_joint->Push(L);

    return 1;
}

static int DestroyJoint(lua_State *L){//void DestroyJoint (b2Joint *joint)
    utils::check_arg_count(L, 2);
    World *world = World_get_userdata_safe(L, 1);
    Joint *joint = Joint_get_userdata_safe(L, 2);
    world->world->DestroyJoint(joint->joint);
    joint->Destroy(L);
    return 0;
}
static int Step(lua_State *L){;//void Step (float timeStep, int32 velocityIterations, int32 positionIterations)
    utils::check_arg_count(L, 4);

    World *lua_world = World_get_userdata_safe(L, 1);

    double time_step = lua_tonumber(L, 2);
    double velocity_iterations = lua_tonumber(L, 3);
    double position_iterations = lua_tonumber(L, 4);

    //set script instance
    if(lua_world->contactListener != NULL){
        lua_world->contactListener->error = false;
        lua_world->contactListener->error_message = NULL;
        lua_world->contactListener->L = L;
        if(lua_world->contactListener->defold_script_instance_ref != LUA_REFNIL){
            //save current instance in stack
            dmScript::GetInstance(L);
            lua_rawgeti(L, LUA_REGISTRYINDEX, lua_world->contactListener->defold_script_instance_ref);
            if (!dmScript::IsInstanceValid(L)){
                utils::error(L,"ContactListener script instance in not valid");
            }
            dmScript::SetInstance(L);
        }
    }

    lua_world->world->Step((float)time_step, (int)velocity_iterations, (int)position_iterations);


    //remove script instance
    if(lua_world->contactListener != NULL){
        lua_world->contactListener->EndListen(L);
        if(lua_world->contactListener->defold_script_instance_ref != LUA_REFNIL){
            //return prev instance
            dmScript::SetInstance(L);
        }

        if(lua_world->contactListener->error){
            luaL_error(L,"%s", lua_world->contactListener->error_message);
        }
    }
    return 0;
}

static int ClearForces(lua_State *L){//void ClearForces ()
    utils::check_arg_count(L, 1);
    World *lua_world = World_get_userdata_safe(L, 1);
    lua_world->world->ClearForces();
    return 0;
};

static int DebugDraw(lua_State *L){//void DebugDraw ()
    utils::check_arg_count(L, 1);
    World *lua_world = World_get_userdata_safe(L, 1);
    if(lua_world->draw != NULL){
        lua_world->draw->L = L;
    }
      //set script instance
    if(lua_world->draw != NULL && lua_world->draw->defold_script_instance != LUA_REFNIL){
        //save current instance in stack
        dmScript::GetInstance(L);
        lua_rawgeti(L, LUA_REGISTRYINDEX, lua_world->draw->defold_script_instance);
         if (!dmScript::IsInstanceValid(L)){utils::error(L,"DebugDraw script instance in not valid"); }
         dmScript::SetInstance(L);
    }

    lua_world->world->DebugDraw();

    //remove script instance??
    if(lua_world->draw != NULL && lua_world->draw->defold_script_instance != LUA_REFNIL){
        //return prev instance
        dmScript::SetInstance(L);
    }

    return 0;
};

class LuaQueryCallback : public b2QueryCallback {
    public:
        lua_State *L;
        bool error;
        const char *error_message;

        LuaQueryCallback(lua_State *L){  // This is the constructor
            this->L = L;
            error = false;
            error_message = NULL;
        }

        bool ReportFixture(b2Fixture* fixture) {
            lua_pushvalue(L,-1);

            Fixture* lua_fixture = (Fixture *)fixture->GetUserData().pointer;
            lua_fixture->Push(L);


            if (lua_pcall(L, 1, 1, 0) == 0){
                bool result = lua_toboolean(L,-1);
                lua_pop(L,1);
                return result;
            }else{
                error = true;
                error_message = lua_tostring(L,-1);
                lua_pop(L,1);
                return false;
            }
        }
};

//void QueryAABB (b2QueryCallback *callback, const b2AABB &aabb) const
static int QueryAABB(lua_State *L){
    utils::check_arg_count(L, 3);
    World *world = World_get_userdata_safe(L, 1);

    b2AABB aabb;

    if (!lua_isfunction(L, 2)){
        utils::error(L,"callback is not function");
        return 0;
    }

    if (!lua_istable(L, 3)){
        utils::error(L,"aabb is not table");
        return 0;
    }

    aabb.lowerBound = extra_utils::table_get_b2vec_safe(L,"lowerBound","lowerBound not vector3");
    aabb.upperBound = extra_utils::table_get_b2vec_safe(L,"upperBound","upperBound not vector3");

    //cb function on top
    lua_pushvalue(L,2);

    LuaQueryCallback* cb = new LuaQueryCallback(L);
    world->world->QueryAABB(cb, aabb);

    if(cb->error){
        const char *error_message = cb->error_message;
        delete cb;
        luaL_error(L,"%s",error_message);
    }else{
         delete cb;
    }

    lua_pop(L,1);
    return 0;
};



class LuaRayCastCallback : public b2RayCastCallback {
    public:
        lua_State *L;
        bool error;
        const char *error_message;

        LuaRayCastCallback(lua_State *L){  // This is the constructor
            this->L = L;
            error = false;
            error_message = NULL;
        }
    
        float ReportFixture(b2Fixture* fixture, const b2Vec2& point,const b2Vec2& normal, float fraction) {
            lua_pushvalue(L,-1);

            Fixture* lua_fixture = (Fixture *)fixture->GetUserData().pointer;
            lua_fixture->Push(L);

            utils::push_vector(L, point.x, point.y, 0);
            utils::push_vector(L, normal.x, normal.y, 0);
            lua_pushnumber(L,fraction);
            if (lua_pcall(L, 4, 1, 0) == 0){
                float result = lua_tonumber(L,-1);
                lua_pop(L,1);
                return result;
            }else{
                error = true;
                error_message = lua_tostring(L,-1);
                lua_pop(L,1);
                return 0;
            }
        }
};
//https://www.iforce2d.net/b2dtut/world-querying
//void RayCast (b2RayCastCallback *callback, const b2Vec2 &point1, const b2Vec2 &point2) const
static int RayCast(lua_State *L){
    utils::check_arg_count(L, 4);
    World *world = World_get_userdata_safe(L, 1);
    if (!lua_isfunction(L, 2)){
        utils::error(L,"callback is not function");
        return 0;
    }
    b2Vec2 point1 = extra_utils::get_b2vec_safe(L,3,"point1 not vector3");
    b2Vec2 point2 = extra_utils::get_b2vec_safe(L,4,"point2 not vector3");

    //cb function on top
    lua_pushvalue(L,2);

    LuaRayCastCallback* cb = new LuaRayCastCallback(L);

    world->world->RayCast(cb, point1, point2);

    if(cb->error){
        const char *error_message = cb->error_message;
        delete cb;
        luaL_error(L,"%s",error_message);
    }else{
        delete cb;
    }

    lua_pop(L,1);

    return 0;
};
static int GetContactList(lua_State *L){//b2Contact* GetContactList();
    utils::check_arg_count(L, 1);
    World *world = World_get_userdata_safe(L, 1);
    utils::check_arg_count(L, 1);
    b2Contact *contact_top = world->world->GetContactList();
    if(contact_top == NULL){
        lua_pushnil(L);
    }else{
        Contact_from_b2Contact(contact_top )->Push(L);
    }
    return 1;
}


static int GetBodyList(lua_State *L){//const b2Body * GetBodyList () const Returns the head of the world body list.
    utils::check_arg_count(L, 1);
    World *lua_world = World_get_userdata_safe(L, 1);
    b2Body* body_top = lua_world->world->GetBodyList();
    if(body_top == NULL){
        lua_pushnil(L);
    }else{
        Body* lua_body_new = (Body *)body_top->GetUserData().pointer;
        lua_body_new->Push(L);
    }
    return 1;
}

static int GetJointList(lua_State *L){ //const b2Joint * GetJointList() const
    utils::check_arg_count(L, 1);
    World *lua_world = World_get_userdata_safe(L, 1);
    b2Joint* joint_top = lua_world->world->GetJointList();
    if(joint_top == NULL){
        lua_pushnil(L);
    }else{
        Joint* lua_joint_new = (Joint *)joint_top->GetUserData().pointer;
        lua_joint_new->Push(L);
    }
    return 1;

}

static int SetAllowSleeping(lua_State *L){//void SetAllowSleeping (bool flag)
    utils::check_arg_count(L, 2);
    World *lua_world = World_get_userdata_safe(L, 1);
    lua_world->world->SetAllowSleeping(lua_toboolean(L, -1));
    return 0;
};

static int GetAllowSleeping(lua_State *L){ //bool GetAllowSleeping () const
    utils::check_arg_count(L, 1);
    World *lua_world = World_get_userdata_safe(L, 1);
    lua_pushboolean(L,lua_world->world->GetAllowSleeping());
    return 1;
};

static int SetWarmStarting(lua_State *L){//void SetWarmStarting (bool flag) Enable/disable warm starting. For testing.
    utils::check_arg_count(L, 2);
    World *lua_world = World_get_userdata_safe(L, 1);
    lua_world->world->SetWarmStarting(lua_toboolean(L, -1));
    return 0;
};

static int GetWarmStarting(lua_State *L){//bool GetWarmStarting () const
    utils::check_arg_count(L, 1);
    World *lua_world = World_get_userdata_safe(L, 1);
    lua_pushboolean(L,lua_world->world->GetWarmStarting());
    return 1;
};

static int SetContinuousPhysics(lua_State *L){//void SetContinuousPhysics (bool flag)Enable/disable continuous physics. For testing.
    utils::check_arg_count(L, 2);
    World *lua_world = World_get_userdata_safe(L, 1);
    lua_world->world->SetContinuousPhysics(lua_toboolean(L, -1));
    return 0;
};

static int GetContinuousPhysics(lua_State *L){//bool GetContinuousPhysics () const
    utils::check_arg_count(L, 1);
    World *lua_world = World_get_userdata_safe(L, 1);
    lua_pushboolean(L,lua_world->world->GetContinuousPhysics());
    return 1;
};

static int SetSubStepping(lua_State *L){//void SetSubStepping (bool flag)Enable/disable single stepped continuous physics. For testing.
    utils::check_arg_count(L, 2);
    World *lua_world = World_get_userdata_safe(L, 1);
    lua_world->world->SetSubStepping(lua_toboolean(L, -1));
    return 0;
};

static int GetSubStepping(lua_State *L){//bool GetSubStepping () const
    utils::check_arg_count(L, 1);
    World *lua_world = World_get_userdata_safe(L, 1);
    lua_pushboolean(L,lua_world->world->GetSubStepping());
    return 1;
};

static int GetProxyCount(lua_State *L){//int32 GetProxyCount () const Get the number of broad-phase proxies.
    utils::check_arg_count(L, 1);
    World *lua_world = World_get_userdata_safe(L, 1);
    lua_pushnumber(L,lua_world->world->GetProxyCount());
    return 1;
};

static int GetBodyCount(lua_State *L){//int32 GetBodyCount () const Get the number of bodies.
    utils::check_arg_count(L, 1);
    World *lua_world = World_get_userdata_safe(L, 1);
    lua_pushnumber(L,lua_world->world->GetBodyCount());
    return 1;
};

static int GetJointCount(lua_State *L){//int32 GetJointCount () const Get the number of joints.
    utils::check_arg_count(L, 1);
    World *lua_world = World_get_userdata_safe(L, 1);
    lua_pushnumber(L,lua_world->world->GetJointCount());
    return 1;
};

static int GetContactCount(lua_State *L){//int32 GetContactCount () const Get the number of contacts (each may have 0 or more contact points).
    utils::check_arg_count(L, 1);
    World *lua_world = World_get_userdata_safe(L, 1);
    lua_pushnumber(L,lua_world->world->GetContactCount());
    return 1;
};

static int GetTreeHeight(lua_State *L){//int32 GetTreeHeight () const Get the height of the dynamic tree.
    utils::check_arg_count(L, 1);
    World *lua_world = World_get_userdata_safe(L, 1);
    lua_pushnumber(L,lua_world->world->GetTreeHeight());
    return 1;
};

static int GetTreeBalance(lua_State *L){//int32 GetTreeBalance () const Get the balance of the dynamic tree.
    utils::check_arg_count(L, 1);
    World *lua_world = World_get_userdata_safe(L, 1);
    lua_pushnumber(L,lua_world->world->GetTreeBalance());
    return 1;
};


static int GetTreeQuality(lua_State *L){ //float GetTreeQuality () const
    utils::check_arg_count(L, 1);
    World *lua_world = World_get_userdata_safe(L, 1);
    lua_pushnumber(L,lua_world->world->GetTreeQuality());
    return 1;
};

static int SetGravity(lua_State *L){//void SetGravity (const b2Vec2 &gravity) Change the global gravity vector.
    utils::check_arg_count(L, 2);

    World *lua_world = World_get_userdata_safe(L, 1);
    b2Vec2 gravity = extra_utils::get_b2vec_safe(L,2,"gravity not vector3");

    lua_world->world->SetGravity(gravity);
    return 0;
};

static int GetGravity(lua_State *L){//b2Vec2 GetGravity () const Get the global gravity vector.
    utils::check_arg_count(L, 1);

    World *lua_world = World_get_userdata_safe(L, 1);

    b2Vec2 gravity = lua_world->world->GetGravity();
    utils::push_vector(L, gravity.x, gravity.y, 0);
    return 1;
};

static int IsLocked(lua_State *L){//bool IsLocked () const Is the world locked (in the middle of a time step).
    utils::check_arg_count(L, 1);
    World *lua_world = World_get_userdata_safe(L, 1);
    lua_pushboolean(L,lua_world->world->IsLocked());
    return 1;
};

static int SetAutoClearForces(lua_State *L){ //void SetAutoClearForces (bool flag) Set flag to control automatic clearing of forces after each time step.
    utils::check_arg_count(L, 2);
    World *lua_world = World_get_userdata_safe(L, 1);
    lua_world->world->SetAutoClearForces(lua_toboolean(L, -1));
    return 0;
};

static int GetAutoClearForces(lua_State *L){ //bool GetAutoClearForces () const Get the flag that controls automatic clearing of forces after each time step.
    utils::check_arg_count(L, 1);
    World *lua_world = World_get_userdata_safe(L, 1);
    lua_pushboolean(L,lua_world->world->GetAutoClearForces());
    return 1;
};

static int ShiftOrigin(lua_State *L){//void ShiftOrigin (const b2Vec2 &newOrigin)
    utils::check_arg_count(L, 2);
    World *lua_world = World_get_userdata_safe(L, 1);
    b2Vec2 newOrigin = extra_utils::get_b2vec_safe(L,-1,"newOrigin not vector3");
    lua_world->world->ShiftOrigin(newOrigin);
    return 0;
};


static int Dump(lua_State *L){//void Dump()
    utils::check_arg_count(L, 1);

    World *lua_world = World_get_userdata_safe(L, 1);
    #if !defined(DM_PLATFORM_ANDROID) && !defined(DM_PLATFORM_IOS)
        lua_world->world->Dump();
    #else
        dmLogWarning("Dump not supported on mobiles");
    #endif
    return 0;
}

int Destroy(lua_State *L) {
	utils::check_arg_count(L, 1);
	World *lua_world = World_get_userdata_safe(L, 1);

    //destroy b2objects wrappers
    for (b2Contact *contact = lua_world->world->GetContactList(); contact; contact = contact->GetNext()) {
        b2BodyUserData& userdata = contact->GetUserData();
        if(userdata.pointer != 0){
            ((box2dDefoldNE::Contact *) userdata.pointer)->Destroy(L);
            userdata.pointer = 0;
        }
    }


	for (b2Body *body = lua_world->world->GetBodyList(); body; body = body->GetNext()) {
		Body *lua_body = (Body *)body->GetUserData().pointer;
        lua_body->DestroyJoints(L);
	}

	for (b2Body *body = lua_world->world->GetBodyList(); body; body = body->GetNext()) {
        Body *lua_body = (Body *)body->GetUserData().pointer;
        lua_body->DestroyFixtures(L);
        lua_body->Destroy(L);
    }


    lua_world->Destroy(L);
    
	return 0;
}

static int ToString(lua_State *L){
    utils::check_arg_count(L, 1);

    World *lua_world = World_get_userdata_safe(L, 1);
    lua_pushfstring( L, "b2World[%p]",(void *) lua_world->world);
	return 1;
}

static int NewIndex(lua_State *L){
    utils::error(L,"world can't set new fields");
	return 0;
}

void WorldInitMetaTable(lua_State *L){
    int top = lua_gettop(L);

    luaL_Reg functions[] = {
        {"GetProfile",GetProfile},
        {"SetContactListener",SetContactListener},
        {"SetDestructionListener",SetDestructionListener},
        {"SetDebugDraw",SetDebugDraw},
        {"CreateBody",CreateBody},
        {"DestroyBody",DestroyBody},
        {"CreateJoint",CreateJoint},
        {"DestroyJoint",DestroyJoint},
        {"Step",Step},
        {"ClearForces",ClearForces},
        {"DebugDraw",DebugDraw},
        {"RayCast",RayCast},
        {"QueryAABB",QueryAABB},
        {"GetBodyList",GetBodyList},
        {"GetContactList",GetContactList},
        {"GetJointList",GetJointList},
        {"SetAllowSleeping",SetAllowSleeping},
        {"GetAllowSleeping",GetAllowSleeping},
        {"SetWarmStarting",SetWarmStarting},
        {"GetWarmStarting",GetWarmStarting},
        {"SetContinuousPhysics",SetContinuousPhysics},
        {"GetContinuousPhysics",GetContinuousPhysics},
        {"SetSubStepping",SetSubStepping},
        {"GetSubStepping",GetSubStepping},

        {"GetProxyCount",GetProxyCount},
        {"GetBodyCount",GetBodyCount},
        {"GetJointCount",GetJointCount},
        {"GetContactCount",GetContactCount},
        {"GetTreeHeight",GetTreeHeight},
        {"GetTreeBalance",GetTreeBalance},
        {"GetTreeQuality",GetTreeQuality},

        {"SetGravity",SetGravity},
        {"GetGravity",GetGravity},

        {"IsLocked",IsLocked},
        {"SetAutoClearForces",SetAutoClearForces},
        {"GetAutoClearForces",GetAutoClearForces},

        {"ShiftOrigin",ShiftOrigin},
        {"Dump",Dump},

        {"Destroy",Destroy},
        {"__tostring",ToString},
        {"__newindex",NewIndex},
        { 0, 0 }
    };
    luaL_newmetatable(L, META_NAME);
    luaL_register (L, NULL,functions);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_pop(L, 1);

    assert(top == lua_gettop(L));
}

void World::Destroy(lua_State *L){
    if(contactListener != NULL){
        contactListener->Destroy(L);
        contactListener = NULL;
    }
    if(destructionListener != NULL){
        destructionListener->Destroy(L);
        destructionListener = NULL;
    }

    BaseUserData::Destroy(L);
    delete this;
}


// b2ContactListener
void World::BeginContact(b2Contact *contact) {
     if(contactListener != NULL){
        contactListener->BeginContact(contact);
     }
}

void World::EndContact(b2Contact *contact) {
    if(contactListener != NULL){
        contactListener->EndContact(contact);
    }
}

void World::PreSolve(b2Contact *contact, const b2Manifold *old_manifold) {
    if(contactListener != NULL){
        contactListener->PreSolve(contact, old_manifold);
    }
}

void World::PostSolve(b2Contact* contact, const b2ContactImpulse *impulse) {
    if(contactListener != NULL){
        contactListener->PostSolve(contact, impulse);
    }
}

void World::SayGoodbye(b2Joint* joint) {
    Joint* joint_lua = (Joint *)joint->GetUserData().pointer;
    if(destructionListener != NULL){
        destructionListener->SayGoodbye(joint);
        if(destructionListener->error){
            dmLogError("SayGoodbyeJoint error:%s",destructionListener->error_message);
        }
    }
    joint_lua->Destroy(GLOBAL_L);
}

void World::SayGoodbye(b2Fixture* fixture) {
    Fixture* fixture_lua = (Fixture *)fixture->GetUserData().pointer;
    if(destructionListener != NULL){
        destructionListener->SayGoodbye(fixture);
        if(destructionListener->error){
            dmLogError("SayGoodbyeFixture error:%s",destructionListener->error_message);
        }
    }

    fixture_lua->Destroy(GLOBAL_L);
}

}