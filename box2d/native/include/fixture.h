#ifndef fixture_h
#define fixture_h

#include <box2d/box2d.h>
#include <dmsdk/sdk.h>
#include <extra_utils.h>




class Fixture {
private:

public:
    int user_data_ref;
    int table_ref; //always return same table
    b2Fixture *fixture;
    Fixture(b2Fixture *f);
    ~Fixture();
	void Push(lua_State *L);
    void Destroy(lua_State *L);
};

void FixtureInitMetaTable(lua_State *L);
Fixture* Fixture_get_userdata(lua_State *L, int index);
Fixture* Fixture_get_userdata_safe(lua_State *L, int index);
#endif