# Shape
There is no direct binding for `b2Shape`. Use a table with data instead when you need a shape, for example when you create a fixture.

## Constructor

```lua
local Box2dShape = {
	-- See the `box2d.b2Shape` enum: { e_circle=0, e_edge=1, e_polygon=2, e_chain=3 }
	shape = 0,

	--circle
	circle_radius = 1,
	circle_position = vmath.vector3(0), --or nil

	--edge
	edge_two_sided = false,
	edge_v0 = vmath.vector3(0),
	edge_v1 = vmath.vector3(0),
	edge_v2 = vmath.vector3(0),
	edge_v3 = vmath.vector3(0),

	--box (polygon)
	box = true,
	box_hx = 1, box_hy = 1,
	box_center = vmath.vector3(0), --or nil
	box_angle = 0, -- or nil. need box_center when use angle

	--polygon vertices
	polygon_vertices = { vmath.vector3(0, 0, 0), vmath.vector3(1, 0, 0), vmath.vector3(0, 1, 0) },

	--chain
	chain_loop = false, --true use CreateLoop false use CreateChain
	chain_vertices = { vmath.vector3(1.7, 0, 0), vmath.vector3(1, 0, 0), vmath.vector3(0, 0, 0), vmath.vector3(-1.7, 0.4, 0) },
	chain_prev_vertex = vmath.vector3(0, 0, 0),
	chain_next_vertex = vmath.vector3(0, 0, 0)
}
```
