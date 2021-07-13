#ifndef body_h
#define body_h

#include <box2d/box2d.h>
#include <dmsdk/sdk.h>
#include <extra_utils.h>

#include "world.h"

namespace box2dDefoldNE {

class Body {
private:

public:
    int user_data_ref;
    int table_ref; //always return same table
    b2Body *body;
    Body(b2Body *b);
    ~Body();
	void Push(lua_State *L);
	void Destroy(lua_State *L);
	void DestroyFixtures(lua_State *L);
	void DestroyJoints(lua_State *L);
};

void BodyInitMetaTable(lua_State *L);
Body* Body_get_userdata(lua_State *L, int index);
Body* Body_get_userdata_safe(lua_State *L, int index);

}
#endif