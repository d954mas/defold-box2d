
### Box2dMassData <kbd>table</kbd>
This holds the mass data computed for a shape. Returned by Box2dBody:GetMassData().

_FIELDS_
* __mass__ <kbd>number</kbd> - The mass of the shape, usually in kilograms.
* __center__ <kbd>vector3</kbd> - The position of the shape's centroid relative to the shape's origin.
* __I__ <kbd>number</kbd> -  The rotational inertia of the shape about the local origin.
