#include <string>
#include <queue>

#include "utils.h"

static bool is_debug = false;

static char *copy_string(const char *source) {
	if (source != NULL) {
		size_t length = strlen(source) + 1;
		char *destination = new char[length];
		strncpy(destination, source, length);
		destination[length - 1] = 0;
		return destination;
	}
	return NULL;
}

namespace utils {
	uint64_t get_time() {
		#ifdef _SYS_TIME_H_
			timeval tv;
			gettimeofday(&tv, 0);
			return ((uint64_t) tv.tv_sec) * 1000000U + tv.tv_usec;
		#else
			return 0;
		#endif
	}

	void enable_debug() {
		is_debug = true;
	}

	void check_arg_count(lua_State *L, int count_exact) {
		int count = lua_gettop(L);
		if (count != count_exact) {
			luaL_error(L, "This function requires %d arguments. Got %d.", count_exact, count);
		}
	}

	void check_arg_count(lua_State *L, int count_from, int count_to) {
		int count = lua_gettop(L);
		if (count < count_from || count > count_to) {
			luaL_error(L, "This function requires from %d to %d arguments. Got %d.", count_from, count_to, count);
		}
	}

	void get_table(lua_State *L, int index) {
		if (!lua_istable(L, index)) {
			luaL_error(L, "Missing parameters table argument.");
		}
		lua_pushvalue(L, index);
	}

	// String.
	const char *table_get_string(lua_State *L, const char *key, const char *default_value) {
		lua_getfield(L, -1, key);
		const char *value = default_value;
		if (lua_isstring(L, -1)) {
			value = lua_tostring(L, -1);
		}
		lua_pop(L, 1);
		return value;
	}

	void table_get_stringp_value(lua_State *L, const char *key, char **value, const char *default_value, bool not_null) {
		if (*value != NULL) {
			delete []*value;
			*value = NULL;
		}
		lua_getfield(L, -1, key);
		int value_type = lua_type(L, -1);
		if (value_type == LUA_TSTRING) {
			size_t length;
			const char *lua_string = lua_tolstring(L, -1, &length);
			++length; // Adding null terminator.
			*value = new char[length];
			strncpy(*value, lua_string, length);
			(*value)[length - 1] = 0;
		} else if (value_type == LUA_TNIL && default_value != NULL) {
			size_t length = strlen(default_value) + 1; // Adding null terminator.
			*value = new char[length];
			strncpy(*value, default_value, length);
			(*value)[length - 1] = 0;
		}
		lua_pop(L, 1);
		if (*value == NULL && not_null) {
			luaL_error(L, "Table's property %s is not a string.", key);
		}
	}

	void table_get_stringp(lua_State *L, const char *key, char **value) {
		table_get_stringp_value(L, key, value, NULL, false);
	}

	void table_get_stringp(lua_State *L, const char *key, char **value, const char *default_value) {
		if (default_value != NULL) {
			table_get_stringp_value(L, key, value, default_value, false);
		} else {
			dmLogError("table_get_string: default value is NULL for key %s", key);
		}
	}

	void table_get_stringp_not_null(lua_State *L, const char *key, char **value) {
		table_get_stringp_value(L, key, value, NULL, true);
	}

	// Integer.
	int table_get_integer(lua_State *L, const char *key, int default_value) {
		lua_getfield(L, -1, key);
		int value = default_value;
		if (lua_isnumber(L, -1)) {
			value = lua_tointeger(L, -1);
		}
		lua_pop(L, 1);
		return value;
	}

	int table_get_integer_safe(lua_State *L, const char *key, const char *error_message) {
        lua_getfield(L, -1, key);
        if (lua_isnumber(L, -1)) {
            int value = lua_tointeger(L, -1);
            lua_pop(L, 1);
            return value;
        }else{
            error(L,error_message);
        }

        return 0;
    }

	void table_get_integerp_value(lua_State *L, const char *key, int **value, int *default_value, bool not_null) {
		if (*value != NULL) {
			delete *value;
			*value = NULL;
		}
		lua_getfield(L, -1, key);
		int value_type = lua_type(L, -1);
		if (value_type == LUA_TNUMBER) {
			lua_Number lua_number = lua_tonumber(L, -1);
			*value = new int((int)lua_number);
		} else if (value_type == LUA_TNIL && default_value != NULL) {
			*value = new int(*default_value);
		}
		lua_pop(L, 1);
		if (*value == NULL && not_null) {
			luaL_error(L, "Table's property %s is not a number.", key);
		}
	}

	void table_get_integerp(lua_State *L, const char *key, int **value) {
		table_get_integerp_value(L, key, value, NULL, false);
	}

	void table_get_integerp(lua_State *L, const char *key, int **value, int default_value) {
		table_get_integerp_value(L, key, value, &default_value, false);
	}

	void table_get_integerp_not_null(lua_State *L, const char *key, int **value) {
		table_get_integerp_value(L, key, value, NULL, true);
	}

	// Double.
	double table_get_double(lua_State *L, const char *key, double default_value) {
		lua_getfield(L, -1, key);
		double value = default_value;
		if (lua_isnumber(L, -1)) {
			value = lua_tonumber(L, -1);
		}
		lua_pop(L, 1);
		return value;
	}

	double table_get_double_safe(lua_State *L, const char *key, const char *error_message) {
        lua_getfield(L, -1, key);
        if (lua_isnumber(L, -1)) {
            double value = lua_tonumber(L, -1);
            lua_pop(L, 1);
            return value;
        }else{
            error(L,error_message);
        }

        return 0;
    }

	void table_get_doublep_value(lua_State *L, const char *key, double **value, double *default_value, bool not_null) {
		if (*value != NULL) {
			delete *value;
			*value = NULL;
		}
		lua_getfield(L, -1, key);
		int value_type = lua_type(L, -1);
		if (value_type == LUA_TNUMBER) {
			lua_Number lua_number = lua_tonumber(L, -1);
			*value = new double(lua_number);
		} else if (value_type == LUA_TNIL && default_value != NULL) {
			*value = new double(*default_value);
		}
		lua_pop(L, 1);
		if (*value == NULL && not_null) {
			luaL_error(L, "Table's property %s is not a number.", key);
		}
	}

	void table_get_doublep(lua_State *L, const char *key, double **value) {
		table_get_doublep_value(L, key, value, NULL, false);
	}

	void table_get_doublep(lua_State *L, const char *key, double **value, double default_value) {
		table_get_doublep_value(L, key, value, &default_value, false);
	}

	void table_get_doublep_not_null(lua_State *L, const char *key, double **value) {
		table_get_doublep_value(L, key, value, NULL, true);
	}

	// Boolean.
	bool table_get_boolean(lua_State *L, const char *key, bool default_value) {
		lua_getfield(L, -1, key);
		bool value = default_value;
		if (lua_isboolean(L, -1)) {
			value = lua_toboolean(L, -1);
		}
		lua_pop(L, 1);
		return value;
	}

    // Boolean.
    bool table_get_boolean_safe(lua_State *L, const char *key, const char* error_str) {
        lua_getfield(L, -1, key);
        if (lua_isboolean(L, -1)) {
            bool value = lua_toboolean(L, -1);
            lua_pop(L, 1);
            return value;
        }else{
            error(L, error_str);
        }
    }

	void table_get_booleanp_value(lua_State *L, const char *key, bool **value, bool *default_value, bool not_null) {
		if (*value != NULL) {
			delete *value;
			*value = NULL;
		}
		lua_getfield(L, -1, key);
		int value_type = lua_type(L, -1);
		if (value_type == LUA_TBOOLEAN) {
			bool lua_boolean = lua_toboolean(L, -1);
			*value = new bool(lua_boolean);
		} else if (value_type == LUA_TNIL && default_value != NULL) {
			*value = new bool(*default_value);
		}
		lua_pop(L, 1);
		if (*value == NULL && not_null) {
			luaL_error(L, "Table's property %s is not a boolean.", key);
		}
	}

	void table_get_booleanp(lua_State *L, const char *key, bool **value) {
		table_get_booleanp_value(L, key, value, NULL, false);
	}

	void table_get_booleanp(lua_State *L, const char *key, bool **value, bool default_value) {
		table_get_booleanp_value(L, key, value, &default_value, false);
	}

	void table_get_booleanp_not_null(lua_State *L, const char *key, bool **value) {
		table_get_booleanp_value(L, key, value, NULL, true);
	}

	// Function.
	int table_get_function(lua_State *L, const char *key, int default_value) {
		lua_getfield(L, -1, key);
		int value = default_value;
		if (lua_isfunction(L, -1)) {
			value = luaL_ref(L, LUA_REGISTRYINDEX);
		}
		lua_pop(L, 1);
		return value;
	}

	void table_get_functionp_value(lua_State *L, const char *key, int *value, bool not_null) {
		lua_getfield(L, -1, key);
		if (lua_isfunction(L, -1)) {
			*value = luaL_ref(L, LUA_REGISTRYINDEX);
		} else {
			lua_pop(L, 1);
			if (not_null) {
				luaL_error(L, "Table's property %s is not a function.", key);
			}
		}
	}

	void table_get_functionp(lua_State *L, const char *key, int *value) {
		table_get_functionp_value(L, key, value, false);
	}

	void table_get_functionp_not_null(lua_State *L, const char *key, int *value) {
		table_get_functionp_value(L, key, value, true);
	}

	/*void table_get_functionp_value(lua_State *L, const char *key, int **value, int *default_value, bool not_null) {
		if (*value != NULL) {
			delete *value;
			*value = NULL;
		}
		lua_getfield(L, -1, key);
		int value_type = lua_type(L, -1);
		if (value_type == LUA_TFUNCTION) {
			int lua_ref = luaL_ref(L, LUA_REGISTRYINDEX);
			*value = new int(lua_ref);
		} else {
			lua_pop(L, 1);
			if (value_type == LUA_TNIL && default_value != NULL) {
				*value = new int(*default_value);
			}
		}
		if (*value == NULL && not_null) {
			luaL_error(L, "Table's property %s is not a function.", key);
		}
	}

	void table_get_functionp(lua_State *L, const char *key, int **value) {
		table_get_functionp_value(L, key, value, NULL, false);
	}

	void table_get_functionp(lua_State *L, const char *key, int **value, int default_value) {
		table_get_functionp_value(L, key, value, &default_value, false);
	}

	void table_get_functionp_not_null(lua_State *L, const char *key, int **value) {
		table_get_functionp_value(L, key, value, NULL, true);
	}*/

	// Lightuserdata.
	void *table_get_lightuserdata(lua_State *L, const char *key, void *default_value) {
		lua_getfield(L, -1, key);
		void *value = default_value;
		if (lua_islightuserdata(L, -1)) {
			value = lua_touserdata(L, -1);
		}
		lua_pop(L, 1);
		return value;
	}

	void table_get_lightuserdatap_value(lua_State *L, const char *key, void **value, void *default_value, bool not_null) {
		lua_getfield(L, -1, key);
		int value_type = lua_type(L, -1);
		if (value_type == LUA_TLIGHTUSERDATA) {
			*value = lua_touserdata(L, -1);
		} else if (value_type == LUA_TNIL && default_value != NULL) {
			*value = default_value;
		}
		lua_pop(L, 1);
		if (*value == NULL && not_null) {
			luaL_error(L, "Table's property %s is not a lightuserdata.", key);
		}
	}

	void table_get_lightuserdatap(lua_State *L, const char *key, void **value) {
		table_get_lightuserdatap_value(L, key, value, NULL, false);
	}

	void table_get_lightuserdatap(lua_State *L, const char *key, void **value, void *default_value) {
		table_get_lightuserdatap_value(L, key, value, default_value, false);
	}

	void table_get_lightuserdatap_not_null(lua_State *L, const char *key, void **value) {
		table_get_lightuserdatap_value(L, key, value, NULL, true);
	}

	// Vector3
	Vectormath::Aos::Vector3 *table_get_vector3(lua_State *L, const char *key, Vectormath::Aos::Vector3 *default_value) {
		lua_getfield(L, -1, key);
		Vectormath::Aos::Vector3 *value = default_value;
		if (lua_isuserdata(L, -1)) {
			value = dmScript::ToVector3(L, -1);
		}
		lua_pop(L, 1);
		return value;
	}

	bool table_is_string(lua_State *L, const char *key) {
		bool result = false;
		lua_getfield(L, -1, key);
		result = lua_isstring(L, -1);
		lua_pop(L, 1);
		return result;
	}

	bool table_is_number(lua_State *L, const char *key) {
		bool result = false;
		lua_getfield(L, -1, key);
		result = lua_isnumber(L, -1);
		lua_pop(L, 1);
		return result;
	}

	bool table_is_boolean(lua_State *L, const char *key) {
		bool result = false;
		lua_getfield(L, -1, key);
		result = lua_isboolean(L, -1);
		lua_pop(L, 1);
		return result;
	}

	bool table_is_not_nil(lua_State *L, const char *key){
        bool result = false;
        lua_getfield(L, -1, key);
        result = !lua_isnil(L, -1);
        lua_pop(L, 1);
        return result;
	}

    bool table_is_nil(lua_State *L, const char *key){
        bool result = false;
        lua_getfield(L, -1, key);
        result = lua_isnil(L, -1);
        lua_pop(L, 1);
        return result;
    }

	void table_set_string_field(lua_State *L, const char *key, const char *value) {
		if (value != NULL) {
			lua_pushstring(L, value);
			lua_setfield(L, -2, key);
		}
	}

	void table_set_boolean_field(lua_State *L, const char *key, bool value) {
		lua_pushboolean(L, value);
		lua_setfield(L, -2, key);
	}


	void push_vector(lua_State *L, double x, double y, double z) {
		lua_getglobal(L, "vmath");
		lua_getfield(L, -1, "vector3");
		lua_remove(L, -2); // vmath
		lua_pushnumber(L, x);
		lua_pushnumber(L, y);
		lua_pushnumber(L, z);
		lua_call(L, 3, 1);
	}
	
	void push_vector(lua_State *L, double x, double y) {
		push_vector(L, x, y, 0);
	}

	void unref(lua_State *L, int ref) {
		if (ref != LUA_REFNIL) {
			luaL_unref(L, LUA_REGISTRYINDEX, ref);
		}
	}

	void error(lua_State *L,const char *error){
	    luaL_error(L,"%s",error);
	//	lua_pushstring(L, error);
	//	lua_error(L);

	}

	bool test_userdata(lua_State *L,int idx, const char* tname){
        if(!lua_isuserdata(L,idx)){return false;}
        if(!lua_getmetatable(L, idx)){
            return false;
        }
        luaL_getmetatable(L,tname);

        bool equals = lua_equal(L,-1,-2);
        lua_pop(L,2);
        return equals;
	}
}