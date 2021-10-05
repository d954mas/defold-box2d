#ifndef joint_h
#define joint_h

#include <box2d/box2d.h>
#include <dmsdk/sdk.h>
#include <extra_utils.h>
#include "base_userdata.h"

namespace box2dDefoldNE {


class Joint : public BaseUserData {
private:

public:
    int user_data_ref;
    b2Joint *joint;
    Joint(b2Joint *j);
    ~Joint();
	virtual void Destroy(lua_State *L);
};

void JointInitMetaTable(lua_State *L);
Joint* Joint_get_userdata_safe(lua_State *L, int index);
#endif

}