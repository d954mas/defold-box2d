# Box2dWorldManifold
This is used to compute the current state of a contact manifold.

_FIELDS_
* __normal__ <kbd>vector3</kbd> - World vector pointing from A to B.
* __points__ <kbd>vector3[]</kbd> - World contact point (point of intersection).
* __separations__ <kbd>number[]</kbd> - A negative value indicates overlap, in meters.
