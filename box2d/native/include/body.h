#ifndef body_h
#define body_h

#include <box2d/box2d.h>
#include <dmsdk/sdk.h>
#include <extra_utils.h>

#include "world.h"

namespace box2dDefoldNE {

class Body  : public BaseUserData{
private:

public:
    int user_data_ref;
    b2Body *body;
    Body(b2Body *b);
    ~Body();
	virtual void Destroy(lua_State *L);
	void DestroyFixtures(lua_State *L);
	void DestroyJoints(lua_State *L);
};

void BodyInitMetaTable(lua_State *L);
Body* Body_get_userdata_safe(lua_State *L, int index);

}
#endif