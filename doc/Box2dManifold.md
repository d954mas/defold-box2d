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
* __type__ <kbd>number</kbd> - box2d.b2Manifold_Type
* __localPoint__ <kbd>vector3</kbd> - Usage depends on manifold type.
* __localNormal__ <kbd>vector3</kbd> - Not use for Type::e_points.
* __pointCount__ <kbd>number</kbd> - The number of manifold points.
* __points__ <kbd>Box2dManifoldPoint[]</kbd> - The points of contact.

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
* __localPoint__ <kbd>vector3</kbd> - Usage depends on manifold type.
* __normalImpulse__ <kbd>number</kbd> - The non-penetration impulse.
* __tangentImpulse__ <kbd>number</kbd> - The friction impulse.
* __id__ <kbd>Box2dContactID</kbd> - Uniquely identifies a contact point between two shapes.

## Box2dContactID
Contact ids to facilitate warm starting.

_FIELDS_
* __cf__ <kbd>Box2dContactFeature</kbd>
* __key__ <kbd>number</kbd> - Used to quickly compare contact ids.

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
* __indexA__ <kbd>number</kbd> - Feature index on shapeA.
* __indexB__ <kbd>number</kbd> - Feature index on shapeB.
* __typeA__ <kbd>number</kbd> - The feature type on shapeA.
* __typeB__ <kbd>number</kbd> - The feature type on shapeB.
