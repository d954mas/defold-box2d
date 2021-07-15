# BodyDef
A body definition holds all the data needed to construct a rigid body.
You can safely re-use body definitions. Shapes are added to a body after construction.

## Constructor

```lua
local Box2dBodyDef = {
    -- The body type: static, kinematic, or dynamic.
    -- box2d.b2BodyType
    -- Note: if a dynamic body would have zero mass, the mass is set to one.
    type = box2d.b2BodyType.b2_staticBody,

    -- The world position of the body. Avoid creating bodies at the origin
    -- since this can lead to many overlapping shapes.
    position = vmath.vector3(0),

    -- The world angle of the body in radians.
    angle = 0,

    -- The linear velocity of the body's origin in world co-ordinates.
    linearVelocity = vmath.vector3(0),

    -- The angular velocity of the body.
    angularVelocity = 0,

    -- Linear damping is use to reduce the linear velocity. The damping parameter
    -- can be larger than 1.0f but the damping effect becomes sensitive to the
    -- time step when the damping parameter is large.
    -- Units are 1/time
    linearDamping = 0,

    -- Angular damping is use to reduce the angular velocity. The damping parameter
    -- can be larger than 1.0f but the damping effect becomes sensitive to the
    -- time step when the damping parameter is large.
    -- Units are 1/time
    angularDamping = 0,

    -- Set this flag to false if this body should never fall asleep. Note that
    -- this increases CPU usage.
    allowSleep = true,

    -- Is this body initially awake or sleeping?
    awake = true,

    -- Should this body be prevented from rotating? Useful for characters.
    fixedRotation = false,

    -- Is this a fast moving body that should be prevented from tunneling through
    -- other moving bodies? Note that all bodies are prevented from tunneling through
    -- kinematic and static bodies. This setting is only considered on dynamic bodies.
    -- @_Warning:_ You should use this flag sparingly since it increases processing time.
    bullet = false,

    -- Does this body start out enabled?
    enabled = true,

    -- Use this to store application specific body data.
    userData = nil,

    -- Scale the gravity applied to this body.
    gravityScale = 1
}
```
