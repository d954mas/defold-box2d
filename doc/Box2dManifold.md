# Box2dManifold
A manifold for two touching convex shapes.

Box2D supports multiple types of contact:
- clip point versus plane with radius
- point versus point with radius (circles)

The local point usage depends on the manifold type:
- e_circles: the local center of circleA
- e_faceA: the center of faceA
- e_faceB: the center of faceB

Similarly the local normal usage:
- e_circles: not used
- e_faceA: the normal on polygonA
- e_faceB: the normal on polygonB

We store contacts in this way so that position correction can
account for movement, which is critical for continuous physics.
All contact scenarios must be expressed in one of these types.
This structure is stored across time steps, so we keep it small.

_FIELDS_
* `type` (number) - box2d.b2Manifold_Type
* `localPoint` (vector3) - Usage depends on manifold type.
* `localNormal` (vector3) - Not use for Type::e_points.
* `pointCount` (number) - The number of manifold points.
* `points` <kbd>Box2dManifoldPoint[]</kbd> - The points of contact.

## Box2dManifoldPoint
A manifold point is a contact point belonging to a contact
manifold. It holds details related to the geometry and dynamics
of the contact points.

The local point usage depends on the manifold type:
- e_circles: the local center of circleB
- e_faceA: the local center of cirlceB or the clip point of polygonB
- e_faceB: the clip point of polygonA

This structure is stored across time steps, so we keep it small.
Note: the impulses are used for internal caching and may not
provide reliable contact forces, especially for high speed collisions.

_FIELDS_
* `localPoint` (vector3) - Usage depends on manifold type.
* `normalImpulse` (number) - The non-penetration impulse.
* `tangentImpulse` (number) - The friction impulse.
* `id` (Box2dContactID) - Uniquely identifies a contact point between two shapes.

## Box2dContactID
Contact ids to facilitate warm starting.

_FIELDS_
* `cf` (Box2dContactFeature)
* `key` (number) - Used to quickly compare contact ids.

The features that intersect to form the contact point
This must be 4 bytes or less.
```lua
enum Type
	{
		e_vertex = 0,
		e_face = 1
	}
```

## Box2dContactFeature

_FIELDS_
* `indexA` (number) - Feature index on shapeA.
* `indexB` (number) - Feature index on shapeB.
* `typeA` (number) - The feature type on shapeA.
* `typeB` (number) - The feature type on shapeB.
