#ifndef contact_h
#define contact_h

#include <box2d/box2d.h>
#include <dmsdk/sdk.h>
#include <extra_utils.h>




class Contact {
private:

public:
    bool reuse; //reuse Contact class in callbacks.
    int table_ref; //always return same table
    b2Contact *contact;
    Contact(b2Contact *c);
    ~Contact();
    void Reuse(b2Contact *c); //reuse Contact class in callbacks.
	void Push(lua_State *L);
    void Destroy(lua_State *L);
    void DestroyTable(lua_State *L);
};

void ContactInitMetaTable(lua_State *L);
Contact* Contact_get_userdata(lua_State *L, int index);
Contact* Contact_get_userdata_safe(lua_State *L, int index);
#endif