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
            transform.q = b2Rot(luaL_checknumber(L,-1));
            lua_pop(L,1);
            
            lua_pop(L,1);
        }else{
            utils::error(L,"b2Transform not table");
    	}
    	return transform;
    }

    void b2Transform_push(lua_State *L,b2Transform transform){
        lua_newtable(L);
        utils::push_vector(L, transform.p.x, transform.p.y, 0);
        lua_setfield(L, -2, "p");
        lua_pushnumber(L, transform.q.GetAngle());
        lua_setfield(L, -2, "q");
    }

    b2AABB get_b2AABB_safe(lua_State *L,int index, const char *error){
        b2AABB aabb;
        if (lua_istable(L, index)) {
            lua_pushvalue(L,index);
            aabb.lowerBound = extra_utils::table_get_b2vec_safe(L,"lowerBound","lowerBound not vector3");
            aabb.upperBound = extra_utils::table_get_b2vec_safe(L,"upperBound","upperBound not vector3");
            lua_pop(L,1);
        }else{
            utils::error(L,"b2AABB not table");
        }
        return aabb;
    }

    b2MassData get_b2MassData_safe(lua_State *L,int index, const char *error){
        b2MassData massData;
        if (lua_istable(L, index)) {
            lua_pushvalue(L,index);
            lua_getfield(L, -1, "mass");
            if (lua_isnumber(L, -1)) {
                massData.mass = lua_tonumber(L, -1);
                lua_pop(L, 1);
            }else{
                utils::error(L,"mass not number");
            }

            lua_getfield(L, -1, "I");
            if (lua_isnumber(L, -1)) {
                massData.I = lua_tonumber(L, -1);
                lua_pop(L, 1);
            }else{
                utils::error(L,"I not number");
            }


            lua_getfield(L, -1, "center");
            if (lua_istable(L, -1)) {
                lua_getfield(L, -1, "x");
                if (lua_isnumber(L, -1)) {
                    massData.center.x = lua_tonumber(L, -1);
                    lua_pop(L, 1);
                }else{
                    utils::error(L,"x not number");
                }

                lua_getfield(L, -1, "y");
                if (lua_isnumber(L, -1)) {
                    massData.center.y = lua_tonumber(L, -1);
                    lua_pop(L, 1);
                }else{
                     utils::error(L,"y not number");
                }
                lua_pop(L, 1);
            }else{
                utils::error(L,"center not table");
            }

        }else{
            utils::error(L,"b2MassData not table");
        }
        return massData;
    }

    void b2AABB_push(lua_State *L, b2AABB aabb){
        lua_newtable(L);
        utils::push_vector(L, aabb.lowerBound.x, aabb.lowerBound.y, 0);
        lua_setfield(L, -2, "lowerBound");
        utils::push_vector(L, aabb.upperBound.x, aabb.upperBound.y, 0);
        lua_setfield(L, -2, "upperBound");
    }

    void b2RayCastOutput_push(lua_State *L, b2RayCastOutput output){
        lua_newtable(L);
        utils::push_vector(L, output.normal.x, output.normal.y, 0);
        lua_setfield(L, -2, "normal");
        lua_pushnumber(L, output.fraction);
        lua_setfield(L, -2, "fraction");
    }


    b2RayCastInput get_b2RayCastInput_safe(lua_State *L, int index){
        b2RayCastInput input;
        if (lua_istable(L, index)) {
            lua_pushvalue(L,index);
            input.p1 = extra_utils::table_get_b2vec_safe(L,"p1","b2RayCastInput.p1 not vector3");
            input.p2 = extra_utils::table_get_b2vec_safe(L,"p2","b2RayCastInput.p2 not vector3");
            input.maxFraction = utils::table_get_double_safe(L,"maxFraction","b2RayCastInput.maxFraction not number");
            lua_pop(L,1);
        }else{
            utils::error(L,"b2RayCastInput not table");
        }
        return input;
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

	b2Vec2* parse_vertices(lua_State *L, int index, int* b2vecSize){
        if(lua_istable(L,index)){
            lua_pushvalue(L,index);
            int size = lua_objlen(L,-1);
            b2Vec2* vertices = new b2Vec2[size];
            *b2vecSize = size;
            for (int idx = 1; idx <= size; idx++) {
                lua_pushinteger(L, idx);
                lua_gettable(L, -2);
                if (lua_isuserdata(L, -1)) {
                    if(dmScript::IsVector3(L,  -1)){
                        Vectormath::Aos::Vector3 *value = dmScript::ToVector3(L, -1);
                        b2Vec2 v;
                        v.x = value->getX();
                        v.y = value->getY();
                        vertices[idx-1] = v;
                    }else{
                        delete[] vertices;
                        utils::error(L,"vertex not vector3");
                    }
                }else{
                    delete[] vertices;
                    utils::error(L,"vertex not vector3");
                }
                lua_pop(L, 1);
            }
            lua_pop(L,1);
            return vertices;
        }else{
           utils::error(L,"vertices not table");
        }
    }
}