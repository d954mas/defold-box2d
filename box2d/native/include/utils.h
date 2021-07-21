#ifndef utils_h
#define utils_h

#include <utility>

#if defined(__linux__) || defined(__APPLE__)
	#include <sys/time.h>
#endif

#include <dmsdk/sdk.h>
#include <dmsdk/dlib/log.h>

#define ERROR_MESSAGE(format, ...) snprintf(error_message, 2048, format, ##__VA_ARGS__)

namespace utils {
	const int ERROR_MESSAGE_MAX = 2048;
	struct Event {
		const char *name;
		const char *phase;
		bool is_error;
		const char *error_message;
	};
	struct ScriptListener {
		int lua_listener;
		int lua_script_instance;
	};
	uint64_t get_time();
	void enable_debug();
	void check_arg_count(lua_State *L, int count_exact);
	void check_arg_count(lua_State *L, int count_from, int count_to);
	void get_table(lua_State *L, int index);

	const char *table_get_string(lua_State *L, const char *key, const char *default_value);
	void table_get_stringp(lua_State *L, const char *key, char **value);
	void table_get_stringp(lua_State *L, const char *key, char **value, const char *default_value);
	void table_get_stringp_not_null(lua_State *L, const char *key, char **value);

	int table_get_integer(lua_State *L, const char *key, int default_value);
	int table_get_integer_safe(lua_State *L, const char *key, const char *error_message);
	void table_get_integerp(lua_State *L, const char *key, int **value);
	void table_get_integerp(lua_State *L, const char *key, int **value, int default_value);
	void table_get_integerp_not_null(lua_State *L, const char *key, int **value);

	double table_get_double(lua_State *L, const char *key, double default_value);
	double table_get_double_safe(lua_State *L, const char *key, const char *error_message);
	void table_get_doublep(lua_State *L, const char *key, double **value);
	void table_get_doublep(lua_State *L, const char *key, double **value, double default_value);
	void table_get_doublep_not_null(lua_State *L, const char *key, double **value);

	bool table_get_boolean(lua_State *L, const char *key, bool default_value);
	bool table_get_boolean_safe(lua_State *L, const char *key, const char *error_message);
	void table_get_booleanp(lua_State *L, const char *key, bool **value);
	void table_get_booleanp(lua_State *L, const char *key, bool **value, bool default_value);
	void table_get_booleanp_not_null(lua_State *L, const char *key, bool **value);

	void table_get_function(lua_State *L, const char *key, int *value);

	int table_get_function(lua_State *L, const char *key, int default_value);
	void table_get_functionp(lua_State *L, const char *key, int *value);
	void table_get_functionp(lua_State *L, const char *key, int *value, int default_value);
	void table_get_functionp_not_null(lua_State *L, const char *key, int *value);

	void *table_get_lightuserdata(lua_State *L, const char *key, void *default_value);
	void table_get_lightuserdatap(lua_State *L, const char *key, void **value);
	void table_get_lightuserdatap(lua_State *L, const char *key, void **value, void *default_value);
	void table_get_lightuserdatap_not_null(lua_State *L, const char *key, void **value);

	Vectormath::Aos::Vector3 *table_get_vector3(lua_State *L, const char *key, Vectormath::Aos::Vector3 *default_value);

	bool table_is_string(lua_State *L, const char *key);
	bool table_is_number(lua_State *L, const char *key);
	bool table_is_boolean(lua_State *L, const char *key);

	bool table_is_not_nil(lua_State *L, const char *key);
	bool table_is_nil(lua_State *L, const char *key);


	void push_vector(lua_State *L, double x, double y, double z);
	void push_vector(lua_State *L, double x, double y);

	void unref(lua_State *L, int ref);

	void error(lua_State *L,const char *error);

	bool test_userdata(lua_State *L,int idx, const char* meta);
}

#endif