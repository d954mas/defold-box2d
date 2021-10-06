#ifndef destruction_listener_h
#define destruction_listener_h

#include <box2d/box2d.h>
#include <dmsdk/sdk.h>
#include <extra_utils.h>
#include <contact.h>


namespace box2dDefoldNE {
class LuaDestructionListener : public b2DestructionListener {
public:
    int fun_say_goodbye_fixture;
    int fun_say_goodbye_joint;
    int defold_script_instance_ref;
    bool error;
    const char* error_message;

    LuaDestructionListener();
    ~LuaDestructionListener();

    void InitFromTable(lua_State *L, int index);
    void Destroy(lua_State *L);

    void SayGoodbye(b2Joint* joint);
    void SayGoodbye(b2Fixture* fixture);
};

}

#endif