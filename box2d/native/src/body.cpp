#include "body.h"
#include "fixture_def.h"
#include "fixture.h"
#include "utils.h"
#include "shape.h"
#include "joint.h"
#include "allocators.h"

#define META_NAME "Box2d::BodyClass"
#define USERDATA_TYPE "body"

namespace box2dDefoldNE {

Body::Body(b2Body *b):  BaseUserData(USERDATA_TYPE){
    this->box2dObj = b;
    this->metatable_name = META_NAME;

    user_data_ref = LUA_REFNIL;
	body = b;
	b2BodyUserData& userdata = body->GetUserData();
	userdata.pointer = (uintptr_t)(void*) this;
}

Body::~Body() {

}


Body* Body_get_userdata_safe(lua_State *L, int index) {
    Body *lua_body = (Body*) BaseUserData_get_userdata(L, index, USERDATA_TYPE);
    return lua_body;
}

static int CreateFixture(lua_State *L){
//b2Fixture* CreateFixture (const b2FixtureDef *def)
//b2Fixture* CreateFixture (const b2Shape *shape, float density)
    utils::check_arg_count(L, 2,3);
    Body *body = Body_get_userdata_safe(L, 1);
    Fixture* lua_fixture = NULL;

    if (lua_gettop(L) == 2 || lua_isnil(L, 3)) {
        b2FixtureDef def = b2FixtureDef_from_table(L,2);
        b2Fixture* fixture = body->body->CreateFixture(&def);
        lua_fixture = new Fixture(fixture);
        if(def.userData.pointer != NULL){
           lua_rawgeti(L,LUA_REGISTRYINDEX,def.userData.pointer);
           int ref = luaL_ref(L,LUA_REGISTRYINDEX);
           utils::unref(L, def.userData.pointer);
           lua_fixture->user_data_ref = ref;
        }
        b2Shape_free((b2Shape*) def.shape);
    }else{
        b2Shape* shape = b2Shape_from_lua(L,2);
        double density = lua_tonumber(L,3);
        b2Fixture* fixture = body->body->CreateFixture(shape,density);
        lua_fixture = new Fixture(fixture);
        b2Shape_free(shape);
    }

    lua_fixture->Push(L);

    return 1;
}



static int DestroyFixture(lua_State *L){//void DestroyFixture (b2Fixture *fixture)
    utils::check_arg_count(L, 2);
    Body *body = Body_get_userdata_safe(L, 1);
    Fixture *fixture = Fixture_get_userdata_safe(L, 2);
    body->body->DestroyFixture(fixture->fixture);
    fixture->Destroy(L);

    return 0;
}

static int SetTransform(lua_State *L){ //void SetTransform (const b2Vec2 &position, float angle)
    utils::check_arg_count(L, 2,3);
    Body *body = Body_get_userdata_safe(L, 1);
    b2Vec2 position = extra_utils::get_b2vec_safe(L,2,"position not vector3");
    float angle = 0;

    if (lua_gettop(L) == 2 || lua_isnil(L, 3)) {
        const b2Transform& transform = body->body->GetTransform();
        angle = transform.q.GetAngle();
    }else{
        angle = lua_tonumber(L,3);
    }
    body->body->SetTransform(position,angle);
    return 0;
};

static int GetTransform(lua_State *L){ //const b2Transform& GetTransform () const
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    const b2Transform& transform = body->body->GetTransform();
    extra_utils::b2Transform_push(L, transform);
    return 1;
};

static int GetPosition(lua_State *L){ //const b2Vec2& GetPosition () const
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    b2Vec2 position = body->body->GetPosition();
    utils::push_vector(L, position.x, position.y, 0);
    return 1;
}

static int GetPositionRaw(lua_State *L){
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    b2Vec2 position = body->body->GetPosition();
    lua_pushnumber(L, position.x);
    lua_pushnumber(L, position.y);
    return 2;
}

static int GetAngle(lua_State *L){//float GetAngle () const
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    float angle = body->body->GetAngle();
    lua_pushnumber(L, angle);
    return 1;
}

static int GetWorldCenter(lua_State *L){ //const b2Vec2& GetWorldCenter () const Get the world position of the center of mass.
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    b2Vec2 center = body->body->GetWorldCenter();
    utils::push_vector(L, center.x, center.y, 0);
    return 1;
}

static int GetLocalCenter(lua_State *L){ //const b2Vec2& GetLocalCenter () const Get the local position of the center of mass.
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    b2Vec2 center = body->body->GetLocalCenter();
    utils::push_vector(L, center.x, center.y, 0);
    return 1;
}

static int SetLinearVelocity(lua_State *L){//void SetLinearVelocity (const b2Vec2 &v)
    utils::check_arg_count(L, 2);
    Body *body = Body_get_userdata_safe(L, 1);
    b2Vec2 vector = extra_utils::get_b2vec_safe(L,2,"LinearVelocity not vector3");
    body->body->SetLinearVelocity(vector);
    return 0;
};

static int GetLinearVelocity(lua_State *L){ //const b2Vec2& GetLinearVelocity () const
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    b2Vec2 vector = body->body->GetLinearVelocity();
    utils::push_vector(L, vector.x, vector.y, 0);
    return 1;
}

static int SetAngularVelocity(lua_State *L){//void SetAngularVelocity (float omega)
    utils::check_arg_count(L, 2);
    Body *body = Body_get_userdata_safe(L, 1);
    float omega = lua_tonumber(L,2);
    body->body->SetAngularVelocity(omega);
    return 0;
}

static int GetAngularVelocity(lua_State *L){//float GetAngularVelocity () const
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    float omega = body->body->GetAngularVelocity();
    lua_pushnumber(L, omega);
    return 1;
}

static int ApplyForce(lua_State *L){//void ApplyForce (const b2Vec2 &force, const b2Vec2 &point, bool wake)
    utils::check_arg_count(L, 4);
    Body *body = Body_get_userdata_safe(L, 1);
    b2Vec2 force = extra_utils::get_b2vec_safe(L,2,"force not vector3");
    b2Vec2 point = extra_utils::get_b2vec_safe(L,3,"point not vector3");
    bool wake = lua_toboolean(L, 4);
    body->body->ApplyForce(force,point,wake);
    return 0;
}

static int ApplyForceToCenter(lua_State *L){//void ApplyForceToCenter (const b2Vec2 &force, bool wake)
    utils::check_arg_count(L, 3);
    Body *body = Body_get_userdata_safe(L, 1);
    b2Vec2 force = extra_utils::get_b2vec_safe(L,2,"force not vector3");
    bool wake = lua_toboolean(L, 3);
    body->body->ApplyForceToCenter(force,wake);
    return 0;
}

static int ApplyTorque(lua_State *L){//void ApplyTorque (float torque, bool wake)
    utils::check_arg_count(L, 3);
    Body *body = Body_get_userdata_safe(L, 1);
    float torque =  lua_tonumber(L, 2);
    bool wake = lua_toboolean(L, 3);
    body->body->ApplyTorque(torque,wake);
    return 0;
}

static int ApplyLinearImpulse(lua_State *L){//void ApplyLinearImpulse (const b2Vec2 &impulse, const b2Vec2 &point, bool wake)
    utils::check_arg_count(L, 4);
    Body *body = Body_get_userdata_safe(L, 1);
    b2Vec2 impulse = extra_utils::get_b2vec_safe(L,2,"impulse not vector3");
    b2Vec2 point = extra_utils::get_b2vec_safe(L,3,"point not vector3");
    bool wake = lua_toboolean(L, 4);
    body->body->ApplyLinearImpulse(impulse,point,wake);
    return 0;
}

static int ApplyLinearImpulseToCenter(lua_State *L){//void ApplyLinearImpulseToCenter (const b2Vec2 &impulse, bool wake)
    utils::check_arg_count(L, 3);
    Body *body = Body_get_userdata_safe(L, 1);
    b2Vec2 impulse = extra_utils::get_b2vec_safe(L,2,"impulse not vector3");
    bool wake = lua_toboolean(L, 3);
    body->body->ApplyLinearImpulseToCenter(impulse,wake);
    return 0;
}

static int ApplyAngularImpulse(lua_State *L){//void ApplyAngularImpulse (float impulse, bool wake)
    utils::check_arg_count(L, 3);
    Body *body = Body_get_userdata_safe(L, 1);
    float impulse =  lua_tonumber(L, 2);
    bool wake = lua_toboolean(L, 3);
    body->body->ApplyAngularImpulse(impulse,wake);
    return 0;
}


static int GetMass(lua_State *L){//float GetMass () const
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    float mass = body->body->GetMass();
    lua_pushnumber(L, mass);
    return 1;
}

static int GetInertia(lua_State *L){//float GetInertia () const
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    float value = body->body->GetInertia();
    lua_pushnumber(L, value);
    return 1;
}

static int ResetMassData(lua_State *L){//void ResetMassData () 
	utils::check_arg_count(L, 1);
	Body *lua_body = Body_get_userdata_safe(L,1);
    lua_body->body->ResetMassData();
    return 0;
}

static int GetMassData(lua_State *L) { //void GetMassData (b2MassData *data) const
	utils::check_arg_count(L, 1);
	Body *lua_body = Body_get_userdata_safe(L,1);
    b2MassData massData;
    lua_body->body->GetMassData(&massData);

    extra_utils::massData_to_table(L,massData);

    return 1;
}

static int SetMassData(lua_State *L) { //void SetMassData (const b2MassData *data)
	utils::check_arg_count(L, 2);
	Body *lua_body = Body_get_userdata_safe(L,1);
    b2MassData massData = extra_utils::get_b2MassData_safe(L,2,"not massData");


    lua_body->body->SetMassData(&massData);
    return 0;
}

static int GetWorldPoint(lua_State *L){ //b2Vec2 GetWorldPoint (const b2Vec2 &localPoint) const
    utils::check_arg_count(L, 2);
    Body *body = Body_get_userdata_safe(L, 1);
    b2Vec2 vector = extra_utils::get_b2vec_safe(L,2,"localPoint not vector3");

    b2Vec2 result = body->body->GetWorldPoint(vector);
    utils::push_vector(L, result.x, result.y, 0);
    return 1;
}

static int GetWorldVector(lua_State *L){ //b2Vec2 GetWorldVector (const b2Vec2 &localVector) const
    utils::check_arg_count(L, 2);
    Body *body = Body_get_userdata_safe(L, 1);
    b2Vec2 vector = extra_utils::get_b2vec_safe(L,2,"localVector not vector3");

    b2Vec2 result = body->body->GetWorldVector(vector);
    utils::push_vector(L, result.x, result.y, 0);
    return 1;
}

static int GetLocalPoint(lua_State *L){ //b2Vec2 GetLocalPoint (const b2Vec2 &worldPoint) const
    utils::check_arg_count(L, 2);
    Body *body = Body_get_userdata_safe(L, 1);
    b2Vec2 vector = extra_utils::get_b2vec_safe(L,2,"worldPoint not vector3");

    b2Vec2 result = body->body->GetLocalPoint(vector);
    utils::push_vector(L, result.x, result.y, 0);
    return 1;
}

static int GetLocalVector(lua_State *L){ //b2Vec2 GetLocalVector (const b2Vec2 &worldVector) const
    utils::check_arg_count(L, 2);
    Body *body = Body_get_userdata_safe(L, 1);
    b2Vec2 vector = extra_utils::get_b2vec_safe(L,2,"worldVector not vector3");

    b2Vec2 result = body->body->GetLocalVector(vector);
    utils::push_vector(L, result.x, result.y, 0);
    return 1;
}

static int GetLinearVelocityFromWorldPoint(lua_State *L){ //b2Vec2 GetLinearVelocityFromWorldPoint (const b2Vec2 &worldPoint) const
    utils::check_arg_count(L, 2);
    Body *body = Body_get_userdata_safe(L, 1);
    b2Vec2 vector = extra_utils::get_b2vec_safe(L,2,"worldPoint not vector3");

    b2Vec2 result = body->body->GetLinearVelocityFromWorldPoint(vector);
    utils::push_vector(L, result.x, result.y, 0);
    return 1;
}

static int GetLinearVelocityFromLocalPoint(lua_State *L){//b2Vec2 GetLinearVelocityFromLocalPoint (const b2Vec2 &localPoint) const
    utils::check_arg_count(L, 2);
    Body *body = Body_get_userdata_safe(L, 1);
    b2Vec2 vector = extra_utils::get_b2vec_safe(L,2,"localPoint not vector3");

    b2Vec2 result = body->body->GetLinearVelocityFromLocalPoint(vector);
    utils::push_vector(L, result.x, result.y, 0);
    return 1;
}

static int SetLinearDamping(lua_State *L){//void SetLinearDamping (float linearDamping) Set the linear damping of the body.
    utils::check_arg_count(L, 2);
    Body *body = Body_get_userdata_safe(L, 1);
    float value = lua_tonumber(L,2);
    body->body->SetLinearDamping(value);
    return 0;
}

static int GetLinearDamping(lua_State *L){//float GetLinearDamping () const Get the linear damping of the body.
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    float value = body->body->GetLinearDamping();
    lua_pushnumber(L, value);
    return 1;
}

static int SetAngularDamping(lua_State *L){//void SetAngularDamping (float angularDamping) Set the angular damping of the body.
    utils::check_arg_count(L, 2);
    Body *body = Body_get_userdata_safe(L, 1);
    float value = lua_tonumber(L,2);
    body->body->SetAngularDamping(value);
    return 0;
}

static int GetAngularDamping(lua_State *L){//float GetAngularDamping () const Get the angular damping of the body.
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    float value = body->body->GetAngularDamping();
    lua_pushnumber(L, value);
    return 1;
}

static int SetGravityScale(lua_State *L){//void SetGravityScale (float scale) Set the gravity scale of the body.
    utils::check_arg_count(L, 2);
    Body *body = Body_get_userdata_safe(L, 1);
    float value = lua_tonumber(L,2);
    body->body->SetGravityScale(value);
    return 0;
}

static int GetGravityScale(lua_State *L){//float GetGravityScale () const Get the gravity scale of the body.
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    float value = body->body->GetGravityScale();
    lua_pushnumber(L, value);
    return 1;
}



static int SetType(lua_State *L){//void SetType (b2BodyType type) Set the type of this body. This may alter the mass and velocity.
    utils::check_arg_count(L, 2);
    Body *body = Body_get_userdata_safe(L, 1);
    b2BodyType type = static_cast<b2BodyType>(lua_tonumber(L, 2));
    body->body->SetType(type);
    return 0;
}
static int GetType(lua_State *L){//b2BodyType GetType () const Get the type of this body.
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    lua_pushnumber(L,body->body->GetType());
    return 1;
}

static int SetBullet(lua_State *L){//void SetBullet (bool flag) Should this body be treated like a bullet for continuous collision detection?
    utils::check_arg_count(L, 2);
    Body *body = Body_get_userdata_safe(L, 1);
    body->body->SetBullet(lua_toboolean(L, 2));
    return 0;
};

static int IsBullet(lua_State *L){ //bool IsBullet () const Is this body treated like a bullet for continuous collision detection?
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    lua_pushboolean(L,body->body->IsBullet());
    return 1;
};

static int SetSleepingAllowed(lua_State *L){//void SetSleepingAllowed (bool flag)
    utils::check_arg_count(L, 2);
    Body *body = Body_get_userdata_safe(L, 1);
    body->body->SetSleepingAllowed(lua_toboolean(L, 2));
    return 0;
};

static int IsSleepingAllowed(lua_State *L){ //bool IsSleepingAllowed () const Is this body allowed to sleep.
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    lua_pushboolean(L,body->body->IsSleepingAllowed());
    return 1;
};

static int SetAwake(lua_State *L){//void SetAwake (bool flag)
    utils::check_arg_count(L, 2);
    Body *body = Body_get_userdata_safe(L, 1);
    body->body->SetAwake(lua_toboolean(L, 2));
    return 0;
};

static int IsAwake(lua_State *L){ ///bool IsAwake () const
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    lua_pushboolean(L,body->body->IsAwake());
    return 1;
};

static int SetEnabled(lua_State *L){//void SetEnabled (bool flag)
    utils::check_arg_count(L, 2);
    Body *body = Body_get_userdata_safe(L, 1);
    body->body->SetEnabled(lua_toboolean(L, 2));
    return 0;
};

static int IsEnabled(lua_State *L){ //bool IsEnabled () const Get the active state of the body.
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    lua_pushboolean(L,body->body->IsEnabled());
    return 1;
};

static int SetFixedRotation(lua_State *L){//void SetFixedRotation (bool flag)
    utils::check_arg_count(L, 2);
    Body *body = Body_get_userdata_safe(L, 1);
    body->body->SetFixedRotation(lua_toboolean(L, 2));
    return 0;
};

static int IsFixedRotation(lua_State *L){ //bool IsFixedRotation () const Does this body have fixed rotation?
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    lua_pushboolean(L,body->body->IsFixedRotation());
    return 1;
};

static int GetNext(lua_State *L){ //const b2Body* GetNext () const Get the next body in the world's body list.
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    b2Body* body_new = body->body->GetNext();
    if(body_new == NULL){
        lua_pushnil(L);
    }else{
        Body* lua_body_new = (Body *)body_new->GetUserData().pointer;
        lua_body_new->Push(L);
    }
    return 1;
};


static int GetFixtureList(lua_State *L){//const b2Fixture* GetFixtureList () const Get the list of all fixtures attached to this body.
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    b2Fixture* fixture_top = body->body->GetFixtureList();
    if(fixture_top == NULL){
        lua_pushnil(L);
    }else{
        Fixture* lua_fixture_top = (Fixture *)fixture_top->GetUserData().pointer;
        lua_fixture_top->Push(L);
    }
    return 1;
}

static int GetJointList(lua_State *L){//b2JointEdge* GetJointList () Get the list of all joints attached to this body.GF
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    int i=0;
    for (b2JointEdge *jointEdge = body->body->GetJointList(); jointEdge; jointEdge=jointEdge->next) {
        Joint* joint_lua = (Joint *)jointEdge->joint->GetUserData().pointer;
        joint_lua->Push(L);
        lua_rawseti(L, -2, i+1);
        i++;
    }
    return 1;
}

static int GetContactList(lua_State *L){//const b2ContactEdge* GetContactList () const
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    int i=0;
    for (b2ContactEdge *contactEdge = body->body->GetContactList(); contactEdge; contactEdge=contactEdge->next) {
        Contact_from_b2Contact(contactEdge->contact)->Push(L);
        lua_rawseti(L, -2, i+1);
        i++;
    }
    return 1;
}



static int GetUserData(lua_State *L){//b2BodyUserData& GetUserData () Get the user data pointer that was provided in the body definition.
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    lua_rawgeti(L,LUA_REGISTRYINDEX,body->user_data_ref);
    return 1;
}

static int SetUserData(lua_State *L){//void SetUserData(void *data) Set the user data. Use this to store your application specific data.
    utils::check_arg_count(L, 2);
    Body *body = Body_get_userdata_safe(L, 1);
    if (lua_istable(L, 2)) {
        utils::unref(L, body->user_data_ref);
        body->user_data_ref = luaL_ref(L,LUA_REGISTRYINDEX);
    }else if (lua_isnil(L, 2)){
        utils::unref(L, body->user_data_ref);
        body->user_data_ref = LUA_REFNIL;
    }else {
        utils::error(L,"userdata can be only table or nil");
    }

    return 0;
}

static int GetWorld(lua_State *L){ //b2World* GetWorld () Get the parent world of this body
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    b2World* world = body->body->GetWorld();
    World* lua_world= World_find_by_pointer(world);
    lua_world->Push(L);
    return 1;
};

static int Dump(lua_State *L){//void Dump() Dump this body to a file.
    utils::check_arg_count(L, 1);
    Body *body = Body_get_userdata_safe(L, 1);
    body->body->Dump();
    return 0;
}
static int ToString(lua_State *L){
    utils::check_arg_count(L, 1);

    Body *lua_body = Body_get_userdata_safe(L, 1);
    lua_pushfstring( L, "b2Body[%p]",(void *) lua_body->body);
	return 1;
}

void BodyInitMetaTable(lua_State *L){
    int top = lua_gettop(L);

    luaL_Reg functions[] = {
        {"CreateFixture",CreateFixture},
        {"DestroyFixture",DestroyFixture},
        {"SetTransform",SetTransform},
        {"GetTransform",GetTransform},
        {"GetPosition",GetPosition},
        {"GetPositionRaw",GetPositionRaw},
        {"GetAngle",GetAngle},
        {"GetWorldCenter",GetWorldCenter},
        {"GetLocalCenter",GetLocalCenter},
        {"SetLinearVelocity",SetLinearVelocity},
        {"GetLinearVelocity",GetLinearVelocity},
        {"SetAngularVelocity",SetAngularVelocity},
        {"GetAngularVelocity",GetAngularVelocity},
        {"ApplyForce",ApplyForce},
        {"ApplyForceToCenter",ApplyForceToCenter},
        {"ApplyTorque",ApplyTorque},
        {"ApplyLinearImpulse",ApplyLinearImpulse},
        {"ApplyLinearImpulseToCenter",ApplyLinearImpulseToCenter},
        {"ApplyAngularImpulse",ApplyAngularImpulse},
        {"GetMass",GetMass},
        {"GetInertia",GetInertia},
        {"ResetMassData",ResetMassData},
        {"SetMassData",SetMassData},
        {"GetMassData",GetMassData},
        {"GetWorldPoint",GetWorldPoint},
        {"GetWorldVector",GetWorldVector},
        {"GetLocalPoint",GetLocalPoint},
        {"GetLocalVector",GetLocalVector},
        {"GetLinearVelocityFromLocalPoint",GetLinearVelocityFromLocalPoint},
        {"GetLinearVelocityFromWorldPoint",GetLinearVelocityFromWorldPoint},
        {"SetLinearDamping",SetLinearDamping},
        {"GetLinearDamping",GetLinearDamping},
        {"SetAngularDamping",SetAngularDamping},
        {"GetAngularDamping",GetAngularDamping},
        {"SetGravityScale",SetGravityScale},
        {"GetGravityScale",GetGravityScale},
        {"SetType",SetType},
        {"GetType",GetType},
        {"SetBullet",SetBullet},
        {"IsBullet",IsBullet},
        {"SetSleepingAllowed",SetSleepingAllowed},
        {"IsSleepingAllowed",IsSleepingAllowed},
        {"SetAwake",SetAwake},
        {"IsAwake",IsAwake},
        {"SetEnabled",SetEnabled},
        {"IsEnabled",IsEnabled},
        {"SetFixedRotation",SetFixedRotation},
        {"IsFixedRotation",IsFixedRotation},
        {"GetNext",GetNext},
        {"GetFixtureList",GetFixtureList},
        {"GetContactList",GetContactList},
        {"GetJointList",GetJointList},
        {"GetUserData",GetUserData},
        {"SetUserData",SetUserData},
        {"GetWorld",GetWorld},
        {"Dump",Dump},
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

void Body::Destroy(lua_State *L) {
    utils::unref(L, user_data_ref);
    user_data_ref = LUA_REFNIL;
    BaseUserData::Destroy(L);
    delete this;
}

void Body::DestroyFixtures(lua_State *L) {
    for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()){
        Fixture* fixture_lua = (Fixture *)f->GetUserData().pointer;
        fixture_lua->Destroy(L);
    }
}

void Body::DestroyJoints(lua_State *L) {
    for (b2JointEdge *jointEdge = body->GetJointList(); jointEdge; jointEdge=jointEdge->next) {
        Joint* joint_lua = (Joint *)jointEdge->joint->GetUserData().pointer;
        //do not delete it twice.
        if(joint_lua!=0){
            joint_lua->Destroy(L);
            jointEdge->joint->GetUserData().pointer = 0;
        }

    }
}

}


