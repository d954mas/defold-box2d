#ifndef draw_h
#define draw_h

#include <box2d/box2d.h>
#include <box2d/b2_draw.h>
#include <dmsdk/sdk.h>
#include <extra_utils.h>
#include "base_userdata.h"

namespace box2dDefoldNE {

class Draw: public BaseUserData , public b2Draw{
private:

public:
    int DrawPolygon_ref;
    int DrawSolidPolygon_ref;
    int DrawCircle_ref;
    int DrawSolidCircle_ref;
    int DrawSegment_ref;
    int DrawTransform_ref;
    int DrawPoint_ref;
    int defold_script_instance;
    lua_State *L;

    Draw();
    ~Draw();

	virtual void Destroy(lua_State *L);

    void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
    void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
    void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) override;
    void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) override;
    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
    void DrawTransform(const b2Transform& xf) override;
    void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override;
};

void DrawInitMetaTable(lua_State *L);
Draw* Draw_from_table(lua_State *L);
Draw* Draw_get_userdata_safe(lua_State *L, int index);

}
#endif




