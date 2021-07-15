# Box2dWorldManifold
This is used to compute the current state of a contact manifold.

_FIELDS_
* `normal` (vector3) - World vector pointing from A to B.
* `points` <kbd>vector3[]</kbd> - World contact point (point of intersection).
* `separations` <kbd>number[]</kbd> - A negative value indicates overlap, in meters.
