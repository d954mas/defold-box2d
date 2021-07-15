# Box2dMassData
This holds the mass data computed for a shape. Returned by Box2dBody:GetMassData().

_FIELDS_
* `mass` (number) - The mass of the shape, usually in kilograms.
* `center` (vector3) - The position of the shape's centroid relative to the shape's origin.
* `I` (number) -  The rotational inertia of the shape about the local origin.
