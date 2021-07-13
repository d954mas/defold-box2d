local UTILS = require "tests.test_utils"

local function testContact(w, cb)
    local contacts = {
        BeginContact = {},
        EndContact = {},
        PreSolve = {},
        PostSolve = {},
    }
    w:SetContactListener({
        ---@param contact Box2dContact
        BeginContact = function(contact)
            table.insert(contacts.BeginContact, true)
            cb("BeginContact", contact)
        end,
        EndContact = function(contact)
            table.insert(contacts.EndContact, true)
            cb("EndContact", contact)
        end,
        PreSolve = function(contact, old_manifold)
            table.insert(contacts.PreSolve, true)
            cb("PreSolve", contact)
        end,
        PostSolve = function(contact, impulse)
            table.insert(contacts.PostSolve, true)
            cb("PostSolve", contact)
        end,
    })

    local b1 = w:CreateBody({ type = box2d.b2BodyType.b2_dynamicBody, position = vmath.vector3(0, 0, 0) })
    local b2 = w:CreateBody({ type = box2d.b2BodyType.b2_dynamicBody, position = vmath.vector3(1, 1, 0) })

    b1:CreateFixture({ shape = box2d.b2Shape.e_polygon, box = true, box_hy = 1, box_hx = 1 }, 1)
    b2:CreateFixture({ shape = box2d.b2Shape.e_polygon, box = true, box_hy = 1, box_hx = 1 }, 1)

    w:Step(1 / 60, 3, 5)

    assert_equal(#contacts.BeginContact, 1)
    assert_equal(#contacts.EndContact, 0)
    assert_equal(#contacts.PreSolve, 1)
    assert_equal(#contacts.PostSolve, 1)
end

return function()
    describe("Contact", function()
        before(function()
            UTILS.set_env(getfenv(1))
            setfenv(testContact, getfenv(1))
        end)
        after(function() end)

        test("IsTouching()", function()
            local w = box2d.NewWorld()
            ---@param contact Box2dContact
            testContact(w, function(name, contact)
                assert_true(contact:IsTouching())
            end)
            w:Destroy()
        end)

        test("Set/Is Enabled()", function()
            local w = box2d.NewWorld()
            ---@param contact Box2dContact
            testContact(w, function(name, contact)
                UTILS.test_method_get_set(contact, "Enabled",
                        {
                            getter = "Is",
                            values = { true, false, true }
                        })
            end)
            w:Destroy()
        end)

        test("GetFixtureA/B()", function()
            local w = box2d.NewWorld()
            ---@param contact Box2dContact
            testContact(w, function(name, contact)
                local fixture_a = contact:GetFixtureA()
                local fixture_b = contact:GetFixtureB()
                assert_not_nil(fixture_a)
                assert_not_nil(fixture_b)
                assert_not_equal(fixture_a, fixture_b)
            end)
            w:Destroy()
        end)

        test("GetChildIndexA/B()", function()
            local w = box2d.NewWorld()
            ---@param contact Box2dContact
            testContact(w, function(name, contact)
                local index_a = contact:GetChildIndexA()
                local index_b = contact:GetChildIndexB()
                assert_equal(type(index_a), "number")
                assert_equal(type(index_b), "number")
            end)
            w:Destroy()
        end)

        test("Set/Get/Reset Friction()", function()
            local w = box2d.NewWorld()
            ---@param contact Box2dContact
            testContact(w, function(name, contact)
                local value = contact:GetFriction()
                UTILS.test_method_get_set(contact, "Friction",
                        {
                            values = { 0, 1, 1.4 },
                            float = true
                        })
                assert_not_equal(value, contact:GetFriction())
                contact:ResetFriction()
                assert_equal_float(value, contact:GetFriction())
            end)
            w:Destroy()
        end)

        test("Set/Get/Reset Restitution()", function()
            local w = box2d.NewWorld()
            ---@param contact Box2dContact
            testContact(w, function(name, contact)
                local value = contact:GetRestitution()
                UTILS.test_method_get_set(contact, "Restitution",
                        {
                            values = { 0, 1, 1.4 },
                            float = true
                        })
                assert_not_equal(value, contact:GetRestitution())
                contact:ResetRestitution()
                assert_equal_float(value, contact:GetRestitution())

            end)
            w:Destroy()
        end)

        test("Set/Get/Reset RestitutionThreshold()", function()
            local w = box2d.NewWorld()
            ---@param contact Box2dContact
            testContact(w, function(name, contact)
                local value = contact:GetRestitutionThreshold()
                UTILS.test_method_get_set(contact, "RestitutionThreshold",
                        {
                            values = { 0, 1, 1.4 },
                            float = true
                        })
                assert_not_equal(value, contact:GetRestitutionThreshold())
                contact:ResetRestitutionThreshold()
                assert_equal_float(value, contact:GetRestitutionThreshold())

            end)
            w:Destroy()
        end)

        test("Set/Get TangentSpeed()", function()
            local w = box2d.NewWorld()
            ---@param contact Box2dContact
            testContact(w, function(name, contact)
                UTILS.test_method_get_set(contact, "TangentSpeed",
                        {
                            values = { 0, 1, 1.4 },
                            float = true
                        })
            end)
            w:Destroy()
        end)

        test("GetManifold()", function()
            local w = box2d.NewWorld()
            ---@param contact Box2dContact
            testContact(w, function(name, contact)
                local manifold = contact:GetManifold()
                assert_equal(type(manifold), "table")
                assert_equal(manifold.type, box2d.b2Manifold_Type.e_faceA)
                assert_equal_v3(manifold.localPoint, vmath.vector3(1, 0, 0))
                assert_equal_v3(manifold.localNormal, vmath.vector3(1, 0, 0))
                assert_equal(#manifold.points, manifold.pointCount)
                assert_equal(#manifold.points, 2)
                for i, point in ipairs(manifold.points) do
                    if (i == 1) then
                        assert_equal_v3(point.localPoint, vmath.vector3(-1, -1, 0))
                        assert_equal_float(point.normalImpulse, 0)
                        assert_equal_float(point.tangentImpulse, 0)
                        assert_equal(type(point.id), "table")
                        assert_equal(type(point.id.cf), "table")
                        assert_equal(type(point.id.key), "number")
                    elseif (i == 2) then
                        assert_equal_v3(point.localPoint, vmath.vector3(-1, 0.019999980926514, 0))
                        assert_equal_float(point.normalImpulse, 0)
                        assert_equal_float(point.tangentImpulse, 0)
                        assert_equal(type(point.id), "table")
                        assert_equal(type(point.id.cf), "table")
                        assert_equal(type(point.id.key), "number")
                    end
                end
            end)

            w:Destroy()
        end)
        test("GetWorldManifold()", function()
            local w = box2d.NewWorld()
            ---@param contact Box2dContact
            testContact(w, function(name, contact)
                if (name == "BeginContact") then
                    local manifold = contact:GetWorldManifold()
                    assert_equal(type(manifold), "table")
                    assert_equal_v3(manifold.normal, vmath.vector3(1, 0, 0))
                    assert_equal(#manifold.points, 2)
                    assert_equal(#manifold.separations, 2)
                    assert_equal(#manifold.separations, #manifold.points)

                    assert_equal_v3(manifold.points[1], vmath.vector3(0.5, 0, 0))
                    assert_equal_v3(manifold.points[2], vmath.vector3(0.5, 1.0199999809265, 0))

                    assert_equal_float(manifold.separations[1], -1.0199999809265)
                    assert_equal_float(manifold.separations[2], -1.0199999809265)

                end
            end)
            w:Destroy()
        end)


    end)
end
