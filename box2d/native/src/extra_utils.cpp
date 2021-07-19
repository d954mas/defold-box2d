#include "extra_utils.h"
#include "utils.h"

namespace extra_utils {
	void table_get_b2vec(lua_State *L, const char *key, b2Vec2 *vector) {
		Vectormath::Aos::Vector3 *v = utils::table_get_vector3(L, key, NULL);
		if (v != NULL) {
			vector->x = v->getX();
			vector->y = v->getY();
		}
	}

    b2Vec2 table_get_b2vec_safe(lua_State *L, const char *key, const char *error) {
        Vectormath::Aos::Vector3 *v = utils::table_get_vector3(L, key, NULL);
        b2Vec2 vector(0.0f, 0.0f);
        if (v != NULL) {
            vector.x = v->getX();
            vector.y = v->getY();
        }else{
            utils::error(L,error);
        }
        return vector;
    }

	b2Vec2 get_b2vec_safe(lua_State *L,int index, const char *error){
	    b2Vec2 vec2(0.0f, 0.0f);
        if (lua_isuserdata(L, index)) {
            if(dmScript::IsVector3(L,  index)){
                Vectormath::Aos::Vector3 *value = dmScript::ToVector3(L, index);
                vec2.x = value->getX();
                vec2.y = value->getY();
            }else{
                utils::error(L,error);
            }

        }else{
            utils::error(L,error);
        }
        return vec2;
	}

	b2Transform get_b2Transform_safe(lua_State *L,int index, const char *error){
        b2Transform transform;
        if (lua_istable(L, index)) {
            lua_pushvalue(L,index);

            transform.p = table_get_b2vec_safe(L,"p","p not vector3");

            lua_getfield(L, -1, "q");
            b2Rot rot = b2Rot(luaL_checknumber(L,-1));
            lua_pop(L,1);
            
            lua_pop(L,1);
        }else{
            utils::error(L,"b2Transform not table");
    	}
    	return transform;
    }

	void massData_to_table(lua_State *L, const b2MassData& massData){
        lua_newtable(L);
            lua_pushstring(L, "center");
            lua_newtable(L);
                lua_pushstring(L, "x");
                lua_pushnumber(L,massData.center.x);
                lua_settable(L,-3);
                lua_pushstring(L, "y");
                lua_pushnumber(L,massData.center.y);
                lua_settable(L,-3);
            lua_settable(L,-3);

            lua_pushstring(L, "mass");
            lua_pushnumber(L,massData.mass);
            lua_settable(L,-3);

            lua_pushstring(L, "I");
            lua_pushnumber(L,massData.I);
            lua_settable(L,-3);
	}
}