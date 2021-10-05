#ifndef contact_h
#define contact_h

#include <box2d/box2d.h>
#include <dmsdk/sdk.h>
#include <extra_utils.h>
#include "base_userdata.h"

namespace box2dDefoldNE {

class Contact : public BaseUserData {
private:

public:
    bool reuse; //reuse Contact class in callbacks.
    b2Contact *contact;
    Contact(b2Contact *c);
    ~Contact();
    void Reuse(b2Contact *c); //reuse Contact class in callbacks.
    virtual void Destroy(lua_State *L);
    void DestroyTable(lua_State *L);
};

void ContactInitMetaTable(lua_State *L);
Contact* Contact_get_userdata_safe(lua_State *L, int index);

}
#endif