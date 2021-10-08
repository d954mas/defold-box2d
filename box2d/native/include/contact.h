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
    b2Contact *contact;
    Contact(b2Contact *c);
    ~Contact();
    virtual void Destroy(lua_State *L);
};

void ContactInitMetaTable(lua_State *L);
Contact* Contact_get_userdata_safe(lua_State *L, int index);

Contact* Contact_from_b2Contact(b2Contact* contact);

}
#endif