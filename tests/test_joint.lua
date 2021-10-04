local UTILS = require "tests.test_utils"
local LUME = require "libs.lume"

---@param w:Box2dWorld
local create_revoluteJoint = function(w)
    local bodyA = w:CreateBody({ position = vmath.vector3(0, 0, 0), type = box2d.b2BodyType.b2_dynamicBody })
    local bodyB = w:CreateBody({ position = vmath.vector3(1, 1, 0), type = box2d.b2BodyType.b2_dynamicBody })
    local joint = w:CreateJoint(box2d.InitializeRevoluteJointDef(bodyA,bodyB,vmath.vector3(0,0,0)))
    return joint, bodyA, bodyB
end

local create_prismaticJoint = function(w)
    local bodyA = w:CreateBody({ position = vmath.vector3(0, 0, 0), type = box2d.b2BodyType.b2_dynamicBody })
    local bodyB = w:CreateBody({ position = vmath.vector3(1, 1, 0), type = box2d.b2BodyType.b2_dynamicBody })
    local joint = w:CreateJoint(box2d.InitializePrismaticJointDef(bodyA,bodyB,vmath.vector3(1, 0, 0),vmath.vector3(1, 0, 0)))

    return joint, bodyA, bodyB
end

local create_distanceJoint = function(w)
    local bodyA = w:CreateBody({ position = vmath.vector3(0, 0, 0), type = box2d.b2BodyType.b2_dynamicBody })
    local bodyB = w:CreateBody({ position = vmath.vector3(1, 1, 0), type = box2d.b2BodyType.b2_dynamicBody })
    local joint = w:CreateJoint(box2d.InitializeDistanceJointDef(bodyA,bodyB,vmath.vector3(0),vmath.vector3(1,0,0)))
    return joint, bodyA, bodyB
end

local create_pulleyJoint = function(w)
    local bodyA = w:CreateBody({ position = vmath.vector3(0, 0, 0), type = box2d.b2BodyType.b2_dynamicBody })
    local bodyB = w:CreateBody({ position = vmath.vector3(1, 1, 0), type = box2d.b2BodyType.b2_dynamicBody })
    local joint = w:CreateJoint(box2d.InitializePulleyJointDef(bodyA,bodyB,vmath.vector3(0),vmath.vector3(0),
    vmath.vector3(0),vmath.vector3(0),1))
    return joint, bodyA, bodyB
end

local create_mouseJoint = function(w)
    local bodyA = w:CreateBody({ position = vmath.vector3(0, 0, 0), type = box2d.b2BodyType.b2_dynamicBody })
    local bodyB = w:CreateBody({ position = vmath.vector3(1, 1, 0), type = box2d.b2BodyType.b2_dynamicBody })
    local joint = w:CreateJoint({
        type = box2d.b2JointType.e_mouseJoint,
        bodyA = bodyA,
        bodyB = bodyB,
    })
    return joint, bodyA, bodyB
end
local create_gearJoint = function(w)
    local bodyA = w:CreateBody({ position = vmath.vector3(0, 0, 0), type = box2d.b2BodyType.b2_dynamicBody })
    local bodyB = w:CreateBody({ position = vmath.vector3(1, 1, 0), type = box2d.b2BodyType.b2_dynamicBody })
    local joint1 = w:CreateJoint({ type = box2d.b2JointType.e_revoluteJoint,
                                   bodyA = bodyA,
                                   bodyB = bodyB})

    local joint2 = w:CreateJoint({ type = box2d.b2JointType.e_revoluteJoint,
                                   bodyA = bodyA,
                                   bodyB = bodyB})
    local joint = w:CreateJoint({
        type = box2d.b2JointType.e_gearJoint,
        bodyA = bodyA,
        bodyB = bodyB,
        joint1 = joint1,
        joint2 = joint2
    })
    return joint, bodyA, bodyB, joint1, joint2
end

local create_wheelJoint = function(w)
    local bodyA = w:CreateBody({ position = vmath.vector3(0, 0, 0), type = box2d.b2BodyType.b2_dynamicBody })
    local bodyB = w:CreateBody({ position = vmath.vector3(1, 1, 0), type = box2d.b2BodyType.b2_dynamicBody })
    local joint = w:CreateJoint(box2d.InitializeWheelJointDef(bodyA,bodyB,vmath.vector3(1,0,0),vmath.vector3(1,0,0)))
    return joint, bodyA, bodyB
end

local create_weldJoint = function(w)
    local bodyA = w:CreateBody({ position = vmath.vector3(0, 0, 0), type = box2d.b2BodyType.b2_dynamicBody })
    local bodyB = w:CreateBody({ position = vmath.vector3(1, 1, 0), type = box2d.b2BodyType.b2_dynamicBody })
    local joint = w:CreateJoint(box2d.InitializeWeldJointDef(bodyA,bodyB,vmath.vector3(1,0,0)))

    return joint, bodyA, bodyB
end

local create_frictionJoint = function(w)
    local bodyA = w:CreateBody({ position = vmath.vector3(0, 0, 0), type = box2d.b2BodyType.b2_dynamicBody })
    local bodyB = w:CreateBody({ position = vmath.vector3(1, 1, 0), type = box2d.b2BodyType.b2_dynamicBody })
    local joint = w:CreateJoint(box2d.InitializeFrictionJointDef(bodyA,bodyB,vmath.vector3(1,0,0)))
    return joint, bodyA, bodyB
end

local create_motorJoint = function(w)
    local bodyA = w:CreateBody({ position = vmath.vector3(0, 0, 0), type = box2d.b2BodyType.b2_dynamicBody })
    local bodyB = w:CreateBody({ position = vmath.vector3(1, 1, 0), type = box2d.b2BodyType.b2_dynamicBody })
    local joint = w:CreateJoint(box2d.InitializeMotorJointDef(bodyA,bodyB))
    return joint, bodyA, bodyB
end

local JOINTS = {
    [box2d.b2JointType.e_revoluteJoint] = { creator = create_revoluteJoint },
    [box2d.b2JointType.e_prismaticJoint] = { creator = create_prismaticJoint },
    [box2d.b2JointType.e_distanceJoint] = { creator = create_distanceJoint },
    [box2d.b2JointType.e_pulleyJoint] = { creator = create_pulleyJoint },
    [box2d.b2JointType.e_mouseJoint] = { creator = create_mouseJoint },
    [box2d.b2JointType. e_gearJoint] = { creator = create_gearJoint },
    [box2d.b2JointType.e_wheelJoint] = { creator = create_wheelJoint },
    [box2d.b2JointType.e_weldJoint] = { creator = create_weldJoint },
    [box2d.b2JointType.e_frictionJoint] = { creator = create_frictionJoint },
    --  [box2d.b2JointType.e_ropeJoint] = { },
    [box2d.b2JointType.e_motorJoint] = { creator = create_motorJoint },
}

local all_joints = {
    box2d.b2JointType.e_revoluteJoint, box2d.b2JointType.e_prismaticJoint,
    box2d.b2JointType.e_distanceJoint, box2d.b2JointType.e_pulleyJoint,
    box2d.b2JointType.e_mouseJoint, box2d.b2JointType.e_gearJoint,
    box2d.b2JointType.e_wheelJoint, box2d.b2JointType.e_weldJoint,
    box2d.b2JointType.e_frictionJoint, --e_ropeJoint = 10,
    box2d.b2JointType.e_motorJoint,
}

local jtype = box2d.b2JointType

local FUNCTIONS = {
    GetType = { name = "GetType", joints = all_joints },
    GetBodyA = { name = "GetBodyA", joints = all_joints },
    GetBodyB = { name = "GetBodyB", joints = all_joints },
    GetAnchorA = { name = "GetAnchorA", joints = all_joints },
    GetAnchorB = { name = "GetAnchorB", joints = all_joints },
    GetReactionForce = { name = "GetReactionForce", args = { 1 }, joints = all_joints },
    GetReactionTorque = { name = "GetReactionTorque", args = { 1 }, joints = all_joints },
    GetNext = { name = "GetNext", joints = all_joints },
    IsEnabled = { name = "IsEnabled", joints = all_joints },
    GetCollideConnected = { name = "GetCollideConnected", joints = all_joints },
    Dump = { name = "Dump", joints = all_joints },
    ShiftOrigin = { name = "ShiftOrigin", args = { vmath.vector3(1, 1, 0) }, joints = all_joints },
    GetLocalAnchorA = { name = "GetLocalAnchorA", joints = { jtype.e_revoluteJoint, jtype.e_prismaticJoint,
                                                             jtype.e_distanceJoint, jtype.e_wheelJoint, jtype.e_weldJoint, jtype.e_frictionJoint } },
    GetLocalAnchorB = { name = "GetLocalAnchorB", joints = { jtype.e_revoluteJoint, jtype.e_prismaticJoint,
                                                             jtype.e_distanceJoint, jtype.e_wheelJoint, jtype.e_weldJoint, jtype.e_frictionJoint } },
    GetReferenceAngle = { name = "GetReferenceAngle", joints = { jtype.e_revoluteJoint, jtype.e_prismaticJoint, jtype.e_weldJoint } },
    GetJointAngle = { name = "GetJointAngle", joints = { jtype.e_revoluteJoint, jtype.e_wheelJoint } },
    GetJointSpeed = { name = "GetJointSpeed", joints = { jtype.e_revoluteJoint, jtype.e_prismaticJoint } },
    Get_Set_EnableLimit = { name = "Get/Set EnableLimit", joints = { jtype.e_revoluteJoint, jtype.e_prismaticJoint, jtype.e_wheelJoint },
                            test_method_get_set = { key = "EnableLimit", config = {
                                getter_full = "IsLimitEnabled", setter_full = "EnableLimit",
                                values = { true, false, true }
                            } }
    },
    Get_Set_EnableMotor = { name = "Get/Set EnableMotor", joints = { jtype.e_revoluteJoint, jtype.e_prismaticJoint, jtype.e_wheelJoint },
                            test_method_get_set = { key = "EnableMotor", config = {
                                getter_full = "IsMotorEnabled", setter_full = "EnableMotor",
                                values = { true, false, true }
                            } }
    },
    Get_Set_MotorSpeed = { name = "Get/Set MotorSpeed", joints = { jtype.e_revoluteJoint, jtype.e_prismaticJoint, jtype.e_wheelJoint },
                           test_method_get_set = { key = "MotorSpeed", config = {
                               getter_full = "GetMotorSpeed", setter_full = "SetMotorSpeed",
                               values = { 2, -2, 10 }
                           } }
    },
    Get_Set_MaxMotorTorque = { name = "Get/Set MaxMotorTorque", joints = { jtype.e_revoluteJoint, jtype.e_wheelJoint },
                               test_method_get_set = { key = "MaxMotorTorque", config = {
                                   getter_full = "GetMaxMotorTorque", setter_full = "SetMaxMotorTorque",
                                   values = { 2, -2, 10 }
                               } }
    },
    GetMotorTorque = { name = "GetMotorTorque", args = { 1 }, joints = { jtype.e_revoluteJoint, jtype.e_prismaticJoint } },
    GetLocalAxisA = { name = "GetLocalAxisA", joints = { jtype.e_prismaticJoint, jtype.e_wheelJoint } },
    GetJointTranslation = { name = "GetJointTranslation", joints = { jtype.e_prismaticJoint, jtype.e_wheelJoint } },
    Get_Set_MaxMotorForce = { name = "Get/Set MaxMotorForce", joints = { jtype.e_prismaticJoint },
                              test_method_get_set = { key = "MaxMotorForce", config = {
                                  getter_full = "GetMaxMotorForce", setter_full = "SetMaxMotorForce",
                                  values = { 2, -2, 10 }
                              } }
    },
    GetMotorForce = { name = "GetMotorForce", args = { 1 }, joints = { jtype.e_prismaticJoint } },

    Get_Set_Length = { name = "Get/Set Length", joints = { jtype.e_distanceJoint },
                       test_method_get_set = { key = "Length", config = {
                           values = { 2, 5, 10 }
                       } }
    },
    Get_Set_MinLength = { name = "Get/Set MinLength", joints = { jtype.e_distanceJoint },
                          test_method_get_set = { key = "MinLength", config = {
                              values = { 0.1, 0.5, 0.25 }, float = true
                          } }
    },
    Get_Set_MaxLength = { name = "Get/Set MaxLength", joints = { jtype.e_distanceJoint },
                          test_method_get_set = { key = "MaxLength", config = {
                              values = { 2, 5, 10 }
                          } }
    },
    GetCurrentLength = { name = "GetCurrentLength", joints = { jtype.e_distanceJoint } },

    Get_Set_Stiffness = { name = "Get/Set Stiffness", joints = { jtype.e_distanceJoint, jtype.e_mouseJoint, jtype.e_wheelJoint, jtype.e_weldJoint },
                          test_method_get_set = { key = "Stiffness", config = {
                              values = { 2, 5, 10 }
                          } }
    },
    Get_Set_Damping = { name = "Get/Set Damping", joints = { jtype.e_distanceJoint, jtype.e_mouseJoint, jtype.e_wheelJoint, jtype.e_weldJoint },
                        test_method_get_set = { key = "Damping", config = {
                            values = { 2, 5, 10 }
                        } }
    },
    GetGroundAnchorA = { name = "GetGroundAnchorA", joints = { jtype.e_pulleyJoint } },
    GetGroundAnchorB = { name = "GetGroundAnchorB", joints = { jtype.e_pulleyJoint } },
    GetLengthA = { name = "GetLengthA", joints = { jtype.e_pulleyJoint } },
    GetLengthB = { name = "GetLengthB", joints = { jtype.e_pulleyJoint } },
    GetRatio = { name = "GetRatio", joints = { jtype.e_pulleyJoint, jtype.e_gearJoint } },
    SetRatio = { name = "SetRatio", args = { 1 }, joints = { jtype.e_gearJoint } },
    GetCurrentLengthA = { name = "GetCurrentLengthA", joints = { jtype.e_pulleyJoint } },
    GetCurrentLengthB = { name = "GetCurrentLengthB", joints = { jtype.e_pulleyJoint } },
    Get_Set_Target = { name = "Get/Set Target", joints = { jtype.e_mouseJoint },
                       test_method_get_set = { key = "Target", config = {
                           v3 = true,
                           values = { vmath.vector3(10, 10, 0), vmath.vector3(-50, -25, 0) }
                       } }
    },
    Get_Set_MaxForce = { name = "Get/Set MaxForce", joints = { jtype.e_mouseJoint, jtype.e_frictionJoint, jtype.e_motorJoint },
                         test_method_get_set = { key = "MaxForce", config = {
                             values = { 10, 50, 0.5 }, float = true
                         } }
    },
    GetJointLinearSpeed = { name = "GetJointLinearSpeed", joints = { jtype.e_wheelJoint } },
    GetJointAngularSpeed = { name = "GetJointAngularSpeed", joints = { jtype.e_wheelJoint } },

    Get_Set_MaxTorque = { name = "Get/Set MaxTorque", joints = { jtype.e_frictionJoint, jtype.e_motorJoint, jtype.e_motorJoint },
                          test_method_get_set = { key = "MaxTorque", config = {
                              values = { 10, 50, 0.5 }, float = true
                          } }
    },

    Get_Set_LinearOffset = { name = "Get/Set LinearOffset", joints = { jtype.e_motorJoint },
                          test_method_get_set = { key = "LinearOffset", config = {
                              values = { vmath.vector3(1,1,0),vmath.vector3(0.5,2,0) }, v3 = true
                          } }
    },

    Get_Set_AngularOffset = { name = "Get/Set AngularOffset", joints = { jtype.e_motorJoint },
                          test_method_get_set = { key = "AngularOffset", config = {
                              values = { 10, 50, 0.5 }, float = true
                          } }
    },

    Get_Set_CorrectionFactor = { name = "Get/Set CorrectionFactor", joints = { jtype.e_motorJoint },
                              test_method_get_set = { key = "CorrectionFactor", config = {
                                  values = { 0, 0.5, 1 }, float = true
                              } }
    },
}

local function test_function(f)
    local all = LUME.clone(all_joints)
    for _, joint_type in ipairs(all) do
        local w = box2d.NewWorld()
        local joint, b1, b2 = JOINTS[joint_type].creator(w)
        if (LUME.findi(f.joints, joint_type)) then
            local status, result
            if (f.test_method_get_set) then
                UTILS.test_method_get_set(joint, f.test_method_get_set.key, f.test_method_get_set.config)
            else
                assert(joint[f.name], "no function:" .. f.name)
                if (f.name == "GetNext") then
                    if (joint_type ~= box2d.b2JointType.e_gearJoint) then
                        status, result = pcall(joint[f.name], joint)
                        assert_true(status)
                        assert_nil(result)
                    end

                    local j2 = create_revoluteJoint(w)
                    status, result = pcall(j2.GetNext, j2)
                    assert_true(status)
                    assert_equal(result, joint)

                    if (joint_type ~= box2d.b2JointType.e_gearJoint) then
                        status, result = pcall(joint.GetNext, joint)
                        assert_true(status)
                        assert_nil(result)
                    end
                else
                    if (f.args) then
                        status, result = pcall(joint[f.name], joint, unpack(f.args))
                    else
                        status, result = pcall(joint[f.name], joint)
                    end
                end
                if (not status) then
                    print(joint_type)
                    print("error")
                    print(result)
                end

                assert_true(status)
                if (f.name == "GetType") then
                    assert_equal(joint_type, result)
                elseif (f.name == "GetBodyA") then
                    assert_equal(result, b1)
                elseif (f.name == "GetBodyB") then
                    assert_equal(result, b2)
                else
                    if (f.result) then
                        local equals = assert_equal
                        if (f.result_v3) then equals = assert_equal_v3 end
                        equals(result, f.result)
                    end
                end
            end
        else
            if (f.test_method_get_set) then
                local getter = joint[f.test_method_get_set.config.getter_full]
                local setter = joint[f.test_method_get_set.config.setter_full]
                if (not getter) then
                    getter = joint[(f.test_method_get_set.config.getter or "Get") .. f.test_method_get_set.key]
                end
                if (not setter) then
                    setter = joint[(f.test_method_get_set.config.setter or "Set") .. f.test_method_get_set.key]
                end
                assert(getter, "no getter")
                assert(setter, "no setter")

                local status, result
                status, result = pcall(getter, joint)
                assert_false(status)
                UTILS.test_error(result,"function not supported")

                status, result = pcall(setter, joint, f.test_method_get_set.config.values[1])
                assert_false(status)
                UTILS.test_error(result, "function not supported")
            else
                assert(joint[f.name], "no function:" .. f.name)
                local status, result
                if (f.args) then
                    status, result = pcall(joint[f.name], joint, unpack(f.args))
                else
                    status, result = pcall(joint[f.name], joint)
                end
                assert_false(status)
                UTILS.test_error(result,"function not supported")
            end
        end
        w:Destroy()
    end
end

return function()
    describe("Joint", function()
        before(function()
            UTILS.set_env(getfenv(1))
            setfenv(test_function, getfenv(1))
        end)
        after(function() end)

        test("world:DestroyJoint()", function()
            local w = box2d.NewWorld()
            local b = w:CreateBody()
            local b2 = w:CreateBody()
            local joint = w:CreateJoint({type = box2d.b2JointType.e_revoluteJoint, bodyA = b, bodyB = b2})

            joint:GetType()
            w:DestroyJoint(joint)

            local status, value = pcall(joint.GetType,joint)
            assert_false(status)
            UTILS.test_error(value, "Joint already destroyed")
        end)

        test("destroy joint after body destroyed", function()
            local w = box2d.NewWorld()
            local b = w:CreateBody()
            local b2 = w:CreateBody()
            local joint = w:CreateJoint({type = box2d.b2JointType.e_revoluteJoint, bodyA = b, bodyB = b2})

            joint:GetType()
            w:DestroyBody(b)

            local status, value = pcall(joint.GetType,joint)
            assert_false(status)
            UTILS.test_error(value, "Joint already destroyed")
        end)

        test("destroy joint after world destroyed", function()
            local w = box2d.NewWorld()
            local b = w:CreateBody()
            local b2 = w:CreateBody()
            local joint = w:CreateJoint({type = box2d.b2JointType.e_revoluteJoint, bodyA = b, bodyB = b2})

            joint:GetType()
            w:Destroy()

            local status, value = pcall(joint.GetType,joint)
            assert_false(status)
            UTILS.test_error(value, "Joint already destroyed")
        end)

        test("GetType()", function() test_function(FUNCTIONS.GetType) end)

        test("GetBodyA()", function() test_function(FUNCTIONS.GetBodyB) end)

        test("GetBodyB()", function() test_function(FUNCTIONS.GetBodyB) end)
        test("GetAnchorA()", function() test_function(FUNCTIONS.GetAnchorA) end)
        test("GetAnchorB()", function() test_function(FUNCTIONS.GetAnchorB) end)
        test("GetReactionForce()", function() test_function(FUNCTIONS.GetReactionForce) end)
        test("GetReactionTorque()", function() test_function(FUNCTIONS.GetReactionTorque) end)
        test("GetNext()", function() test_function(FUNCTIONS.GetNext) end)
        test("IsEnabled()", function() test_function(FUNCTIONS.IsEnabled) end)
        test("GetCollideConnected()", function() test_function(FUNCTIONS.GetCollideConnected) end)
        test("Dump()", function() test_function(FUNCTIONS.Dump) end)
        test("ShiftOrigin()", function() test_function(FUNCTIONS.ShiftOrigin) end)
        test("Set/Get UserData()()", function()
            local all = LUME.clone(all_joints)
            for _, joint_type in ipairs(all) do
                local w = box2d.NewWorld()
                local joint, b1, b2 = JOINTS[joint_type].creator(w)
                local userdata = {}
                assert_nil(joint:GetUserData())
                joint:SetUserData(userdata)
                assert_equal(joint:GetUserData(), userdata)
                joint:SetUserData(nil)
                assert_nil(joint:GetUserData())
                w:Destroy()
            end
        end)
        test("GetLocalAnchorA()", function() test_function(FUNCTIONS.GetLocalAnchorA) end)
        test("GetLocalAnchorB()", function() test_function(FUNCTIONS.GetLocalAnchorB) end)
        test("GetReferenceAngle()", function() test_function(FUNCTIONS.GetReferenceAngle) end)
        test("GetJointAngle()", function() test_function(FUNCTIONS.GetJointAngle) end)
        test("GetJointSpeed()", function() test_function(FUNCTIONS.GetJointSpeed) end)
        test("Set/Get EnableLimit()", function() test_function(FUNCTIONS.Get_Set_EnableLimit) end)
        test("Set/Get Limits()", function()
            local all = LUME.clone(all_joints)
            local supported = { box2d.b2JointType.e_revoluteJoint, box2d.b2JointType.e_prismaticJoint, box2d.b2JointType.e_wheelJoint }
            for _, joint_type in ipairs(all) do
                local w = box2d.NewWorld()
                local joint, b1, b2 = JOINTS[joint_type].creator(w)
                if (LUME.findi(supported, joint_type)) then
                    local values = { { 1, 2 }, { 5, 10 } }
                    for _, limits in ipairs(values) do
                        local status, result = pcall(joint.SetLimits, joint, limits[1], limits[2])
                        assert_true(status)
                        status, result = pcall(joint.GetUpperLimit, joint)
                        assert_true(status)
                        assert_equal(limits[2], result)
                        status, result = pcall(joint.GetLowerLimit, joint)
                        assert_true(status)
                        assert_equal(limits[1], result)
                    end
                else
                    local status, result = pcall(joint.GetUpperLimit, joint)
                    assert_false(status)
                    UTILS.test_error(result,"function not supported")

                    status, result = pcall(joint.GetLowerLimit, joint)
                    assert_false(status)
                    UTILS.test_error(result,"function not supported")

                    status, result = pcall(joint.SetLimits, joint, 1, 2)
                    assert_false(status)
                    UTILS.test_error(result,"function not supported")
                end
            end
        end)
        test("Set/Get EnableMotor()", function() test_function(FUNCTIONS.Get_Set_EnableMotor) end)
        test("Set/Get MotorSpeed()", function() test_function(FUNCTIONS.Get_Set_MotorSpeed) end)
        test("Set/Get MaxMotorTorque()", function() test_function(FUNCTIONS.Get_Set_MaxMotorTorque) end)
        test("GetMotorTorque()", function() test_function(FUNCTIONS.Get_Set_MaxMotorTorque) end)
        test("GetLocalAxisA()", function() test_function(FUNCTIONS.GetLocalAxisA) end)
        test("GetJointTranslation()", function() test_function(FUNCTIONS.GetJointTranslation) end)
        test("Set/Get MaxMotorForce()", function() test_function(FUNCTIONS.Get_Set_MaxMotorForce) end)
        test("GetMotorForce()", function() test_function(FUNCTIONS.GetMotorForce) end)
        test("Set/Get Length()", function() test_function(FUNCTIONS.Get_Set_Length) end)
        test("Set/Get MinLength()", function() test_function(FUNCTIONS.Get_Set_MinLength) end)
        test("Set/Get MaxLength()", function() test_function(FUNCTIONS.Get_Set_MaxLength) end)
        test("GetCurrentLength()", function() test_function(FUNCTIONS.GetCurrentLength) end)
        test("Set/Get Stiffness()", function() test_function(FUNCTIONS.Get_Set_Stiffness) end)
        test("Set/Get Damping()", function() test_function(FUNCTIONS.Get_Set_Damping) end)
        test("GetGroundAnchorA()", function() test_function(FUNCTIONS.GetGroundAnchorA) end)
        test("GetGroundAnchorB()", function() test_function(FUNCTIONS.GetGroundAnchorB) end)
        test("GetLengthA()", function() test_function(FUNCTIONS.GetLengthA) end)
        test("GetLengthB()", function() test_function(FUNCTIONS.GetLengthB) end)
        test("GetRatio()", function() test_function(FUNCTIONS.GetRatio) end)
        test("SetRatio()", function() test_function(FUNCTIONS.SetRatio) end)
        test("GetCurrentLengthA()", function() test_function(FUNCTIONS.GetCurrentLengthA) end)
        test("GetCurrentLengthB()", function() test_function(FUNCTIONS.GetCurrentLengthB) end)
        test("Set/Get Target()", function() test_function(FUNCTIONS.Get_Set_Target) end)
        test("Set/Get MaxForce()", function() test_function(FUNCTIONS.Get_Set_MaxForce) end)
        test("GetJoint1/2()", function()
            test_function(FUNCTIONS.Get_Set_MaxForce)
            local all = LUME.clone(all_joints)
            local supported = { box2d.b2JointType.e_gearJoint }
            for _, joint_type in ipairs(all) do
                local w = box2d.NewWorld()
                local joint, b1, b2, j1, j2 = JOINTS[joint_type].creator(w)
                if (LUME.findi(supported, joint_type)) then
                    local status, result = pcall(joint.GetJoint1, joint)
                    assert_true(status)
                    assert_equal(result, j1)

                    status, result = pcall(joint.GetJoint2, joint)
                    assert_true(status)
                    assert_equal(result, j2)
                else
                    local status, result = pcall(joint.GetJoint1, joint)
                    assert_false(status)
                    UTILS.test_error(result,"function not supported")

                    status, result = pcall(joint.GetJoint2, joint)
                    assert_false(status)
                    UTILS.test_error(result,"function not supported")
                end
            end
        end)
        test("GetJointLinearSpeed()", function() test_function(FUNCTIONS.GetJointLinearSpeed) end)
        test("GetJointAngularSpeed()", function() test_function(FUNCTIONS.GetJointAngularSpeed) end)
        test("Set/Get MaxTorque()", function() test_function(FUNCTIONS.Get_Set_MaxTorque) end)
        test("Set/Get LinearOffset()", function() test_function(FUNCTIONS.Get_Set_LinearOffset) end)
        test("Set/Get AngularOffset()", function() test_function(FUNCTIONS.Get_Set_AngularOffset) end)
        test("Set/Get CorrectionFactor()", function() test_function(FUNCTIONS.Get_Set_CorrectionFactor) end)

    end)
end