# FixtureDef
There is no binding for b2FixtureDef, just use a table.

## Constructor
A fixture definition is used to create a fixture.
You can reuse fixture definitions safely.

```lua
local Box2dFixtureDef = {
    -- The shape, this must be set.
    @type Box2dShape
    shape = { shape = box2d.b2Shape.e_circle, circle_radius = 1, circle_position = vmath.vector3(0) },

    -- Use this to store application specific fixture data.
    userData = nil;

    -- The friction coefficient, usually in the range [0,1].
    friction = 0.2;

    -- The restitution (elasticity) usually in the range [0,1].
    restitution = 0;

    -- Restitution velocity threshold, usually in m/s. Collisions above this
    -- speed have restitution applied (will bounce).
    restitutionThreshold = 1;

    --The density, usually in kg/m^2.
    density = 0;

    -- A sensor shape collects contact information but never generates a collision
    -- response.
    isSensor = false;

    -- Contact filtering data. b2Filter
    -- filter = nil;
}
```
