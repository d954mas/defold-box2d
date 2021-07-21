local UTILS = require "tests.test_utils"

local function createFixture(world, shape)
    local body = world:CreateBody()
    local f = body:CreateFixture(shape, 1)
    assert_not_nil(f)
    return f;
end

return function()
    describe("Shape", function()
        before(function()
            UTILS.set_env(getfenv(1))
            setfenv(createFixture, getfenv(1))
        end)
        after(function()

        end)

        test("fixture circle", function()
            local w = box2d.NewWorld()
            local shape = box2d.NewCircleShape()
            shape:SetPosition(vmath.vector3(1, 1, 1))
            shape:SetRadius(1)
            local f = createFixture(w, shape)

            w:Destroy()
        end)

        test("fixture edge", function()
            local w = box2d.NewWorld()
            local shape = box2d.NewEdgeShape()
            shape:SetTwoSided(vmath.vector3(0), vmath.vector3(1, 0, 0))
            local f = createFixture(w, shape)

            shape:SetOneSided(vmath.vector3(0),vmath.vector3(1, 0, 0), vmath.vector3(2, 0, 0), vmath.vector3(3, 0, 0))
            f = createFixture(w, shape)

            assert_equal_v3(shape:GetVertex3(),vmath.vector3(3,0,0))

            w:Destroy()
        end)

        test("fixture polygon", function()
            local w = box2d.NewWorld()
            local shape = box2d.NewPolygonShape()
            shape:SetAsBox(1, 1)
            createFixture(w, shape)
            w:Destroy()
        end)

        test("fixture chain", function()
            local w = box2d.NewWorld()
            local shape = box2d.NewChainShape()
            shape:CreateChain({ vmath.vector3(0, 0, 0), vmath.vector3(1, 0, 0), vmath.vector3(1, 1, 0) },
                    vmath.vector3(0, 0, 0), vmath.vector3(1, 1, 0))
            createFixture(w, shape)
            shape = box2d.NewChainShape()
            shape:CreateLoop({ vmath.vector3(0, 0, 0), vmath.vector3(1, 0, 0), vmath.vector3(1, 1, 0)})
            createFixture(w, shape)

        end)

        test("polygon shape", function()
            local w = box2d.NewWorld()

            local shape = box2d.NewPolygonShape()
            shape:SetAsBox(1, 1)
            assert_equal(shape:GetType(), box2d.b2Shape.e_polygon)

            shape:SetRadius(2)
            assert_equal_float(shape:GetRadius(), 2)
            shape:SetRadius(0.01)
            assert_equal_float(shape:GetRadius(), 0.01)

            local shape_clone = shape:Clone()
            --change
            assert_not_equal(shape, shape_clone)
            assert_equal(shape:GetCount(), shape_clone:GetCount())

            shape_clone:Set({ vmath.vector3(0, 0, 0), vmath.vector3(1, 0, 0), vmath.vector3(1, 1, 0) })
            assert_not_equal(shape:GetCount(), shape_clone:GetCount())

            assert_equal(shape:GetChildCount(), 1)

            shape:TestPoint({ p = vmath.vector3(0), q = 1 }, vmath.vector3(0))

            shape:Set({ vmath.vector3(0, 0, 0), vmath.vector3(1, 0, 0), vmath.vector3(1, 1, 0) })

            local raycast = shape:RayCast({ p1 = vmath.vector3(0, 0, 0), p2 = vmath.vector3(1, 0, 0),
                                            maxFraction = 1 }, { p = vmath.vector3(0), q = 1 })
            assert_nil(raycast)

            raycast = shape:RayCast({ p1 = vmath.vector3(-0.5, -0.5, 0), p2 = vmath.vector3(1.4, 0.7, 0),
                                      maxFraction = 1 }, { p = vmath.vector3(0), q = 0 })

            assert_not_nil(raycast)
            assert_not_nil(raycast.normal)
            assert_not_nil(raycast.fraction)

            local aabb = shape:ComputeAABB({ p = vmath.vector3(0), q = 1 })
            assert_not_nil(aabb.lowerBound)
            assert_not_nil(aabb.upperBound)

            local massData = shape:ComputeMass(1)
            assert_equal(type(massData), "table")

            shape:Set({ vmath.vector3(0, 0, 0), vmath.vector3(1, 0, 0), vmath.vector3(1, 1, 0) })

            shape:SetAsBox(1, 1)
            shape:SetAsBox(1, 1, vmath.vector3(0, 0, 0), 10)

            assert_true(shape:Validate())

            shape:Set({ vmath.vector3(0, 0, 0), vmath.vector3(1, 0, 0), vmath.vector3(1, 1, 0) })

            assert_not_nil(shape:GetCentroid())
            assert_equal(#shape:GetVertices(), 3)
            assert_equal_v3(shape:GetVertices()[1], vmath.vector3(1, 0, 0))
            assert_equal(#shape:GetNormals(), 3)
            assert_equal(shape:GetCount(), 3)

            w:Destroy()
        end)

        test("circle shape", function()
            local w = box2d.NewWorld()

            local shape = box2d.NewCircleShape()
            assert_equal(shape:GetType(), box2d.b2Shape.e_circle)

            assert_equal_float(shape:GetRadius(), 0.0)

            local shape_clone = shape:Clone()
            --change
            assert_not_equal(shape, shape_clone)
            assert_equal(shape:GetRadius(), shape_clone:GetRadius())

            shape_clone:SetRadius(1)
            assert_not_equal(shape:GetRadius(), shape_clone:GetRadius())

            assert_equal(shape:GetChildCount(), 1)

            shape:TestPoint({ p = vmath.vector3(0), q = 1 }, vmath.vector3(0))

            local raycast = shape:RayCast({ p1 = vmath.vector3(2, 0, 0), p2 = vmath.vector3(1, 0, 0),
                                            maxFraction = 1 }, { p = vmath.vector3(0), q = 1 })
            assert_nil(raycast)

            raycast = shape:RayCast({ p1 = vmath.vector3(-1.2, 0, 0), p2 = vmath.vector3(1.2, 0, 0),
                                      maxFraction = 1 }, { p = vmath.vector3(0), q = 0 })

            assert_not_nil(raycast)
            assert_not_nil(raycast.normal)
            assert_not_nil(raycast.fraction)

            local aabb = shape:ComputeAABB({ p = vmath.vector3(0), q = 1 })
            assert_not_nil(aabb.lowerBound)
            assert_not_nil(aabb.upperBound)

            local massData = shape:ComputeMass(1)
            assert_equal(type(massData), "table")

            shape:SetRadius(2)
            assert_equal(shape:GetRadius(), 2)

            shape:SetPosition(vmath.vector3(2, 5, 0))
            assert_equal_v3(shape:GetPosition(), vmath.vector3(2, 5, 0))

            w:Destroy()
        end)

        test("edge shape", function()
            local w = box2d.NewWorld()

            local shape = box2d.NewEdgeShape()
            assert_equal(shape:GetType(), box2d.b2Shape.e_edge)

            assert_equal_float(shape:GetRadius(), 0.01)

            local shape_clone = shape:Clone()
            --change
            assert_not_equal(shape, shape_clone)
            assert_equal(shape:GetRadius(), shape_clone:GetRadius())

            shape_clone:SetRadius(1)
            assert_not_equal(shape:GetRadius(), shape_clone:GetRadius())

            assert_equal(shape:GetChildCount(), 1)

            shape:SetOneSided(vmath.vector3(-1, 0, 0), vmath.vector3(0, 0, 0), vmath.vector3(1, 0, 0), vmath.vector3(2, 0, 0))

            shape:TestPoint({ p = vmath.vector3(0), q = 1 }, vmath.vector3(0))

            local raycast = shape:RayCast({ p1 = vmath.vector3(2, 0, 0), p2 = vmath.vector3(1, 0, 0),
                                            maxFraction = 1 }, { p = vmath.vector3(0), q = 1 })
            assert_nil(raycast)

            raycast = shape:RayCast({ p1 = vmath.vector3(0, -1, 0), p2 = vmath.vector3(0, 1, 0),
                                      maxFraction = 1 }, { p = vmath.vector3(0), q = 0 })

            assert_not_nil(raycast)
            assert_not_nil(raycast.normal)
            assert_not_nil(raycast.fraction)

            local aabb = shape:ComputeAABB({ p = vmath.vector3(0), q = 1 })
            assert_not_nil(aabb.lowerBound)
            assert_not_nil(aabb.upperBound)

            local massData = shape:ComputeMass(1)
            assert_equal(type(massData), "table")

            shape:SetRadius(2)
            assert_equal(shape:GetRadius(), 2)
            shape:SetRadius(0.01)

            shape:SetOneSided(vmath.vector3(-1, 0, 0), vmath.vector3(0, 0, 0), vmath.vector3(1, 0, 0), vmath.vector3(2, 0, 0))
            assert_equal_v3(shape:GetVertex0(), vmath.vector3(-1, 0, 0))
            assert_equal_v3(shape:GetVertex1(), vmath.vector3(0, 0, 0))
            assert_equal_v3(shape:GetVertex2(), vmath.vector3(1, 0, 0))
            assert_equal_v3(shape:GetVertex3(), vmath.vector3(2, 0, 0))
            assert_true(shape:IsOneSided())

            shape:SetTwoSided(vmath.vector3(1, 1, 0), vmath.vector3(2, 2, 0))
            assert_equal_v3(shape:GetVertex1(), vmath.vector3(1, 1, 0))
            assert_equal_v3(shape:GetVertex2(), vmath.vector3(2, 2, 0))
            assert_false(shape:IsOneSided())

            w:Destroy()
        end)

        test("chain shape", function()
            local w = box2d.NewWorld()

            local shape = box2d.NewChainShape()
            assert_equal(shape:GetType(), box2d.b2Shape.e_chain)

            shape:CreateLoop({ vmath.vector3(0, 0, 0), vmath.vector3(1, 1, 0), vmath.vector3(2, 0, 0) })

            assert_equal_float(shape:GetRadius(), 0.01)

            local shape_clone = shape:Clone()
            --change
            assert_not_equal(shape, shape_clone)
            assert_equal(shape:GetRadius(), shape_clone:GetRadius())

            shape_clone:SetRadius(1)
            assert_not_equal(shape:GetRadius(), shape_clone:GetRadius())

            assert_equal(shape:GetChildCount(), 3)

            shape:TestPoint({ p = vmath.vector3(0), q = 1 }, vmath.vector3(0))

            local raycast = shape:RayCast({ p1 = vmath.vector3(2, 0, 0), p2 = vmath.vector3(1, 0, 0),
                                            maxFraction = 1 }, { p = vmath.vector3(0), q = 1 }, 0)
            assert_nil(raycast)

            raycast = shape:RayCast({ p1 = vmath.vector3(-1, 0.5, 0), p2 = vmath.vector3(1, 0.5, 0),
                                      maxFraction = 1 }, { p = vmath.vector3(0), q = 0 }, 0)

            assert_not_nil(raycast)
            assert_not_nil(raycast.normal)
            assert_not_nil(raycast.fraction)

            local aabb = shape:ComputeAABB({ p = vmath.vector3(0), q = 1 }, 1)
            assert_not_nil(aabb.lowerBound)
            assert_not_nil(aabb.upperBound)

            local massData = shape:ComputeMass(1)
            assert_equal(type(massData), "table")

            shape:SetRadius(2)
            assert_equal(shape:GetRadius(), 2)
            shape:SetRadius(0.01)--]]

            assert_equal(#shape:GetVertices(), 3 + 1)

            assert_equal_v3(shape:GetVertices()[1], vmath.vector3(0, 0, 0))
            assert_equal_v3(shape:GetVertices()[2], vmath.vector3(1, 1, 0))
            assert_equal_v3(shape:GetVertices()[3], vmath.vector3(2, 0, 0))
            assert_equal_v3(shape:GetVertices()[4], vmath.vector3(0, 0, 0))
            assert_equal(shape:GetCount(), 3 + 1)
            assert_equal(shape:GetCount(), #shape:GetVertices())

            shape:Clear()
            assert_equal(shape:GetCount(), 0)

            shape:CreateChain({ vmath.vector3(1, 1, 0), vmath.vector3(2, 2, 0) }, vmath.vector3(0, 0, 0), vmath.vector3(3, 3, 0))
            assert_equal(#shape:GetVertices(), 2)

            assert_equal_v3(shape:GetVertices()[1], vmath.vector3(1, 1, 0))
            assert_equal_v3(shape:GetVertices()[2], vmath.vector3(2, 2, 0))
            assert_equal(shape:GetCount(), 2)

            w:Destroy()
        end)
    end)

end