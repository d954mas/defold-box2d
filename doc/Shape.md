# Shape
[box2d doc](https://box2d.org/documentation/md__d_1__git_hub_box2d_docs_collision.html)

There are 2 ways to work with shapes.
1) Table. You use lua table with shape description.
2) Userdata. Lua binding for every b2Shape.

## Table
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

## Userdata
Shape
```lua
---@class Box2dShape
local Box2dShape = {}

--- Clone the concrete shape using the provided allocator
---@return Box2dShape
function Box2dShape:Clone() end

--- Get the type of this shape. You can use this to down cast to the concrete shape.
---@return number box2d.b2Shape
function Box2dShape:GetType() end

--- Get the number of child primitives.
---@return number
function Box2dShape:GetChildCount() end

--- Test a point for containment in this shape. This only works for convex shapes.
---@param xf Box2dTransform
---@param p vector3
---@return boolean
function Box2dShape:TestPoint(xf, p) end

--- Cast a ray against a child shape.
--- @param input Box2dRayCastInput the ray-cast input parameters.
--- @param transform Box2dTransform transform to be applied to the shape.
--- @param childIndex number|nil the child shape index
---@return Box2dRayCastOutput|nil
function Box2dShape:RayCast(input, transform, childIndex) end

--- Given a transform, compute the associated axis aligned bounding box for a child shape.
--- @param xf Box2dTransform the world transform of the shape.
--- @param childIndex number|nil the child shape index
---@return Box2dAABB
function Box2dShape:ComputeAABB(xf, childIndex) end

--- Compute the mass properties of this shape using its dimensions and density.
--- The inertia tensor is computed about the local origin.
--- @param density number the density in kilograms per meter squared.
---@return Box2dMassData the mass data for this shape.
function Box2dShape:ComputeMass(density) end

--- Radius of a shape. For polygonal shapes this must be b2_polygonRadius. There is no support for
--- making rounded polygons.
---@return number
function Box2dShape:GetRadius() end

---@param radius number
function Box2dShape:SetRadius(radius) end
```
CircleShape
```lua
---@class Box2dCircleShape:Box2dShape
local Box2dCircleShape = {}

--- Clone the concrete shape using the provided allocator
---@return Box2dCircleShape
function Box2dCircleShape:Clone() end

---@param position vector3
function Box2dCircleShape:SetPosition(position) end

---@return vector3
function Box2dCircleShape:GetPosition() end

```

PolygonShape
```lua
---@class Box2dPolygonShape:Box2dShape
local Box2dPolygonShape = {}

--- Clone the concrete shape using the provided allocator
---@return Box2dPolygonShape
function Box2dPolygonShape:Clone() end

--- Create a convex hull from the given array of local points.
--- The count must be in the range [3, b2_maxPolygonVertices].
--- @warning the points may be re-ordered, even if they form a convex polygon
--- @warning collinear points are handled but not removed. Collinear points
--- may lead to poor stacking behavior.
---@param points vector3[]
function Box2dPolygonShape:Set(points) end

--- Build vertices to represent an axis-aligned box centered on the local origin.
---@param hx number the half-width.
---@param hy number the half-height.
function Box2dPolygonShape:SetAsBox(hx, hy) end

--- Build vertices to represent an oriented box.
---@param hx number the half-width.
---@param hy number the half-height.
---@param center vector3 the center of the box in local coordinates.
---@param angle float the rotation of the box in local coordinates.
function Box2dPolygonShape:SetAsBox(hx, hy, center, angle) end

--- Validate convexity. This is a very time consuming operation.
---@return boolean true if valid
function Box2dPolygonShape:Validate() end

---@return vector3
function Box2dPolygonShape:GetCentroid() end

---@return vector3[]
function Box2dPolygonShape:GetVertices() end

---@return vector3[]
function Box2dPolygonShape:GetNormals() end

---@return number
function Box2dPolygonShape:GetCount() end
```

EdgeShape
```lua
---@class Box2dEdgeShape:Box2dShape
local Box2dEdgeShape = {}

--- Clone the concrete shape using the provided allocator
---@return Box2dEdgeShape
function Box2dEdgeShape:Clone() end

--- Set this as a part of a sequence. Vertex v0 precedes the edge and vertex v3
--- follows. These extra vertices are used to provide smooth movement
--- across junctions. This also makes the collision one-sided. The edge
--- normal points to the right looking from v1 to v2.
---@param v0 vector3
---@param v1 vector3
---@param v2 vector3
---@param v3 vector3
function Box2dEdgeShape:SetOneSided(v0, v1, v2, v3) end

--- Set this as an isolated edge. Collision is two-sided.
---@param v1 vector3
---@param v2 vector3
function Box2dEdgeShape:SetTwoSided(v1, v2) end

---@return vector3
function Box2dEdgeShape:GetVertex0() end

---@return vector3
function Box2dEdgeShape:GetVertex1() end

---@return vector3
function Box2dEdgeShape:GetVertex2() end

---@return vector3
function Box2dEdgeShape:GetVertex3() end

---@return boolean
function Box2dEdgeShape:IsOneSided() end
```

ChainShape
```lua
---@class Box2dChainShape:Box2dShape
local Box2dChainShape = {}

--- Clone the concrete shape using the provided allocator
---@return Box2dChainShape
function Box2dChainShape:Clone() end

--- Clear all data.
function Box2dChainShape:Clear() end

--- Create a loop. This automatically adjusts connectivity.
---@param vertices vector3[] an array of vertices, these are copied
function Box2dChainShape:CreateLoop(vertices) end

--- Create a chain with ghost vertices to connect multiple chains together.
---@param vertices vector3[] an array of vertices, these are copied
---@param prevVertex vector3 previous vertex from chain that connects to the start
---@param nextVertex vector3 next vertex from chain that connects to the end
function Box2dChainShape:CreateChain(vertices, prevVertex, nextVertex) end

---Get a child edge.
---@param index number
---@return Box2dEdgeShape edge
function Box2dChainShape:GetChildEdge(index) end

---@return vector3[]
function Box2dChainShape:GetVertices() end

---@return vector3
function Box2dChainShape:GetNextVertex() end

---@return vector3
function Box2dChainShape:GetPrevVertex() end

---@return vector3 vertices count
function Box2dChainShape:GetCount() end
```