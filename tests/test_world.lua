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
            assert_equal(value , "World already destroyed")
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
            assert_equal(value , "World already destroyed")


            status, value = pcall(f2)
            assert_false(status)
            assert_equal(value , "World already destroyed")
        end)

        test("newIndex", function()
            local w = box2d.NewWorld()
            local f = function () w.data = {} end
            local status,value = pcall(f)
            assert_false(status)
            assert_equal(value,"world can't set new fields")
            w:Destroy()
        end)

        test("tostring", function()
            local w = box2d.NewWorld()
            local s = tostring(w)
            assert_equal(s:sub(1,8),"b2World[")
            w:Destroy()
        end)

        test("equals", function()
            local w = box2d.NewWorld()
            local w2 = box2d.NewWorld()

            assert_equal(w,w)
            assert_not_equal(w,w2)
            assert_not_equal(w,1)
            assert_not_equal(w, {})


            local b = w:CreateBody({})

            assert_equal(w,b:GetWorld())

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

        -- test("CreateBody()", function() end) -- body tests
        -- test("DestroyBody()", function() end)-- body tests
        -- test("CreateJoint()", function() end) -- jointDef tests
        -- test("DestroyBJoint()", function() end)-- joint tests


        test("Step()", function()
            local w = box2d.NewWorld()
            UTILS.test_method(w, "Step", {
                args = {1/60,2,4}
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

        test("GetBodyList()", function()
            local w = box2d.NewWorld()
            assert_nil(w:GetBodyList())
            local body_1 = w:CreateBody()
            local body_2 = w:CreateBody()
            assert_equal(w:GetBodyList(),body_2)
            w:Destroy()
        end)

        test("GetJointList()", function()
            local w = box2d.NewWorld()
            assert_nil(w:GetJointList())
            local body_1 = w:CreateBody()
            local body_2 = w:CreateBody()
            local joint1 = w:CreateJoint({type = box2d.b2JointType.e_revoluteJoint,bodyA = body_1, bodyB =  body_2})
            assert_equal(w:GetJointList(),joint1)
            w:Destroy()
        end)

        test("Set/Get AllowSleeping()", function()
            local w = box2d.NewWorld()
            UTILS.test_method_get_set(w, "AllowSleeping", {
                values = { true,false }
            })
            w:Destroy()
        end)

        test("Set/Get WarmStarting()", function()
            local w = box2d.NewWorld()
            UTILS.test_method_get_set(w, "WarmStarting", {
                values = { true,false }
            })
            w:Destroy()
        end)

        test("Set/Get ContinuousPhysics()", function()
            local w = box2d.NewWorld()
            UTILS.test_method_get_set(w, "ContinuousPhysics", {
                values = { true,false }
            })
            w:Destroy()
        end)

        test("Set/Get SubStepping()", function()
            local w = box2d.NewWorld()
            UTILS.test_method_get_set(w, "SubStepping", {
                values = { true,false }
            })
            w:Destroy()
        end)

        test("GetProxyCount()",function ()
            local w = box2d.NewWorld()
            UTILS.test_method(w, "GetProxyCount", {
                result = 0
            })
            w:Destroy()
        end)

        test("GetBodyCount()",function ()
            local w = box2d.NewWorld()
            UTILS.test_method(w, "GetBodyCount", {
                result = 0
            })
            w:Destroy()
        end)

        test("GetJointCount()",function ()
            local w = box2d.NewWorld()
            UTILS.test_method(w, "GetJointCount", {
                result = 0
            })
            w:Destroy()
        end)

        test("GetContactCount()",function ()
            local w = box2d.NewWorld()
            UTILS.test_method(w, "GetContactCount", {
                result = 0
            })
            w:Destroy()
        end)

        test("GetTreeHeight()",function ()
            local w = box2d.NewWorld()
            UTILS.test_method(w, "GetTreeHeight", {
                result = 0
            })
            w:Destroy()
        end)

        test("GetTreeBalance()",function ()
            local w = box2d.NewWorld()
            UTILS.test_method(w, "GetTreeBalance", {
                result = 0
            })
            w:Destroy()
        end)

        test("GetTreeQuality()",function ()
            local w = box2d.NewWorld()
            UTILS.test_method(w, "GetTreeQuality", {
                result = 0
            })
            w:Destroy()
        end)

        test("Set/Get Gravity()", function()
            local w = box2d.NewWorld()
            UTILS.test_method_get_set(w, "Gravity", {
                v3 = true,default = vmath.vector3(0,0,0),
                values = {  vmath.vector3(-1,0,0), vmath.vector3(10,0,0), vmath.vector3(0,0,0) }
            })
            w:Destroy()
        end)

        test("IsLocked()",function ()
            local w = box2d.NewWorld()
            UTILS.test_method(w, "IsLocked", {
                result = false
            })
            w:Destroy()
        end)

        test("Set/Get AutoClearForces()", function()
            local w = box2d.NewWorld()
            UTILS.test_method_get_set(w, "AutoClearForces", {
                values = {  false,true }
            })
            w:Destroy()
        end)

        test("ShiftOrigin()", function()
            local w = box2d.NewWorld()
            UTILS.test_method(w, "ShiftOrigin", {args = {vmath.vector3(10,10,0)}})
            w:Destroy()
        end)

        test("Dump()", function()
            local w = box2d.NewWorld()
            UTILS.test_method(w, "Dump", {})
            w:Destroy()
        end)

    end)
end
