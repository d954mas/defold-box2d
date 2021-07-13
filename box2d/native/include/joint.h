#ifndef joint_h
#define joint_h

#include <box2d/box2d.h>
#include <dmsdk/sdk.h>
#include <extra_utils.h>

namespace box2dDefoldNE {


class Joint {
private:

public:
    int user_data_ref;
    int table_ref; //always return same table
    b2Joint *joint;
    Joint(b2Joint *j);
    ~Joint();
	void Push(lua_State *L);
    void Destroy(lua_State *L);
};

void JointInitMetaTable(lua_State *L);
Joint* Joint_get_userdata(lua_State *L, int index);
Joint* Joint_get_userdata_safe(lua_State *L, int index);
#endif

}