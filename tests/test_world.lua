local UTILS = require "tests.test_utils"

return function()
    describe("World", function()
        before(function()
            UTILS.set_env(getfenv(1))
        end)
        after(function() end)

        test("create", function()
            local w = box2d.NewWorld()
            assert_not_nil(w)
            assert_not_nil(w.__userdata_world)
            w:Destroy()
        end)

        test("destroy", function()
            local w = box2d.NewWorld()
            w:Destroy()
            local f = function() return w:GetProfile() end
            local status, value = pcall(f)
            assert_false(status)
            assert_equal(value, "World already destroyed")
        end)

        test("destroy all refs", function()
            local w = box2d.NewWorld()
            local body = w:CreateBody({})
            local w2 = body:GetWorld()

            w:Destroy()
            local f = function() return w:GetProfile() end
            local f2 = function() return w2:GetProfile() end

            local status, value = pcall(f)
            assert_false(status)
            assert_equal(value, "World already destroyed")

            status, value = pcall(f2)
            assert_false(status)
            assert_equal(value, "World already destroyed")
        end)

        test("newIndex", function()
            local w = box2d.NewWorld()
            local f = function() w.data = {} end
            local status, value = pcall(f)
            assert_false(status)
            assert_equal(value, "world can't set new fields")
            w:Destroy()
        end)

        test("tostring", function()
            local w = box2d.NewWorld()
            local s = tostring(w)
            assert_equal(s:sub(1, 8), "b2World[")
            w:Destroy()
        end)

        test("equals", function()
            local w = box2d.NewWorld()
            local w2 = box2d.NewWorld()

            assert_equal(w, w)
            assert_not_equal(w, w2)
            assert_not_equal(w, 1)
            assert_not_equal(w, {})

            local b = w:CreateBody({})

            assert_equal(w, b:GetWorld())

            w:Destroy()
            w2:Destroy()
        end)

        test("GetProfile()", function()
            local w = box2d.NewWorld()
            local profile = w:GetProfile()
            assert_not_nil(profile.step)
            assert_not_nil(profile.collide)
            assert_not_nil(profile.solve)
            assert_not_nil(profile.solveInit)
            assert_not_nil(profile.solveVelocity)
            assert_not_nil(profile.solvePosition)
            assert_not_nil(profile.broadphase)
            assert_not_nil(profile.solveTOI)
            w:Destroy()
        end)

        test("SetContactListener()", function()
            local w = box2d.NewWorld()
            w:Step(1 / 60, 3, 5)
            w:SetContactListener(nil)
            w:Step(1 / 60, 3, 5)
            w:SetContactListener({ })
            w:Step(1 / 60, 3, 5)

            local contacts = {
                BeginContact = {},
                EndContact = {},
                PreSolve = {},
                PostSolve = {},
            }
            w:SetContactListener({
                BeginContact = function(contact)
                    assert_not_nil(contact)
                    assert_not_nil(contact.__userdata_contact)
                    table.insert(contacts.BeginContact, true)
                end,
                EndContact = function(contact)
                    assert_not_nil(contact)
                    assert_not_nil(contact.__userdata_contact)
                    table.insert(contacts.EndContact, true)
                end,
                PreSolve = function(contact, old_manifold)
                    assert_not_nil(contact)
                    assert_not_nil(contact.__userdata_contact)
                    table.insert(contacts.PreSolve, true)
                end,
                PostSolve = function(contact, impulse)
                    assert_not_nil(contact)
                    assert_not_nil(contact.__userdata_contact)
                    table.insert(contacts.PostSolve, true)
                end,
            })
            w:Step(1 / 60, 3, 5)
            assert_equal(#contacts.BeginContact, 0)
            assert_equal(#contacts.EndContact, 0)
            assert_equal(#contacts.PreSolve, 0)
            assert_equal(#contacts.PostSolve, 0)

            local b1 = w:CreateBody({ type = box2d.b2BodyType.b2_dynamicBody, position = vmath.vector3(0, 0, 0) })
            local b2 = w:CreateBody({ type = box2d.b2BodyType.b2_dynamicBody, position = vmath.vector3(1, 1, 0) })

            b1:CreateFixture({ shape = box2d.b2Shape.e_polygon, box = true, box_hy = 1, box_hx = 1 }, 1)
            b2:CreateFixture({ shape = box2d.b2Shape.e_polygon, box = true, box_hy = 1, box_hx = 1 }, 1)

            w:Step(1 / 60, 3, 5)

            assert_equal(#contacts.BeginContact, 1)
            assert_equal(#contacts.EndContact, 0)
            assert_equal(#contacts.PreSolve, 1)
            assert_equal(#contacts.PostSolve, 1)

            w:SetContactListener({ PreSolve = function()
                error("error")
            end })
            local status, value = pcall(w.Step, w, 1 / 60, 3, 5)
            assert_false(status)
            pprint("ERROR")
            pprint(value)
            UTILS.test_error(value,"error")

            w:SetContactListener({ PreSolve = function()

            end })
            w:Step(1 / 60, 3, 5)
            w:Step(1 / 60, 3, 5)
            w:Step(1 / 60, 3, 5)
            w:Step(1 / 60, 3, 5)
            w:Step(1 / 60, 3, 5)

            w:Destroy()
        end)

        test("SetContactListener() REUSE", function()
            local w = box2d.NewWorld()
            local c
            w:SetContactListener({
                BeginContact = function(contact)
                    c = c or contact
                    assert_equal(c,contact)
                end,
                EndContact = function(contact)
                    c = c or contact
                    assert_equal(c,contact)
                end,
                PreSolve = function(contact, old_manifold)
                    c = c or contact
                    assert_equal(c,contact)
                end,
                PostSolve = function(contact, impulse)
                    c = c or contact
                    assert_equal(c,contact)
                end,
            })

            local b1 = w:CreateBody({ type = box2d.b2BodyType.b2_dynamicBody, position = vmath.vector3(0, 0, 0) })
            local b2 = w:CreateBody({ type = box2d.b2BodyType.b2_dynamicBody, position = vmath.vector3(0, 1, 0) })
            local b3 = w:CreateBody({ type = box2d.b2BodyType.b2_dynamicBody, position = vmath.vector3(1, 0, 0) })
            local b4 = w:CreateBody({ type = box2d.b2BodyType.b2_dynamicBody, position = vmath.vector3(1, 1, 0) })

            b1:CreateFixture({ shape = box2d.b2Shape.e_polygon, box = true, box_hy = 1, box_hx = 1 }, 1)
            b2:CreateFixture({ shape = box2d.b2Shape.e_polygon, box = true, box_hy = 1, box_hx = 1 }, 1)
            b3:CreateFixture({ shape = box2d.b2Shape.e_polygon, box = true, box_hy = 1, box_hx = 1 }, 1)
            b4:CreateFixture({ shape = box2d.b2Shape.e_polygon, box = true, box_hy = 1, box_hx = 1 }, 1)

            w:Step(1 / 60, 3, 5)


            assert_not_nil(c)
            assert_nil(c.__userdata_contact)
            local status,value = pcall(tostring,c)
            assert_false(status)
            assert_equal(value,"Contact already destroyed")

            w:Destroy()
        end)

        -- test("CreateBody()", function() end) -- body tests
        -- test("DestroyBody()", function() end)-- body tests
        -- test("CreateJoint()", function() end) -- jointDef tests
        -- test("DestroyBJoint()", function() end)-- joint tests


        test("Step()", function()
            local w = box2d.NewWorld()
            UTILS.test_method(w, "Step", {
                args = { 1 / 60, 2, 4 }
            })
            w:Destroy()
        end)

        test("ClearForces()", function()
            local w = box2d.NewWorld()
            UTILS.test_method(w, "ClearForces", {})
            w:Destroy()
        end)

        test("DebugDraw()", function()
            local w = box2d.NewWorld()
            UTILS.test_method(w, "DebugDraw", {})
            w:Destroy()
        end)

        test("RayCast()", function()
            local w = box2d.NewWorld()

            local body_1 = w:CreateBody({ position = vmath.vector3(5, 0, 0) })
            local body_2 = w:CreateBody({ position = vmath.vector3(10, 0, 0) })
            local body_3 = w:CreateBody({ position = vmath.vector3(15, 0, 0) })

            body_1:CreateFixture({ shape = box2d.b2Shape.e_polygon, box = true, box_hy = 1, box_hx = 1 }, 1)
            body_2:CreateFixture({ shape = box2d.b2Shape.e_polygon, box = true, box_hy = 1, box_hx = 1 }, 1)
            body_3:CreateFixture({ shape = box2d.b2Shape.e_polygon, box = true, box_hy = 1, box_hx = 1 }, 1)

            local cb_results = {}
            local cb_closest = function(fixture, point, normal, fraction)
                assert_equal(type(fixture), "table")
                assert_equal(type(point), "userdata")
                assert_equal(type(normal), "userdata")
                assert_equal(type(fraction), "number")
                table.insert(cb_results, { fixture = fixture, point = point, normal = normal, fraction = fraction })
                return fraction
            end

            local cb_all = function(fixture, point, normal, fraction)
                table.insert(cb_results, { fixture = fixture, point = point, normal = normal, fraction = fraction })
                return 1
            end

            local cb_any = function(fixture, point, normal, fraction)
                table.insert(cb_results, { fixture = fixture, point = point, normal = normal, fraction = fraction })
                return 0
            end

            local p1 = vmath.vector3(0, 0, 0)
            local point_no = vmath.vector3(0, 10, 0)
            local point_one = vmath.vector3(5, 0, 0)
            local point_all = vmath.vector3(15, 0, 0)

            --*** NO ***
            w:RayCast(cb_closest, p1, point_no)
            assert_equal(#cb_results, 0)
            w:RayCast(cb_all, p1, point_no)
            assert_equal(#cb_results, 0)
            w:RayCast(cb_any, p1, point_no)
            assert_equal(#cb_results, 0)

            --*** ONE ***
            w:RayCast(cb_closest, p1, point_one)
            assert_equal(#cb_results, 1)
            assert_equal(cb_results[1].fixture:GetBody(), body_1)
            cb_results = {}
            w:RayCast(cb_all, p1, point_one)
            assert_equal(#cb_results, 1)
            cb_results = {}
            w:RayCast(cb_any, p1, point_one)
            assert_equal(#cb_results, 1)
            cb_results = {}

            --*** ALL ***
            w:RayCast(cb_closest, p1, point_all)
            assert_equal(cb_results[#cb_results].fixture:GetBody(), body_1)
            cb_results = {}
            w:RayCast(cb_all, p1, point_all)
            assert_equal(#cb_results, 3)
            cb_results = {}
            w:RayCast(cb_any, p1, point_all)
            assert_equal(#cb_results, 1)
            cb_results = {}

            local cb_error = function() error("error happened") end
            local status, error = pcall(w.RayCast, w, cb_error, p1, point_all)
            assert_false(status)
            --remove line number
            UTILS.test_error(error,"error happened")

            w:Destroy()
        end)

        test("QueryAABB()", function()
            local w = box2d.NewWorld()

            local body_1 = w:CreateBody({ position = vmath.vector3(5, 0, 0) })
            local body_2 = w:CreateBody({ position = vmath.vector3(10, 0, 0) })
            local body_3 = w:CreateBody({ position = vmath.vector3(15, 0, 0) })

            body_1:CreateFixture({ shape = box2d.b2Shape.e_polygon, box = true, box_hy = 1, box_hx = 1 }, 1)
            body_2:CreateFixture({ shape = box2d.b2Shape.e_polygon, box = true, box_hy = 1, box_hx = 1 }, 1)
            body_3:CreateFixture({ shape = box2d.b2Shape.e_polygon, box = true, box_hy = 1, box_hx = 1 }, 1)

            local cb_results = {}
            local cb_all = function(fixture)
                table.insert(cb_results, { fixture = fixture })
                return true;
            end

            local cb_one = function(fixture)
                table.insert(cb_results, { fixture = fixture })
                return false;
            end

            local aabb_no = { lowerBound = vmath.vector3(-10, 0, 0), upperBound = vmath.vector3(-0.6, 0.1, 0) }
            local aabb_one = { lowerBound = vmath.vector3(0, 0, 0), upperBound = vmath.vector3(5, 0.5, 0) }
            local aabb_all = { lowerBound = vmath.vector3(0, 0, 0), upperBound = vmath.vector3(15, 0.5, 0) }

            --*** NO ***
            w:QueryAABB(cb_all, aabb_no)
            assert_equal(#cb_results, 0)
            w:QueryAABB(cb_one, aabb_no)
            assert_equal(#cb_results, 0)

            --*** ONE ***
            w:QueryAABB(cb_all, aabb_one)
            assert_equal(#cb_results, 1)
            assert_equal(cb_results[1].fixture:GetBody(), body_1)
            cb_results = {}
            w:QueryAABB(cb_one, aabb_one)
            assert_equal(#cb_results, 1)
            assert_equal(cb_results[1].fixture:GetBody(), body_1)
            cb_results = {}


            --*** ALL ***
            w:QueryAABB(cb_all, aabb_all)
            assert_equal(#cb_results, 3)
            cb_results = {}
            w:QueryAABB(cb_one, aabb_all)
            assert_equal(#cb_results, 1)
            cb_results = {}

            local cb_error = function() error("error happened") end
            local status, error = pcall(w.QueryAABB, w, cb_error, aabb_all)
            assert_false(status)
            --remove line number
            UTILS.test_error(error,"error happened")

            w:Destroy()
        end)

        test("GetBodyList()", function()
            local w = box2d.NewWorld()
            assert_nil(w:GetBodyList())
            local body_1 = w:CreateBody()
            local body_2 = w:CreateBody()
            assert_equal(w:GetBodyList(), body_2)
            w:Destroy()
        end)

        test("GetJointList()", function()
            local w = box2d.NewWorld()
            assert_nil(w:GetJointList())
            local body_1 = w:CreateBody()
            local body_2 = w:CreateBody()
            local joint1 = w:CreateJoint({ type = box2d.b2JointType.e_revoluteJoint, bodyA = body_1, bodyB = body_2 })
            assert_equal(w:GetJointList(), joint1)
            w:Destroy()
        end)

        test("Set/Get AllowSleeping()", function()
            local w = box2d.NewWorld()
            UTILS.test_method_get_set(w, "AllowSleeping", {
                values = { true, false }
            })
            w:Destroy()
        end)

        test("Set/Get WarmStarting()", function()
            local w = box2d.NewWorld()
            UTILS.test_method_get_set(w, "WarmStarting", {
                values = { true, false }
            })
            w:Destroy()
        end)

        test("Set/Get ContinuousPhysics()", function()
            local w = box2d.NewWorld()
            UTILS.test_method_get_set(w, "ContinuousPhysics", {
                values = { true, false }
            })
            w:Destroy()
        end)

        test("Set/Get SubStepping()", function()
            local w = box2d.NewWorld()
            UTILS.test_method_get_set(w, "SubStepping", {
                values = { true, false }
            })
            w:Destroy()
        end)

        test("GetProxyCount()", function()
            local w = box2d.NewWorld()
            UTILS.test_method(w, "GetProxyCount", {
                result = 0
            })
            w:Destroy()
        end)

        test("GetBodyCount()", function()
            local w = box2d.NewWorld()
            UTILS.test_method(w, "GetBodyCount", {
                result = 0
            })
            w:Destroy()
        end)

        test("GetJointCount()", function()
            local w = box2d.NewWorld()
            UTILS.test_method(w, "GetJointCount", {
                result = 0
            })
            w:Destroy()
        end)

        test("GetContactCount()", function()
            local w = box2d.NewWorld()
            UTILS.test_method(w, "GetContactCount", {
                result = 0
            })
            w:Destroy()
        end)

        test("GetTreeHeight()", function()
            local w = box2d.NewWorld()
            UTILS.test_method(w, "GetTreeHeight", {
                result = 0
            })
            w:Destroy()
        end)

        test("GetTreeBalance()", function()
            local w = box2d.NewWorld()
            UTILS.test_method(w, "GetTreeBalance", {
                result = 0
            })
            w:Destroy()
        end)

        test("GetTreeQuality()", function()
            local w = box2d.NewWorld()
            UTILS.test_method(w, "GetTreeQuality", {
                result = 0
            })
            w:Destroy()
        end)

        test("Set/Get Gravity()", function()
            local w = box2d.NewWorld()
            UTILS.test_method_get_set(w, "Gravity", {
                v3 = true, default = vmath.vector3(0, 0, 0),
                values = { vmath.vector3(-1, 0, 0), vmath.vector3(10, 0, 0), vmath.vector3(0, 0, 0) }
            })
            w:Destroy()
        end)

        test("IsLocked()", function()
            local w = box2d.NewWorld()
            UTILS.test_method(w, "IsLocked", {
                result = false
            })
            w:Destroy()
        end)

        test("Set/Get AutoClearForces()", function()
            local w = box2d.NewWorld()
            UTILS.test_method_get_set(w, "AutoClearForces", {
                values = { false, true }
            })
            w:Destroy()
        end)

        test("ShiftOrigin()", function()
            local w = box2d.NewWorld()
            UTILS.test_method(w, "ShiftOrigin", { args = { vmath.vector3(10, 10, 0) } })
            w:Destroy()
        end)

        test("Dump()", function()
            local w = box2d.NewWorld()
            UTILS.test_method(w, "Dump", {})
            w:Destroy()
        end)

    end)
end
