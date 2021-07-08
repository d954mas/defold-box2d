#ifndef contact_listener_h
#define contact_listener_h

#include <box2d/box2d.h>
#include <dmsdk/sdk.h>
#include <extra_utils.h>
#include <contact.h>



class LuaContactListener : public b2ContactListener {
public:
    int fun_begin_contact_ref;
    int fun_end_contact_ref;
    int fun_preSolve_contact_ref;
    int fun_postSolve_contact_ref;
    int defold_script_instance_ref;
    Contact *contact;
    lua_State *L;
    bool error;
    const char* error_message;
    LuaContactListener();
    ~LuaContactListener();
    void InitFromTable(lua_State *L, int index);
    void EndListen(lua_State *L);
    void Destroy(lua_State *L);
    // b2ContactListener
    void BeginContact(b2Contact *contact);
    void EndContact(b2Contact *contact);
    void PreSolve(b2Contact *contact, const b2Manifold *old_manifold);
    void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);
};

#endif