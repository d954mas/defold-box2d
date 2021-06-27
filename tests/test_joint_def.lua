local UTILS = require "tests.test_utils"

local default_values = {
    bodyA = nil,
    bodyB = nil,
    joint1 = nil,
    joint2 = nil,
    userData = { },
    collideConnected = false,
    anchor = vmath.vector3(0),
    axis = vmath.vector3(1, 0, 0),
    localAnchorA = vmath.vector3(0, 0, 0),
    localAnchorB = vmath.vector3(0, 0, 0),
    referenceAngle = 0,
    enableLimit = false,
    lowerAngle = 0,
    upperAngle = 0,
    enableMotor = false,
    motorSpeed = 0,
    maxMotorTorque = 0,
    localAxisA = vmath.vector3(1, 0, 0),
    lowerTranslation = 0,
    upperTranslation = 1,
    maxMotorForce = 0,
    length = 1.0,
    minLength = 0.1,
    maxLength = math.huge,
    stiffness = 0.0,
    damping = 0.0,
    groundAnchorA = vmath.vector3(0),
    groundAnchorB = vmath.vector3(0),
    lengthA = 0,
    lengthB = 0,
    ratio = 0,
    target = vmath.vector3(0),
    maxForce = 0,
    maxTorque = 0,
    linearOffset = vmath.vector3(0);
    angularOffset = 0;
    correctionFactor = 0;
}

---@param w Box2dWorld
local function testJoint(w, config)
    local joint_def = { type = config.type }
    assert(config.def)
    -- config.def.bodyA = config.def.bodyA or w:CreateBody({})
    --config.def.bodyB = config.def.bodyB or w:CreateBody({})

    default_values.bodyA = w:CreateBody({position = vmath.vector3(0,0,0), type = box2d.b2BodyType.b2_dynamicBody})
    default_values.bodyB = w:CreateBody({position = vmath.vector3(1,1,0), type = box2d.b2BodyType.b2_dynamicBody})
    default_values.joint1 = w:CreateJoint({    type = box2d.b2JointType.e_revoluteJoint,
                                                   bodyA = default_values.bodyA,
                                                   bodyB = default_values.bodyB,
                                                   anchor = vmath.vector3(1, 0, 0)})

    default_values.joint2 = w:CreateJoint({    type = box2d.b2JointType.e_revoluteJoint,
                                               bodyA = default_values.bodyA,
                                               bodyB = default_values.bodyB,
                                               anchor = vmath.vector3(1, 0, 0)})

    for k, v in pairs(config.needed_values) do
        joint_def[k] = v == "default" and default_values[k] or v
    end

    for k, v in pairs(config.def) do
        joint_def[k] = v
    end

    --can have some problems with creation. So try 20 times
    for i=1,20 do
        local status, joint = pcall(w.CreateJoint, w, joint_def)
        if(not status)then
            print("error")
            print(joint)
        end
        assert_true(status)
        assert_not_nil(joint)
    end

    --check no needed value error
    for k, v in pairs(config.needed_values) do
        local prev = joint_def[k]
        assert(prev, "no key:" .. k)
        joint_def[k] = nil
        local status, value = pcall(w.CreateJoint, w, joint_def)
        if(status) then
            print("error")
            print(k)
        end
        assert_false(status)
        if(value ~= string.format("no %s", k))then
            print("error")
            print(value)
            print(string.format("no %s", k))
        end
        assert_equal(value, string.format("no %s", k))
        joint_def[k] = prev
    end

    --check all optional valid
    for k, v in pairs(config.optional_values) do
        local prev = joint_def[k]
        assert(default_values[k] ~= nil, "unknown key:" .. k)
        joint_def[k] = v == "default" and default_values[k] or v
        local status, value = pcall(w.CreateJoint, w, joint_def)
        if(not status)then
            print("error")
            print(value)
        end    
        assert_true(status)
        assert_not_nil(value)
        joint_def[k] = prev
    end

    --check unknown key error
    for k, v in pairs(default_values) do
        if (not config.needed_values[k] and not config.optional_values[k]) then
            assert(not joint_def[k], string.format("%s exist in def", k))
            joint_def[k] = default_values[k]
            
            local status, value = pcall(w.CreateJoint, w, joint_def)
            assert_false(status)
            assert_not_nil(value, "unknown key:" .. k)
            joint_def[k] = nil
            --  end
        end
    end
    return joint

end

return function()
    describe("JointDef", function()
        before(function()
            setfenv(testJoint, getfenv(1))
            UTILS.set_env(getfenv(1))
        end)
        after(function() end)

        test("Create e_unknownJoint", function()
            local w = box2d.NewWorld()
            local status, value = pcall(w.CreateJoint,w,{type = box2d.b2JointType.e_unknownJoint})
            assert_false(status);
            assert_equal(value,"e_unknownJoint not supported")
        end)

        test("Create e_revoluteJoint", function()
            local w = box2d.NewWorld()
            testJoint(w, {
                type = box2d.b2JointType.e_revoluteJoint,
                def = { },
                needed_values = {
                    bodyA = "default",
                    bodyB = "default",
                    anchor = vmath.vector3(1, 0, 0),
                },
                optional_values = {
                    collideConnected = "default",
                    userData = "default",
                    localAnchorA = "default",
                    localAnchorB = "default",
                    referenceAngle = "default";
                    lowerAngle = "default";
                    upperAngle = "default";
                    maxMotorTorque = "default";
                    motorSpeed = "default";
                    enableLimit = "default";
                    enableMotor = "default";
                }
            })
            w:Destroy()
        end)


        test("Create e_prismaticJoint", function()
            local w = box2d.NewWorld()
            testJoint(w, {
                type = box2d.b2JointType.e_prismaticJoint,
                def = { },
                needed_values = {
                    bodyA = "default",
                    bodyB = "default",
                    anchor = vmath.vector3(1, 0, 0),
                    axis = vmath.vector3(1, 0, 0)
                },
                optional_values = {
                    collideConnected = "default",
                    userData = "default",
                    localAnchorA = "default",
                    localAnchorB = "default",
                    localAxisA = "default",
                    referenceAngle = "default";
                    lowerTranslation = "default";
                    upperTranslation = "default";
                    enableLimit = "default";
                    enableMotor = "default";
                    motorSpeed = "default";
                    maxMotorForce = "default";

                }
            })
            w:Destroy()
        end)

        test("Create e_distanceJoint", function()
            local w = box2d.NewWorld()
            testJoint(w, {
                type = box2d.b2JointType.e_distanceJoint,
                def = { },
                needed_values = {
                    bodyA = "default",
                    bodyB = "default",
                    anchorA = vmath.vector3(0, 0, 0),
                    anchorB = vmath.vector3(0, 0, 0),
                },
                optional_values = {
                    collideConnected = "default",
                    userData = "default",
                    localAnchorA = "default",
                    localAnchorB ="default",
                    length = "default",
                    minLength = "default",
                    maxLength = "default",
                    stiffness = "default",
                    damping = "default",

                }
            })
            w:Destroy()
        end)

        test("Create e_pulleyJoint", function()
            local w = box2d.NewWorld()
            testJoint(w, {
                type = box2d.b2JointType.e_pulleyJoint,
                def = { },
                needed_values = {
                    bodyA = "default",
                    bodyB = "default",
                    groundAnchorA = vmath.vector3(0, 0, 0),
                    groundAnchorB = vmath.vector3(0, 0, 0),
                    anchorA = vmath.vector3(0, 0, 0),
                    anchorB = vmath.vector3(0, 0, 0),
                    ratio = 1
                },
                optional_values = {
                    collideConnected = "default",
                    userData = "default",
                    localAnchorA = "default",
                    localAnchorB ="default",
                    lengthA = "default",
                    lengthB = "default",
                }
            })
            w:Destroy()
        end)

        test("Create e_mouseJoint", function()
            local w = box2d.NewWorld()
            testJoint(w, {
                type = box2d.b2JointType.e_mouseJoint,
                def = { },
                needed_values = {
                    bodyA = "default",
                    bodyB = "default",
                },
                optional_values = {
                    collideConnected = "default",
                    userData = "default",
                    target = "default",
                    maxForce ="default",
                    stiffness = "default",
                    damping = "default",
                }
            })
            w:Destroy()
        end)

        test("Create e_gearJoint", function()
            local w = box2d.NewWorld()
            testJoint(w, {
                type = box2d.b2JointType.e_gearJoint,
                def = { },
                needed_values = {
                    joint1 = "default",
                    joint2 = "default",
                    bodyA = "default",
                    bodyB = "default",
                },
                optional_values = {
                    collideConnected = "default",
                    userData = "default",
                    ratio = "default",
                }
            })
            w:Destroy()
        end)

        test("Create e_wheelJoint", function()
            local w = box2d.NewWorld()
            testJoint(w, {
                type = box2d.b2JointType.e_wheelJoint,
                def = { },
                needed_values = {
                    bodyA = "default",
                    bodyB = "default",
                    anchor = "default",
                    axis = "default",
                },
                optional_values = {
                    collideConnected = "default",
                    userData = "default",
                    localAnchorA = "default",
                    localAnchorB = "default",
                    enableLimit = "default",
                    enableMotor = "default",
                    motorSpeed = "default",
                    maxMotorTorque = "default",
                    localAxisA = "default",
                    lowerTranslation = "default",
                    upperTranslation = "default",
                    stiffness = "default",
                    damping = "default",
                }
            })
            w:Destroy()
        end)

        test("Create e_weldJoint", function()
            local w = box2d.NewWorld()
            testJoint(w, {
                type = box2d.b2JointType.e_weldJoint,
                def = { },
                needed_values = {
                    bodyA = "default",
                    bodyB = "default",
                    anchor = "default",
                },
                optional_values = {
                    collideConnected = "default",
                    userData = "default",
                    localAnchorA = "default",
                    localAnchorB = "default",
                    referenceAngle = "default",
                    stiffness = "default",
                    damping = "default",
                }
            })
            w:Destroy()
        end)

        test("Create e_frictionJoint", function()
            local w = box2d.NewWorld()
            testJoint(w, {
                type = box2d.b2JointType.e_frictionJoint,
                def = { },
                needed_values = {
                    bodyA = "default",
                    bodyB = "default",
                    anchor = "default",
                },
                optional_values = {
                    collideConnected = "default",
                    userData = "default",
                    localAnchorA = "default",
                    localAnchorB = "default",
                    maxForce = "default",
                    maxTorque = "default",
                }
            })
            w:Destroy()
        end)

        test("Create e_motorJoint", function()
            local w = box2d.NewWorld()
            testJoint(w, {
                type = box2d.b2JointType.e_motorJoint,
                def = { },
                needed_values = {
                    bodyA = "default",
                    bodyB = "default",
                },
                optional_values = {
                    collideConnected = "default",
                    userData = "default",
                    linearOffset = "default",
                    angularOffset = "default",
                    maxForce = "default",
                    maxTorque = "default",
                    correctionFactor = "default",
                }
            })
            w:Destroy()
        end)

        test("Create e_ropeJoint", function()
            local w = box2d.NewWorld()
            local status, value = pcall(w.CreateJoint,w,{type = box2d.b2JointType.e_ropeJoint})
            assert_false(status);
            assert_equal(value,"e_ropeJoint not supported")
        end)

        test("Create bad type", function()
            local w = box2d.NewWorld()
            local status, value = pcall(w.CreateJoint,w,{type = 128})
            assert_false(status);
            assert_equal(value,"bad joint type")
        end)
    end)
end