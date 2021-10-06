#include "utils.h"
#include "draw.h"
#include <static_hash.h>

#define META_NAME "Box2d::DrawClass"
#define USERDATA_TYPE "draw"

namespace box2dDefoldNE {
Draw::Draw(): BaseUserData(USERDATA_TYPE){
    DrawPolygon_ref = LUA_REFNIL;
    DrawSolidPolygon_ref = LUA_REFNIL;
    DrawCircle_ref = LUA_REFNIL;
    DrawSolidCircle_ref = LUA_REFNIL;
    DrawSegment_ref = LUA_REFNIL;
    DrawTransform_ref = LUA_REFNIL;
    DrawPoint_ref = LUA_REFNIL;
    defold_script_instance = LUA_REFNIL;
    L = NULL;

    this->box2dObj = this;
    this->metatable_name = META_NAME;
}

Draw::~Draw() {

}

Draw* Draw_from_table(lua_State *L){
    if (lua_istable(L, -1)) {
        Draw* draw = new Draw();
        dmScript::GetInstance(L);
        draw->defold_script_instance = dmScript::Ref(L, LUA_REGISTRYINDEX);
        //lua_pop(L, 1);

        lua_pushnil(L);  /* first key */
        while (lua_next(L, -2) != 0) {
            const char* key = lua_tostring(L, -2);
           // printf("key %s %s\n", key, lua_tostring(L, -1));
            switch (hash_string(key)) {
                case HASH_flags:
                    draw->SetFlags(luaL_checknumber(L,-1));
                    break;
                case HASH_DrawPolygon:
                    if (lua_isfunction(L, -1)) {lua_pushvalue(L, -1);draw->DrawPolygon_ref = luaL_ref(L,LUA_REGISTRYINDEX);
                    }else {utils::error(L,"DrawPolygon should be function");}
                    break;
                case HASH_DrawSolidPolygon:
                    if (lua_isfunction(L, -1)) {lua_pushvalue(L, -1);draw->DrawSolidPolygon_ref = luaL_ref(L,LUA_REGISTRYINDEX);
                    }else {utils::error(L,"DrawSolidPolygon should be function");}
                    break;
                case HASH_DrawCircle:
                    if (lua_isfunction(L, -1)) {lua_pushvalue(L, -1);draw->DrawCircle_ref = luaL_ref(L,LUA_REGISTRYINDEX);
                    }else {utils::error(L,"DrawCircle should be function");}
                    break;
                case HASH_DrawSolidCircle:
                    if (lua_isfunction(L, -1)) {lua_pushvalue(L, -1);draw->DrawSolidCircle_ref = luaL_ref(L,LUA_REGISTRYINDEX);
                    }else {utils::error(L,"DrawSolidCircle should be function");}
                    break;
                case HASH_DrawSegment:
                    if (lua_isfunction(L, -1)) {lua_pushvalue(L, -1);draw->DrawSegment_ref = luaL_ref(L,LUA_REGISTRYINDEX);
                    }else {utils::error(L,"DrawSegment should be function");}
                    break;
                case HASH_DrawTransform:
                    if (lua_isfunction(L, -1)) {lua_pushvalue(L, -1);draw->DrawTransform_ref = luaL_ref(L,LUA_REGISTRYINDEX);
                    }else {utils::error(L,"DrawTransform should be function");}
                    break;
                case HASH_DrawPoint:
                    if (lua_isfunction(L, -1)) {lua_pushvalue(L, -1);draw->DrawPoint_ref = luaL_ref(L,LUA_REGISTRYINDEX);
                    }else {utils::error(L,"DrawPoint should be function");}
                    break;
                default:
                    draw->Destroy(L);
                    luaL_error(L, "unknown key:%s", key);
                    break;
            }
            /* removes 'value'; keeps 'key' for next iteration */
            lua_pop(L, 1);
        }
        return draw;
    }else{
        utils::error(L,"Need table to create DebugDraw");
    }
}


Draw* Draw_get_userdata_safe(lua_State *L, int index) {
    Draw *lua_draw = (Draw*) BaseUserData_get_userdata(L, index, USERDATA_TYPE);
    return lua_draw;
}

static int SetFlags(lua_State *L){//void SetFlags(uint32 flags);
    utils::check_arg_count(L, 2);
    Draw *draw = Draw_get_userdata_safe(L, 1);
    draw->SetFlags(luaL_checknumber(L,2));
    return 0;
}

static int AppendFlags(lua_State *L){//void AppendFlags(uint32 flags);
    utils::check_arg_count(L, 2);
    Draw *draw = Draw_get_userdata_safe(L, 1);
    draw->AppendFlags(luaL_checknumber(L,2));
    return 0;
}

static int ClearFlags(lua_State *L){//ClearFlags(uint32 flags);
    utils::check_arg_count(L, 2);
    Draw *draw = Draw_get_userdata_safe(L, 1);
    draw->ClearFlags(luaL_checknumber(L,2));
    return 0;
}

static int GetFlags(lua_State *L){//uint32 GetFlags()
    utils::check_arg_count(L, 1);
    Draw *draw = Draw_get_userdata_safe(L, 1);
    lua_pushnumber(L, draw->GetFlags());
    return 1;
}

static int Destroy(lua_State *L){
    utils::check_arg_count(L, 1);
    Draw *draw = Draw_get_userdata_safe(L, 1);
    draw->Destroy(L);
    return 0;
}

static int ToString(lua_State *L){
    utils::check_arg_count(L, 1);
    Draw *draw = Draw_get_userdata_safe(L, 1);
    lua_pushfstring( L, "b2Draw[%p]",(void *) draw);
	return 1;
}


void DrawInitMetaTable(lua_State *L){
    int top = lua_gettop(L);

    luaL_Reg functions[] = {
        {"SetFlags",SetFlags},
        {"GetFlags",GetFlags},
        {"ClearFlags",ClearFlags},
        {"GetFlags",GetFlags},
        {"Destroy",Destroy},
        {"__tostring",ToString},
        { 0, 0 }
    };
    luaL_newmetatable(L, META_NAME);
    luaL_register (L, NULL,functions);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_pop(L, 1);


    assert(top == lua_gettop(L));
}


static void push_polygon(lua_State *L,const b2Vec2* vertices, int32 vertexCount, const b2Color& color){
   lua_newtable(L);
   for(int j=0;j<vertexCount;j++){
       b2Vec2 vec = vertices[j];
       lua_newtable(L);
           lua_pushstring(L, "x");
           lua_pushnumber(L,vec.x);
           lua_settable(L,-3);
           lua_pushstring(L, "y");
           lua_pushnumber(L,vec.y);
           lua_settable(L,-3);
       lua_rawseti(L, -2, j+1);
   }

   lua_newtable(L);
        lua_pushstring(L, "r");
        lua_pushnumber(L,color.r);
        lua_settable(L,-3);
        lua_pushstring(L, "g");
        lua_pushnumber(L,color.g);
        lua_settable(L,-3);
        lua_pushstring(L, "b");
        lua_pushnumber(L,color.b);
        lua_settable(L,-3);
        lua_pushstring(L, "a");
        lua_pushnumber(L,color.a);
        lua_settable(L,-3);
}

static void push_circle(lua_State *L,const b2Vec2& center, float radius, const b2Color& color){
    lua_newtable(L);
        lua_pushstring(L, "x");
        lua_pushnumber(L,center.x);
        lua_settable(L,-3);
        lua_pushstring(L, "y");
        lua_pushnumber(L,center.y);
        lua_settable(L,-3);

    lua_pushnumber(L,radius);

    lua_newtable(L);
        lua_pushstring(L, "r");
        lua_pushnumber(L,color.r);
        lua_settable(L,-3);
        lua_pushstring(L, "g");
        lua_pushnumber(L,color.g);
        lua_settable(L,-3);
        lua_pushstring(L, "b");
        lua_pushnumber(L,color.b);
        lua_settable(L,-3);
        lua_pushstring(L, "a");
        lua_pushnumber(L,color.a);
        lua_settable(L,-3);
}

static void push_solid_circle(lua_State *L,const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color){
    lua_newtable(L);
        lua_pushstring(L, "x");
        lua_pushnumber(L,center.x);
        lua_settable(L,-3);
        lua_pushstring(L, "y");
        lua_pushnumber(L,center.y);
        lua_settable(L,-3);

    lua_pushnumber(L,radius);


    lua_newtable(L);
        lua_pushstring(L, "x");
        lua_pushnumber(L,axis.x);
        lua_settable(L,-3);
        lua_pushstring(L, "y");
        lua_pushnumber(L,axis.y);
        lua_settable(L,-3);

    lua_newtable(L);
        lua_pushstring(L, "r");
        lua_pushnumber(L,color.r);
        lua_settable(L,-3);
        lua_pushstring(L, "g");
        lua_pushnumber(L,color.g);
        lua_settable(L,-3);
        lua_pushstring(L, "b");
        lua_pushnumber(L,color.b);
        lua_settable(L,-3);
        lua_pushstring(L, "a");
        lua_pushnumber(L,color.a);
        lua_settable(L,-3);


}

static void push_segment(lua_State *L,const b2Vec2& p1, const b2Vec2& p2, const b2Color& color){
    lua_newtable(L);
        lua_pushstring(L, "x");
        lua_pushnumber(L,p1.x);
        lua_settable(L,-3);
        lua_pushstring(L, "y");
        lua_pushnumber(L,p1.y);
        lua_settable(L,-3);

    lua_newtable(L);
        lua_pushstring(L, "x");
        lua_pushnumber(L,p2.x);
        lua_settable(L,-3);
        lua_pushstring(L, "y");
        lua_pushnumber(L,p2.y);
        lua_settable(L,-3);


    lua_newtable(L);
        lua_pushstring(L, "r");
        lua_pushnumber(L,color.r);
        lua_settable(L,-3);
        lua_pushstring(L, "g");
        lua_pushnumber(L,color.g);
        lua_settable(L,-3);
        lua_pushstring(L, "b");
        lua_pushnumber(L,color.b);
        lua_settable(L,-3);
        lua_pushstring(L, "a");
        lua_pushnumber(L,color.a);
        lua_settable(L,-3);

}

void Draw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    if(DrawPolygon_ref!= LUA_REFNIL){
        lua_rawgeti(L,LUA_REGISTRYINDEX,DrawPolygon_ref);
        push_polygon(L,vertices,vertexCount,color);
        if (lua_pcall(L, 2, 0, 0) != 0){
             dmLogError("error running DrawPolygon: %s",lua_tostring(L, -1));
        }
    }
}
void Draw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    if(DrawSolidPolygon_ref!= LUA_REFNIL){
        lua_rawgeti(L,LUA_REGISTRYINDEX,DrawSolidPolygon_ref);
        push_polygon(L,vertices,vertexCount,color);
        if (lua_pcall(L, 2, 0, 0) != 0){
             dmLogError("error running DrawSolidPolygon: %s",lua_tostring(L, -1));
        }
    }
}
void Draw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color) {
    if(DrawCircle_ref!= LUA_REFNIL){
        lua_rawgeti(L,LUA_REGISTRYINDEX,DrawCircle_ref);
        push_circle(L,center,radius,color);
        if (lua_pcall(L, 3, 0, 0) != 0){
             dmLogError("error running DrawCircle: %s",lua_tostring(L, -1));
        }
    }
}
void Draw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) {
    if(DrawSolidCircle_ref!= LUA_REFNIL){
        lua_rawgeti(L,LUA_REGISTRYINDEX,DrawSolidCircle_ref);
        push_solid_circle(L,center,radius,axis,color);
        if (lua_pcall(L, 4, 0, 0) != 0){
             dmLogError("error running DrawSolidCircle: %s",lua_tostring(L, -1));
        }
    }
}
void Draw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
    if(DrawSegment_ref!= LUA_REFNIL){
        lua_rawgeti(L,LUA_REGISTRYINDEX,DrawSegment_ref);
        push_segment(L,p1,p2,color);
        if (lua_pcall(L, 3, 0, 0) != 0){
             dmLogError("error running DrawSegment: %s",lua_tostring(L, -1));
        }
    }
}
void Draw::DrawTransform(const b2Transform& xf) {
     if(DrawTransform_ref!= LUA_REFNIL){
        lua_rawgeti(L,LUA_REGISTRYINDEX,DrawTransform_ref);
        extra_utils::b2Transform_push(L, xf);
        if (lua_pcall(L, 1, 0, 0) != 0){
            dmLogError("error running DrawTransform: %s",lua_tostring(L, -1));
        }
    }
}
void Draw::DrawPoint(const b2Vec2& p, float size, const b2Color& color){}


void Draw::Destroy(lua_State *L) {
    utils::unref(L, DrawPolygon_ref);
    utils::unref(L, DrawSolidPolygon_ref);
    utils::unref(L, DrawCircle_ref);
    utils::unref(L, DrawSolidCircle_ref);
    utils::unref(L, DrawSegment_ref);
    utils::unref(L, DrawTransform_ref);
    utils::unref(L, DrawPoint_ref);
    utils::unref(L, defold_script_instance);

    DrawPolygon_ref = LUA_REFNIL;
    DrawSolidPolygon_ref = LUA_REFNIL;
    DrawCircle_ref = LUA_REFNIL;
    DrawSolidCircle_ref = LUA_REFNIL;
    DrawSegment_ref = LUA_REFNIL;
    DrawTransform_ref = LUA_REFNIL;
    DrawPoint_ref = LUA_REFNIL;
    defold_script_instance = LUA_REFNIL;

    BaseUserData::Destroy(L);

    delete this;
}
}
