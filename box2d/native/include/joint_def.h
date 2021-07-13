#ifndef joint_def_h
#define joint_def_h

#include <box2d/box2d.h>
#include <dmsdk/sdk.h>


namespace box2dDefoldNE {
b2JointDef* b2JointDef_from_table(lua_State *L, int index);

void b2JointDef_to_table(lua_State *L, b2JointDef* def);

}

#endif