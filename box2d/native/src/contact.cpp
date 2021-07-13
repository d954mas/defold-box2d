#include "contact.h"
#include "utils.h"
#include "fixture.h"
#include "manifold.h"

#define META_NAME "Box2d::ContactClass"
#define USERDATA_NAME "__userdata_contact"

Contact::Contact(b2Contact *c){
    contact = c;
    reuse = false;
    table_ref = LUA_REFNIL;
}

Contact::~Contact() {

}

Contact* Contact_get_userdata(lua_State *L, int index) {
    int top = lua_gettop(L);

	Contact *lua_contact = NULL;
	lua_getfield(L, index, USERDATA_NAME);
	if (lua_islightuserdata(L, -1)) {
		lua_contact = (Contact *)lua_touserdata(L, -1);
		if(lua_contact->contact == NULL){
            lua_contact = NULL;
        }
	}
	lua_pop(L, 1);

    assert(top == lua_gettop(L));
    return lua_contact;
}

Contact* Contact_get_userdata_safe(lua_State *L, int index) {
    Contact *lua_contact = Contact_get_userdata(L, index);
    if (lua_contact == NULL) {
        utils::error(L,"Contact already destroyed");
    }
	return lua_contact;
}

static int GetManifold(lua_State *L){///const b2Manifold* GetManifold() const;]
    utils::check_arg_count(L, 1);
    Contact *contact = Contact_get_userdata_safe(L, 1);
    manifold_to_table(L, contact->contact->GetManifold());
    return 1;
}

static int GetWorldManifold(lua_State *L){///void GetWorldManifold(b2WorldManifold* worldManifold) const;
    utils::check_arg_count(L, 1);
    Contact *contact = Contact_get_userdata_safe(L, 1);
    b2WorldManifold manifold;
    contact->contact->GetWorldManifold(&manifold);
    world_manifold_to_table(L, &manifold,  contact->contact->GetManifold()->pointCount);
    return 1;
}
/// Is this contact touching?
static int IsTouching(lua_State *L){///	bool IsTouching() const;
    utils::check_arg_count(L, 1);
    Contact *contact = Contact_get_userdata_safe(L, 1);
    lua_pushboolean(L,contact->contact->IsTouching());
    return 1;
}
/// Enable/disable this contact. This can be used inside the pre-solve
/// contact listener. The contact is only disabled for the current
/// time step (or sub-step in continuous collisions).
static int SetEnabled(lua_State *L){///	void SetEnabled(bool flag);
    utils::check_arg_count(L, 2);
    Contact *contact = Contact_get_userdata_safe(L, 1);
    bool flag = lua_toboolean(L,2);
    contact->contact->SetEnabled(flag);
    return 0;
}

/// Has this contact been disabled?
static int IsEnabled(lua_State *L){///	bool IsEnabled() const;
    utils::check_arg_count(L, 1);
    Contact *contact = Contact_get_userdata_safe(L, 1);
    lua_pushboolean(L,contact->contact->IsEnabled());
    return 1;
}

/// Get fixture A in this contact.
static int GetFixtureA(lua_State *L){///b2Fixture* GetFixtureA();
    utils::check_arg_count(L, 1);
    Contact *contact = Contact_get_userdata_safe(L, 1);
    Fixture_from_b2Fixture(contact->contact->GetFixtureA())->Push(L);
    return 1;
}

/// Get the child primitive index for fixture A.
static int GetChildIndexA(lua_State *L){///int32 GetChildIndexA() const;
    utils::check_arg_count(L, 1);
    Contact *contact = Contact_get_userdata_safe(L, 1);
    lua_pushnumber(L, contact->contact->GetChildIndexA());
    return 1;
}
	/// Get fixture B in this contact.
static int GetFixtureB(lua_State *L){///	b2Fixture* GetFixtureB();
    utils::check_arg_count(L, 1);
    Contact *contact = Contact_get_userdata_safe(L, 1);
    Fixture_from_b2Fixture(contact->contact->GetFixtureB())->Push(L);
    return 1;
}
	/// Get the child primitive index for fixture B.
static int GetChildIndexB(lua_State *L){///	int32 GetChildIndexB() const;
    utils::check_arg_count(L, 1);
    Contact *contact = Contact_get_userdata_safe(L, 1);
    lua_pushnumber(L, contact->contact->GetChildIndexB());
    return 1;
}

/// Override the default friction mixture. You can call this in b2ContactListener::PreSolve.
/// This value persists until set or reset.
static int SetFriction(lua_State *L){///	void SetFriction(float friction);
    utils::check_arg_count(L, 2);
    float friction = luaL_checknumber(L,2);
    Contact *contact = Contact_get_userdata_safe(L, 1);
    contact->contact->SetFriction(friction);
    return 0;
}

/// Get the friction.
static int GetFriction(lua_State *L){///	float GetFriction() const;
    utils::check_arg_count(L, 1);
    Contact *contact = Contact_get_userdata_safe(L, 1);
    lua_pushnumber(L, contact->contact->GetFriction());
    return 1;
}

/// Reset the friction mixture to the default value.
static int ResetFriction(lua_State *L){///	void ResetFriction();
    utils::check_arg_count(L, 1);
    Contact *contact = Contact_get_userdata_safe(L, 1);
    contact->contact->ResetFriction();
    return 0;
}

/// Override the default restitution mixture. You can call this in b2ContactListener::PreSolve.
/// The value persists until you set or reset.
static int SetRestitution(lua_State *L){///	void SetRestitution(float restitution);
    utils::check_arg_count(L, 2);
    float restitution = luaL_checknumber(L,2);
    Contact *contact = Contact_get_userdata_safe(L, 1);
    contact->contact->SetRestitution(restitution);
    return 0;
}

/// Get the restitution.
static int GetRestitution(lua_State *L){///	float GetRestitution() const;
    utils::check_arg_count(L, 1);
    Contact *contact = Contact_get_userdata_safe(L, 1);
    lua_pushnumber(L, contact->contact->GetRestitution());
    return 1;
}

/// Reset the restitution to the default value.
static int ResetRestitution(lua_State *L){///	void ResetRestitution();
    utils::check_arg_count(L, 1);
    Contact *contact = Contact_get_userdata_safe(L, 1);
    contact->contact->ResetRestitution();
    return 0;
}

/// Override the default restitution velocity threshold mixture. You can call this in b2ContactListener::PreSolve.
/// The value persists until you set or reset.
static int SetRestitutionThreshold(lua_State *L){///	void SetRestitutionThreshold(float threshold);
    utils::check_arg_count(L, 2);
    float threshold = luaL_checknumber(L,2);
    Contact *contact = Contact_get_userdata_safe(L, 1);
    contact->contact->SetRestitutionThreshold(threshold);
    return 0;
}

/// Get the restitution threshold.
static int GetRestitutionThreshold(lua_State *L){///	float GetRestitutionThreshold() const;
    utils::check_arg_count(L, 1);
    Contact *contact = Contact_get_userdata_safe(L, 1);
    lua_pushnumber(L, contact->contact->GetRestitutionThreshold());
    return 1;
}

/// Reset the restitution threshold to the default value.
static int ResetRestitutionThreshold(lua_State *L){///	void ResetRestitutionThreshold();
    utils::check_arg_count(L, 1);
    Contact *contact = Contact_get_userdata_safe(L, 1);
    contact->contact->ResetRestitutionThreshold();
    return 0;
}

/// Set the desired tangent speed for a conveyor belt behavior. In meters per second.
static int SetTangentSpeed(lua_State *L){///	void SetTangentSpeed(float speed);
    utils::check_arg_count(L, 2);
    float speed = luaL_checknumber(L,2);
    Contact *contact = Contact_get_userdata_safe(L, 1);
    contact->contact->SetTangentSpeed(speed);
    return 0;
}

/// Get the desired tangent speed. In meters per second.
static int GetTangentSpeed(lua_State *L){///	float GetTangentSpeed() const;
    utils::check_arg_count(L, 1);
    Contact *contact = Contact_get_userdata_safe(L, 1);
    lua_pushnumber(L, contact->contact->GetTangentSpeed());
    return 1;
}

static int ToString(lua_State *L){
    utils::check_arg_count(L, 1);

    Contact *lua_contact = Contact_get_userdata_safe(L, 1);
    lua_pushfstring( L, "b2Contact[%p]",(void *) lua_contact->contact);
	return 1;
}

void ContactInitMetaTable(lua_State *L){
    int top = lua_gettop(L);

    luaL_Reg functions[] = {
        {"GetManifold",GetManifold},
        {"GetWorldManifold",GetWorldManifold},
        {"IsTouching",IsTouching},
        {"SetEnabled",SetEnabled},
        {"IsEnabled",IsEnabled},
        {"GetFixtureA",GetFixtureA},
        {"GetChildIndexA",GetChildIndexA},
        {"GetFixtureB",GetFixtureB},
        {"GetChildIndexB",GetChildIndexB},
        {"SetFriction",SetFriction},
        {"GetFriction",GetFriction},
        {"ResetFriction",ResetFriction},
        {"SetRestitution",SetRestitution},
        {"GetRestitution",GetRestitution},
        {"ResetRestitution",ResetRestitution},
        {"SetRestitutionThreshold",SetRestitutionThreshold},
        {"GetRestitutionThreshold",GetRestitutionThreshold},
        {"ResetRestitutionThreshold",ResetRestitutionThreshold},
        {"SetTangentSpeed",SetTangentSpeed},
        {"GetTangentSpeed",GetTangentSpeed},
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



void Contact::Push(lua_State *L) {
    DM_LUA_STACK_CHECK(L, 1);
    if(table_ref == LUA_REFNIL){
        // contact
        lua_createtable(L, 0, 1);
        // contact.__userdata
        lua_pushlightuserdata(L, this);
        lua_setfield(L, -2, USERDATA_NAME);

        luaL_getmetatable(L, META_NAME);
        lua_setmetatable(L, -2);

        lua_pushvalue(L, -1);
        table_ref = luaL_ref(L,LUA_REGISTRYINDEX);
     }else{
        lua_rawgeti(L,LUA_REGISTRYINDEX,table_ref);
     }
}

void Contact::Reuse(b2Contact* c) {
   contact = c;
}

void Contact::Destroy(lua_State *L) {
    if(contact != NULL && !reuse){
        contact = NULL;
        DestroyTable(L);
        delete this;
    }
}

void Contact::DestroyTable(lua_State *L) {
    if(table_ref != LUA_REFNIL){
        lua_rawgeti(L,LUA_REGISTRYINDEX,table_ref);
        lua_pushnil(L);
        lua_setfield(L, -2, USERDATA_NAME);
        lua_pop(L,1);


        utils::unref(L, table_ref);
        table_ref = LUA_REFNIL;
    }
}


