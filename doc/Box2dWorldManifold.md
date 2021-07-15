# Box2dWorldManifold
This is used to compute the current state of a contact manifold.

_FIELDS_
* `normal` (vector3) - World vector pointing from A to B.
* `points` (vector3[]) - World contact point (point of intersection).
* `separations` (number[]) - A negative value indicates overlap, in meters.
