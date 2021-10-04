#ifndef base_userdata_h
#define base_userdata_h

#include <dmsdk/sdk.h>
#include <extra_utils.h>

#define USERDATA_NAME "__userdata_box2d"
#define USERDATA_TYPE "__userdata_type_box2d"

namespace box2dDefoldNE {

class BaseUserData {
private:

public:
    int user_data_ref;
    int table_ref; //always return same table
    const char* userdata_type;;
    const char* metatable_name;
    void* box2dObj;

    BaseUserData(const char* userdata_type, void* box2dObj);
    ~BaseUserData();
	void Push(lua_State *L);
	void Destroy(lua_State *L);
};

BaseUserData* BaseUserData_userdata(lua_State *L, int index, char* userdata_type);



}
#endif