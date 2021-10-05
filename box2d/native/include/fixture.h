#ifndef fixture_h
#define fixture_h

#include <box2d/box2d.h>
#include <dmsdk/sdk.h>
#include <extra_utils.h>
#include <base_userdata.h>

namespace box2dDefoldNE {

class Fixture: public BaseUserData {
private:

public:
    int user_data_ref;
    b2Fixture *fixture;
    Fixture(b2Fixture *f);
    ~Fixture();
    virtual void Destroy(lua_State *L);
};

void FixtureInitMetaTable(lua_State *L);
Fixture* Fixture_get_userdata_safe(lua_State *L, int index);
Fixture* Fixture_from_b2Fixture(b2Fixture *fixture);

}

#endif