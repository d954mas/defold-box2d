#include "fixture.h"
#include "utils.h"
#include "body.h"
#include "filter.h"
#include "shape.h"

#define META_NAME "Box2d::FixtureClass"
#define USERDATA_TYPE "fixture"

namespace box2dDefoldNE {
Fixture::Fixture(b2Fixture *f) :BaseUserData(USERDATA_TYPE){
    user_data_ref = LUA_REFNIL;
    fixture = f;
    b2FixtureUserData& userdata = fixture->GetUserData();
    userdata.pointer = (uintptr_t)(void*) this;

    this->box2dObj = f;
    this->metatable_name = META_NAME;
}

Fixture::~Fixture() {

}


Fixture* Fixture_get_userdata_safe(lua_State *L, int index) {
    Fixture *lua_fixture = (Fixture*) BaseUserData_get_userdata(L, index, USERDATA_TYPE);
	return lua_fixture;
}

Fixture* Fixture_from_b2Fixture(b2Fixture *fixture){
    return (Fixture *)fixture->GetUserData().pointer;
}

static int GetType(lua_State *L){ //b2Shape::Type GetType() const
    utils::check_arg_count(L, 1);
    Fixture *fixture = Fixture_get_userdata_safe(L, 1);
    lua_pushnumber(L, fixture->fixture->GetType());
    return 1;
}

static int GetShape(lua_State *L){ //b2Shape::Type GetType() const
    utils::check_arg_count(L, 1);
    Fixture *fixture = Fixture_get_userdata_safe(L, 1);
    b2Shape_push(L,fixture->fixture->GetShape());
    return 1;
}

static int SetSensor(lua_State *L){ //void SetSensor(bool sensor)Set if this fixture is a sensor.
    utils::check_arg_count(L, 2);
    Fixture *fixture = Fixture_get_userdata_safe(L, 1);
    fixture->fixture->SetSensor(lua_toboolean(L,2));
    return 0;
}

static int IsSensor(lua_State *L){ //bool IsSensor () const
    utils::check_arg_count(L, 1);
    Fixture *fixture = Fixture_get_userdata_safe(L, 1);
    lua_pushboolean(L,fixture->fixture->IsSensor());
    return 1;
}


static int SetFilterData(lua_State *L){//void SetFilterData (const b2Filter &filter)
    utils::check_arg_count(L, 2);
    Fixture *fixture = Fixture_get_userdata_safe(L, 1);
    b2Filter filter = b2Filter_from_table(L,2);
    fixture->fixture->SetFilterData(filter);
    return 0;
}
static int GetFilterData(lua_State *L){//const b2Filter & GetFilterData () constGet the contact filtering data.
    utils::check_arg_count(L, 1);
    Fixture *fixture = Fixture_get_userdata_safe(L, 1);
    b2Filter_to_table(L,fixture->fixture->GetFilterData());
    return 1;
}
static int Refilter(lua_State *L){ //void Refilter () Call this if you want to establish collision that was previously disabled by b2ContactFilter::ShouldCollide.
    utils::check_arg_count(L, 1);
    Fixture *fixture = Fixture_get_userdata_safe(L, 1);
    fixture->fixture->Refilter();
    return 0;
}

static int GetBody(lua_State *L){ //const b2Body * GetBody () const
    utils::check_arg_count(L, 1);
    Fixture *fixture = Fixture_get_userdata_safe(L, 1);
    b2Body* body = fixture->fixture->GetBody();
    if(body == NULL){
        lua_pushnil(L);
    }else{
        Body* lua_body = (Body *)body->GetUserData().pointer;
        lua_body->Push(L);
    }
    return 1;
}

static int GetNext(lua_State *L){ //const b2Fixture * GetNext () const
    utils::check_arg_count(L, 1);
    Fixture *fixture = Fixture_get_userdata_safe(L, 1);
    b2Fixture* fixture_new = fixture->fixture->GetNext();
    if(fixture_new == NULL){
        lua_pushnil(L);
    }else{
        Fixture* lua_fixture = (Fixture *)fixture_new->GetUserData().pointer;
        lua_fixture->Push(L);
    }
    return 1;
}

static int GetUserData(lua_State *L){//b2BodyUserData& GetUserData () Get the user data pointer that was provided in the body definition.
    utils::check_arg_count(L, 1);
    Fixture *fixture = Fixture_get_userdata_safe(L, 1);
    lua_rawgeti(L,LUA_REGISTRYINDEX,fixture->user_data_ref);
    return 1;
}
static int SetUserData(lua_State *L){//void SetUserData(void *data) Set the user data. Use this to store your application specific data.
    utils::check_arg_count(L, 2);
    Fixture *fixture = Fixture_get_userdata_safe(L, 1);
    if (lua_istable(L, 2)) {
        utils::unref(L, fixture->user_data_ref);
        fixture->user_data_ref = luaL_ref(L,LUA_REGISTRYINDEX);
    }else if (lua_isnil(L, 2)){
        utils::unref(L, fixture->user_data_ref);
        fixture->user_data_ref = LUA_REFNIL;
    }else {
        utils::error(L,"userdata can be only table or nil");
    }

    return 0;
}

static int TestPoint(lua_State *L){ //bool TestPoint (const b2Vec2 &p) const
    utils::check_arg_count(L, 2);
    Fixture *fixture = Fixture_get_userdata_safe(L, 1);
    b2Vec2 p = extra_utils::get_b2vec_safe(L,2,"point is not vector3");
    lua_pushboolean(L,fixture->fixture->TestPoint(p));
    return 1;
}

static int RayCast(lua_State* L){
    utils::check_arg_count(L, 3);
    Fixture *fixture = Fixture_get_userdata_safe(L,1);
    b2RayCastInput  input = extra_utils::get_b2RayCastInput_safe(L,2);
    int childIndex = luaL_checknumber(L,3);
    b2RayCastOutput output;
    output.fraction = -1;
    output.normal.x = 0;
    output.normal.y = 0;
    bool result = fixture->fixture->RayCast(&output,input,childIndex);
    if(result){
        extra_utils::b2RayCastOutput_push(L,output);
    }else{
        lua_pushnil(L);
    }
    return 1;
}

//copy paste in body
static int GetMassData(lua_State *L) { //void GetMassData (b2MassData *data) const
	utils::check_arg_count(L, 1);
	Fixture *fixture =  Fixture_get_userdata_safe(L, 1);
    b2MassData massData;
    fixture->fixture->GetMassData(&massData);
    extra_utils::massData_to_table(L,massData);
    return 1;
}

static int GetDensity(lua_State *L){//float GetDensity () const Get the density of this fixture.
    utils::check_arg_count(L, 1);
    Fixture *fixture =  Fixture_get_userdata_safe(L, 1);
    lua_pushnumber(L,fixture->fixture->GetDensity());
    return 1;
}

static int SetDensity(lua_State *L){//void SetDensity (float density)
    utils::check_arg_count(L, 2);
    Fixture *fixture =  Fixture_get_userdata_safe(L, 1);
    fixture->fixture->SetDensity(lua_tonumber(L, 2));
    return 0;
}

static int GetFriction(lua_State *L){//float GetFriction () const Get the coefficient of friction.
    utils::check_arg_count(L, 1);
    Fixture *fixture =  Fixture_get_userdata_safe(L, 1);
    lua_pushnumber(L,fixture->fixture->GetFriction());
    return 1;
}

static int SetFriction(lua_State *L){//void SetFriction (float friction)
    utils::check_arg_count(L, 2);
    Fixture *fixture =  Fixture_get_userdata_safe(L, 1);
    fixture->fixture->SetFriction(lua_tonumber(L, 2));
    return 0;
}

static int GetRestitution(lua_State *L){//float GetRestitution () constGet the coefficient of restitution.
    utils::check_arg_count(L, 1);
    Fixture *fixture =  Fixture_get_userdata_safe(L, 1);
    lua_pushnumber(L,fixture->fixture->GetRestitution());
    return 1;
}

static int SetRestitution(lua_State *L){//void SetRestitution (float restitution)
    utils::check_arg_count(L, 2);
    Fixture *fixture =  Fixture_get_userdata_safe(L, 1);
    fixture->fixture->SetRestitution(lua_tonumber(L, 2));
    return 0;
}


static int GetRestitutionThreshold(lua_State *L){//float GetRestitutionThreshold () const Get the restitution velocity threshold.
    utils::check_arg_count(L, 1);
    Fixture *fixture =  Fixture_get_userdata_safe(L, 1);
    lua_pushnumber(L,fixture->fixture->GetRestitutionThreshold());
    return 1;
}

static int SetRestitutionThreshold(lua_State *L){//void SetRestitutionThreshold (float threshold)
    utils::check_arg_count(L, 2);
    Fixture *fixture =  Fixture_get_userdata_safe(L, 1);
    fixture->fixture->SetRestitutionThreshold(lua_tonumber(L, 2));
    return 0;
}

static int GetAABB(lua_State* L){
    utils::check_arg_count(L, 2);
    Fixture *fixture =  Fixture_get_userdata_safe(L, 1);
    int childIndex = luaL_checknumber(L,2);
    b2AABB aabb = fixture->fixture->GetAABB(childIndex);
    extra_utils::b2AABB_push(L,aabb);
    return 1;
}


static int Dump(lua_State *L){//void Dump (int32 bodyIndex)Dump this fixture to the log file.
    utils::check_arg_count(L, 2);
    Fixture *fixture =  Fixture_get_userdata_safe(L, 1);
    fixture->fixture->Dump(lua_tointeger(L, 2));
    return 0;
}


static int ToString(lua_State *L){
    utils::check_arg_count(L, 1);

    Fixture *lua_fixture = Fixture_get_userdata_safe(L, 1);
    lua_pushfstring( L, "b2Fixture[%p]",(void *) lua_fixture->fixture);
	return 1;
}

void FixtureInitMetaTable(lua_State *L){
    int top = lua_gettop(L);

    luaL_Reg functions[] = {
        {"GetType",GetType},
        {"GetShape",GetShape},
        {"SetSensor",SetSensor},
        {"IsSensor",IsSensor},
        {"SetFilterData",SetFilterData},
        {"GetFilterData",GetFilterData},
        {"Refilter",Refilter},
        {"GetBody",GetBody},
        {"GetNext",GetNext},
        {"GetUserData",GetUserData},
        {"SetUserData",SetUserData},
        {"TestPoint",TestPoint},
        {"RayCast",RayCast},
        {"GetMassData",GetMassData},
        {"GetDensity",GetDensity},
        {"SetDensity",SetDensity},
        {"GetFriction",GetFriction},
        {"SetFriction",SetFriction},
        {"GetRestitution",GetRestitution},
        {"SetRestitution",SetRestitution},
        {"GetRestitutionThreshold",GetRestitutionThreshold},
        {"SetRestitutionThreshold",SetRestitutionThreshold},
        {"GetAABB",GetAABB},
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


void Fixture::Destroy(lua_State *L) {
    utils::unref(L, user_data_ref);
    user_data_ref = LUA_REFNIL;
    BaseUserData::Destroy(L);
    delete this;
}

}

