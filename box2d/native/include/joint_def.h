#ifndef joint_def_h
#define joint_def_h

#include <box2d/box2d.h>
#include <dmsdk/sdk.h>




b2JointDef* b2JointDef_from_table(lua_State *L, int index);
#endif