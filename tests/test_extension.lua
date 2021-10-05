return function()
    describe("Extension", function()
        before(function() end)
        after(function() end)

        test("create world", function()
            local w = box2d.NewWorld()
            assert_not_nil(w)
            assert_not_nil(w.__userdata_box2d)
            assert_equal(w.__userdata_type_box2d, "world")
            w:Destroy()
        end)

        test("create debug draw", function()
            local draw = box2d.NewDebugDraw({  })
            assert_not_nil(draw)
            assert_not_nil(draw.__userdata_draw)
        end)

        test("b2LinearStiffness", function()
            local w = box2d.NewWorld()
            local bodyA = w:CreateBody()
            local bodyB = w:CreateBody()
            local stiffness,damping = box2d.b2LinearStiffness(1,1,bodyA,bodyB)
            assert_not_nil(stiffness)
            assert_not_nil(damping)
            w:Destroy()
        end)

        test("b2AngularStiffness", function()
            local w = box2d.NewWorld()
            local bodyA = w:CreateBody()
            local bodyB = w:CreateBody()
            local stiffness,damping = box2d.b2AngularStiffness(1,1,bodyA,bodyB)
            assert_not_nil(stiffness)
            assert_not_nil(damping)
            w:Destroy()
        end)

        test("enums exist", function()
            local function test_enum(enum_name, config)
                assert_not_nil(box2d[enum_name])
                for k, v in pairs(config) do
                    assert_equal(box2d[enum_name][k], v)
                end
            end
            test_enum("b2Shape", { e_circle = 0, e_edge = 1,
                                   e_polygon = 2, e_chain = 3, })
            test_enum("b2BodyType", { b2_staticBody = 0, b2_kinematicBody = 1,
                                      b2_dynamicBody = 2, })
            test_enum("b2JointType", {
                e_unknownJoint = 0, e_revoluteJoint = 1,
                e_prismaticJoint = 2, e_distanceJoint = 3,
                e_pulleyJoint = 4, e_mouseJoint = 5,
                e_gearJoint = 6, e_wheelJoint = 7,
                e_weldJoint = 8, e_frictionJoint = 9,
                e_ropeJoint = 10, e_motorJoint = 11,
            })
            test_enum("b2Draw", {
                e_shapeBit = 1, e_jointBit = 2,
                e_aabbBit = 4, e_pairBit = 8,
                e_centerOfMassBit = 16
            })

            test_enum("b2Manifold_Type", {
                e_circles = 0, e_faceA = 1,
                e_faceB =2
            })
        end)


    end)
end