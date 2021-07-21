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
    b2MassData get_b2MassData_safe(lua_State *L,int index, const char *error);
    b2Transform get_b2Transform_safe(lua_State *L,int index, const char *error);
    void b2Transform_push(lua_State *L,b2Transform transform);
    b2AABB get_b2AABB_safe(lua_State *L,int index, const char *error);
    void b2AABB_push(lua_State *L, b2AABB aabb);
    void b2RayCastOutput_push(lua_State *L, b2RayCastOutput output);
    b2RayCastInput get_b2RayCastInput_safe(lua_State *L, int index);
    b2Vec2* parse_vertices(lua_State *L, int index, int* b2vecSize);
}

#endif