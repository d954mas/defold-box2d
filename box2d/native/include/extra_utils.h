#ifndef extra_utils_h
#define extra_utils_h

#include <dmsdk/sdk.h>
#include <box2d/box2d.h>

namespace extra_utils {
	void table_get_b2vec(lua_State *L, const char *key, b2Vec2 *vector);
	b2Vec2 table_get_b2vec_safe(lua_State *L, const char *key, const char *error);
	b2Vec2 get_b2vec_safe(lua_State *L,int index, const char *error);
	b2Vec2 get_b2vec(lua_State *L,int index);
    void massData_to_table(lua_State *L, const b2MassData& massData);
}

#endif