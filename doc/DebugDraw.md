# DebugDraw
Register this class with a b2World to provide debug drawing of physics
entities in your game.
Destroy it when not it's needed anymore.

## Constructor
> NOTE: See the /box2d/utils module for premade functions using the "draw_line" message.
### box2d.NewDebugDraw(data)

**PARAMETERS**
* `data` (table) -

**RETURN**
* [(Box2dDebugDraw)](DebugDraw.md)

```lua
box2d.NewDebugDraw({
	DrawPolygon = function(vertices,color) __draw_polygon(physics_scale,vertices,color) end,
	DrawSolidPolygon = function(vertices,color) __draw_polygon(physics_scale,vertices,color) end,
	DrawCircle = function(center,radius,color) __draw_circle(physics_scale,center,radius,nil,color) end,
	DrawSolidCircle = function(center,radius,axis,color) __draw_circle(physics_scale,center,radius,axis,color) end,
	DrawSegment = function(p1,p2,color) __draw_segment(physics_scale,p1,p2,color) end,
})
```

## Methods

* Box2dDebugDraw:[SetFlags](#box2ddebugdrawsetflagsflags) (flags)
* Box2dDebugDraw:[GetFlags](#box2ddebugdrawgetflags) ()
* Box2dDebugDraw:[AppendFlags](#box2ddebugdrawappendflagsflags) (flags)
* Box2dDebugDraw:[ClearFlags](#box2ddebugdrawclearflagsflags) (flags)
* Box2dDebugDraw:[Destroy](#box2ddebugdrawdestroy) ()

---
### Box2dDebugDraw:SetFlags(flags)
Set the drawing flags.

**PARAMETERS**
* `flags` (number) -

---
### Box2dDebugDraw:GetFlags()
Get the drawing flags.

**RETURN**
* (number)

---
### Box2dDebugDraw:AppendFlags(flags)
Append flags to the current flags.

**PARAMETERS**
* `flags` (number) -

---
### Box2dDebugDraw:ClearFlags(flags)
Clear flags from the current flags.

**PARAMETERS**
* `flags` (number) -

---
### Box2dDebugDraw:Destroy()
Destroy, free memory.
