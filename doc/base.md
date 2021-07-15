# Box2D
The extension creates a global module, `box2d`.

## Constants:
```lua
box2d.b2Shape = {
    e_circle = 0,
    e_edge = 1,
    e_polygon = 2,
    e_chain = 3,
}

box2d.b2BodyType = {
    b2_staticBody = 0,
    b2_kinematicBody = 1,
    b2_dynamicBody = 2,
}

box2d.b2JointType = {
    e_unknownJoint = 0, e_revoluteJoint = 1,
    e_prismaticJoint = 2, e_distanceJoint = 3,
    e_pulleyJoint = 4, e_mouseJoint = 5,
    e_gearJoint = 6, e_wheelJoint = 7,
    e_weldJoint = 8, e_frictionJoint = 9,
    e_ropeJoint = 10, e_motorJoint = 11,
}

box2d.b2Draw = {
    e_shapeBit = 1, e_jointBit = 2,
    e_aabbBit = 4, e_pairBit = 8,
    e_centerOfMassBit = 16
}

box2d.b2Manifold_Type = {
    e_circles = 0,
    e_faceA = 1,
    e_faceB = 2
}
```

## Functions

* box2d.[NewWorld](#box2dnewworldgravity) (gravity)
* box2d.[NewDebugDraw](#box2dnewdebugdrawdata) (data)
* box2d.[b2LinearStiffness](#box2db2linearstiffnessfrequencyhertz-dampingratio-bodya-bodyb) (frequencyHertz, dampingRatio, bodyA, bodyB)
* box2d.[b2AngularStiffness](#box2db2angularstiffnessfrequencyhertz-dampingratio-bodya-bodyb) (frequencyHertz, dampingRatio, bodyA, bodyB)

### box2d.NewWorld(gravity)

**PARAMETERS**
* `gravity` (vector3|nil) - The world gravity vector.

**RETURN**
* [(Box2dWorld)](World.md)

### box2d.NewDebugDraw(data)

**PARAMETERS**
* `data` (table)

**RETURN**
* [(Box2dWorld)](DebugDraw.md)

### box2d.b2LinearStiffness(frequencyHertz, dampingRatio, bodyA, bodyB)
Utility to compute linear stiffness values from frequency and damping ratio

**PARAMETERS**
* `data` (table) -
* `data` (table) -
* `bodyA` [(Box2dBody)](Body.md) -
* `bodyB` [(Box2dBody)](Body.md) -

**RETURN**
* (table) - Stiffness
* (table) - Damping

### box2d.b2AngularStiffness(frequencyHertz, dampingRatio, bodyA, bodyB)
Utility to compute rotational stiffness values from frequency and damping ratio

**PARAMETERS**
* `data` (table) -
* `data` (table) -
* `bodyA` [(Box2dBody)](Body.md) -
* `bodyB` [(Box2dBody)](Body.md) -

**RETURN**
* (table) - Stiffness
* (table) - Damping
