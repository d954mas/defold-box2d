local UTILS = require "tests.test_utils"
local LUME = require "libs.lume"

---@param w Box2dWorld
local create_body = function(w, body_def)
    local b = w:CreateBody(body_def)
    return b
end

return function()
    describe("Body", function()
        before(function()
            UTILS.set_env(getfenv(1))
        end)
        after(function() end)

        test("create", function()
            local w = box2d.NewWorld()
            local body = create_body(w)
            assert_not_nil(body)
            assert_not_nil(body.__userdata_body)
            w:Destroy()
        end)

        test("create no args", function()
            local w = box2d.NewWorld()
            local body = create_body(w)
            assert_not_nil(body)
            assert_not_nil(body.__userdata_body)
            w:Destroy()
        end)

        test("Equals", function()
            local world = box2d.NewWorld()
            local body_1 = world:CreateBody({})
            local body_2 = world:CreateBody({})

            assert_equal(body_1, body_1)
            assert_not_equal(body_1, body_2)
            assert_not_equal(body_1, 1)

            local body_1_next_nil = body_1:GetNext()
            local body_2_next_1 = body_2:GetNext()
            assert_nil(body_1_next_nil)

            assert_equal(body_1, body_2_next_1)

            world:Destroy()
        end)

        test("world:DestroyBody()", function()
            local w = box2d.NewWorld()
            local def = {}
            local b = w:CreateBody(def)

            w:DestroyBody(b)

            local f = function() return b:GetLinearVelocity() end
            local status, value = pcall(f)
            assert_false(status)
            assert_equal(value, "Body already destroyed")

            w:Destroy()
        end)

        test("destroy body after world destroyed", function()
            local w = box2d.NewWorld()
            local body = create_body(w)
            w:Destroy()

            local f = function() return body:GetLinearVelocity() end
            local status, value = pcall(f)
            assert_false(status)
            assert_equal(value, "Body already destroyed")
        end)




        test("Set/Get Transform()", function()
            local w = box2d.NewWorld()
            local body = create_body(w)
            local pos, angle = body:GetTransform()
            assert_equal_v3(pos, vmath.vector3(0, 0, 0))
            assert_equal_float(angle, 0)

            body:SetTransform(vmath.vector3(10, 10, 0), math.pi / 2)
            pos, angle = body:GetTransform()

            assert_equal_v3(pos, vmath.vector3(10, 10, 0))
            assert_equal_float(angle, math.pi / 2)

            w:Destroy()
        end)

        test("Set Transform no angle", function()
            local w = box2d.NewWorld()
            local body = create_body(w)
            local pos, angle = body:GetTransform()
            assert_equal_v3(pos, vmath.vector3(0, 0, 0))
            assert_equal_float(angle, 0)

            body:SetTransform(vmath.vector3(-10, -10, 0), math.pi / 2)
            pos, angle = body:GetTransform()

            assert_equal_v3(pos, vmath.vector3(-10, -10, 0))
            assert_equal_float(angle, math.pi / 2)

            body:SetTransform(vmath.vector3(4, 4, 0))
            pos, angle = body:GetTransform()

            assert_equal_v3(pos, vmath.vector3(4, 4, 0))
            assert_equal_float(angle, math.pi / 2)

            body:SetTransform(vmath.vector3(6, 6, 0), nil)
            pos, angle = body:GetTransform()

            assert_equal_v3(pos, vmath.vector3(6, 6, 0))
            assert_equal_float(angle, math.pi / 2)

            w:Destroy()
        end)

        test("GetPosition()", function()
            local w = box2d.NewWorld()
            local body = create_body(w)
            assert_equal_v3(body:GetPosition(), vmath.vector3(0, 0, 0))
            body:SetTransform(vmath.vector3(10, 10, 0), math.pi / 2)
            assert_equal_v3(body:GetPosition(), vmath.vector3(10, 10, 0))
            w:Destroy()
        end)

        test("GetAngle()", function()
            local w = box2d.NewWorld()
            local body = create_body(w)
            assert_equal_float(body:GetAngle(), 0)
            body:SetTransform(vmath.vector3(10, 10, 0), math.pi / 2)
            assert_equal_float(body:GetAngle(), math.pi / 2)
            w:Destroy()
        end)

        test("GetWorldCenter()", function()
            local w = box2d.NewWorld()
            local body = create_body(w)
            assert_equal_v3(body:GetWorldCenter(), vmath.vector3(0, 0, 0))
            body:SetTransform(vmath.vector3(10, 10, 0), math.pi / 2)
            assert_equal_v3(body:GetWorldCenter(), vmath.vector3(10, 10, 0))
            w:Destroy()
        end)

        test("GetLocalCenter()", function()
            local w = box2d.NewWorld()
            local body = create_body(w)
            assert_equal_v3(body:GetLocalCenter(), vmath.vector3(0, 0, 0))
            body:SetTransform(vmath.vector3(10, 10, 0), math.pi / 2)
            assert_equal_v3(body:GetLocalCenter(), vmath.vector3(0, 0, 0))
            w:Destroy()
        end)

        test("Set/Get LinearVelocity()", function()
            local w = box2d.NewWorld()
            local body = create_body(w, { type = box2d.b2BodyType.b2_dynamicBody })
            UTILS.test_method_get_set(body, "LinearVelocity",
                    {
                        v3 = true, default = vmath.vector3(0, 0, 0),
                        values = { vmath.vector3(10, 10, 0), vmath.vector3(-3, 5, 0) }
                    })
            w:Destroy()
        end)

        test("Set/Get AngularVelocity()", function()
            local w = box2d.NewWorld()
            local body = create_body(w, { type = box2d.b2BodyType.b2_dynamicBody })
            UTILS.test_method_get_set(body, "AngularVelocity",
                    {
                        float = true, default = 0,
                        values = { -10, 2 }
                    })
            w:Destroy()
        end)

        test("ApplyForce()", function()
            local w = box2d.NewWorld()
            local body = create_body(w, { type = box2d.b2BodyType.b2_dynamicBody })
            assert_equal_v3(body:GetLinearVelocity(), vmath.vector3(0, 0, 0))
            body:ApplyForce(vmath.vector3(50, 0, 0), vmath.vector3(0, 0, 0), true)
            w:Destroy()
        end)

        test("ApplyForceToCenter()", function()
            local w = box2d.NewWorld()
            local body = create_body(w, { type = box2d.b2BodyType.b2_dynamicBody })
            assert_equal_v3(body:GetLinearVelocity(), vmath.vector3(0, 0, 0))
            body:ApplyForceToCenter(vmath.vector3(50, 0, 0), true)
            w:Destroy()
        end)

        test("ApplyTorque()", function()
            local w = box2d.NewWorld()
            local body = create_body(w, { type = box2d.b2BodyType.b2_dynamicBody })
            assert_equal_float(body:GetAngularVelocity(), 0)
            body:ApplyTorque(10, true)
            w:Destroy()
        end)

        test("ApplyLinearImpulse()", function()
            local w = box2d.NewWorld()
            local body = create_body(w, { type = box2d.b2BodyType.b2_dynamicBody })
            assert_equal_v3(body:GetLinearVelocity(), vmath.vector3(0, 0, 0))
            body:ApplyLinearImpulse(vmath.vector3(10, 10, 0), vmath.vector3(0, 0, 0), true)
            w:Destroy()
        end)

        test("ApplyLinearImpulseToCenter()", function()
            local w = box2d.NewWorld()
            local body = create_body(w, { type = box2d.b2BodyType.b2_dynamicBody })
            assert_equal_v3(body:GetLinearVelocity(), vmath.vector3(0, 0, 0))
            body:ApplyLinearImpulseToCenter(vmath.vector3(10, 10, 0), true)
            w:Destroy()
        end)

        test("ApplyAngularImpulse()", function()
            local w = box2d.NewWorld()
            local body = create_body(w, { type = box2d.b2BodyType.b2_dynamicBody })
            assert_equal_float(body:GetAngularVelocity(), 0)
            body:ApplyAngularImpulse(10, true)
            w:Destroy()
        end)

        test("GetMass()", function()
            local w = box2d.NewWorld()
            local body = create_body(w, { type = box2d.b2BodyType.b2_dynamicBody })
            assert_equal_float(body:GetMass(), 0)
            w:Destroy()
        end)

        test("GetInertia()", function()
            local w = box2d.NewWorld()
            local body = create_body(w, { type = box2d.b2BodyType.b2_dynamicBody })
            assert_equal_float(body:GetInertia(), 0)
            w:Destroy()
        end)

        test("ResetMassData()", function()
            local w = box2d.NewWorld()
            local body = create_body(w, { type = box2d.b2BodyType.b2_dynamicBody })
            body:SetMassData({ I = 20, mass = 1, center = { x = 1, y = 1 } })
            local mass_data = body:GetMassData()
            assert_equal(mass_data.mass, 1)
            assert_equal(mass_data.I, 20)
            assert_equal(mass_data.center.x, 1)
            assert_equal(mass_data.center.y, 1)

            body:ResetMassData()

            mass_data = body:GetMassData()
            assert_equal(mass_data.mass, 0)
            assert_equal(mass_data.I, 0)
            assert_equal(mass_data.center.x, 0)
            assert_equal(mass_data.center.y, 0)

            w:Destroy()
        end)

        test("GetMassData()", function()
            local w = box2d.NewWorld()
            local body = create_body(w, { type = box2d.b2BodyType.b2_dynamicBody })
            local mass_data = body:GetMassData()
            --[[
            {
                mass = 0,
                center = {y = 0, x = 0},
                I = 0
            }
            --]]
            assert_equal(mass_data.mass, 0)
            assert_equal(mass_data.I, 0)
            assert_equal(mass_data.center.x, 0)
            assert_equal(mass_data.center.y, 0)

            w:Destroy()
        end)

        test("SetMassData()", function()
            local w = box2d.NewWorld()
            local body = create_body(w, { type = box2d.b2BodyType.b2_dynamicBody })
            body:SetMassData({ I = 20, mass = 1, center = { x = 1, y = 1 } })
            local mass_data = body:GetMassData()
            assert_equal(mass_data.mass, 1)
            assert_equal(mass_data.I, 20)
            assert_equal(mass_data.center.x, 1)
            assert_equal(mass_data.center.y, 1)
            w:Destroy()
        end)

        test("GetWorldPoint()", function()
            local w = box2d.NewWorld()
            local body = create_body(w)
            assert_equal_v3(body:GetWorldPoint(vmath.vector3(2, 2, 0)), vmath.vector3(2, 2, 0))
            body:SetTransform(vmath.vector3(10, 10, 0))
            assert_equal_v3(body:GetWorldPoint(vmath.vector3(-2, -2, 0)), vmath.vector3(8, 8, 0))
            w:Destroy()
        end)

        test("GetWorldVector()", function()
            local w = box2d.NewWorld()
            local body = create_body(w)
            assert_equal_v3(body:GetWorldVector(vmath.vector3(1, 1, 0)), vmath.vector3(1, 1, 0))
            w:Destroy()
        end)

        test("GetLocalPoint()", function()
            local w = box2d.NewWorld()
            local body = create_body(w)
            assert_equal_v3(body:GetLocalPoint(vmath.vector3(2, 2, 0)), vmath.vector3(2, 2, 0))
            body:SetTransform(vmath.vector3(10, 10, 0))
            assert_equal_v3(body:GetLocalPoint(vmath.vector3(-2, -2, 0)), vmath.vector3(-12, -12, 0))
            w:Destroy()
        end)

        test("GetLocalVector()", function()
            local w = box2d.NewWorld()
            local body = create_body(w)
            assert_equal_v3(body:GetLocalVector(vmath.vector3(1, 1, 0)), vmath.vector3(1, 1, 0))
            w:Destroy()
        end)

        test("GetLinearVelocityFromWorldPoint()", function()
            local w = box2d.NewWorld()
            local body = create_body(w)
            assert_equal_v3(body:GetLinearVelocityFromWorldPoint(vmath.vector3(0, 0, 0)), vmath.vector3(0, 0, 0))
            w:Destroy()
        end)

        test("GetLinearVelocityFromLocalPoint()", function()
            local w = box2d.NewWorld()
            local body = create_body(w)
            assert_equal_v3(body:GetLinearVelocityFromLocalPoint(vmath.vector3(0, 0, 0)), vmath.vector3(0, 0, 0))
            w:Destroy()
        end)

        test("Set/Get LinearDamping()", function()
            local w = box2d.NewWorld()
            local body = create_body(w)
            UTILS.test_method_get_set(body, "LinearDamping",
                    {
                        float = true, default = 0,
                        values = { 0.5, 1 }
                    })
            w:Destroy()
        end)

        test("Set/Get AngularDamping()", function()
            local w = box2d.NewWorld()
            local body = create_body(w)
            UTILS.test_method_get_set(body, "AngularDamping",
                    {
                        float = true, default = 0,
                        values = { 0.5, 1 }
                    })
            w:Destroy()
        end)

        test("Set/Get GravityScale()", function()
            local w = box2d.NewWorld()
            local body = create_body(w)
            UTILS.test_method_get_set(body, "GravityScale",
                    {
                        float = true, default = 1,
                        values = { 0.5, 1 }
                    })
            w:Destroy()
        end)

        test("Set/Get Type()", function()
            local w = box2d.NewWorld()
            local body = create_body(w)
            UTILS.test_method_get_set(body, "Type",
                    {
                        default = 0, values = { box2d.b2BodyType.b2_kinematicBody, box2d.b2BodyType.b2_dynamicBody,
                                                box2d.b2BodyType.b2_staticBody }
                    })
            w:Destroy()
        end)

        test("Set/Is Bullet()", function()
            local w = box2d.NewWorld()
            local body = create_body(w)
            UTILS.test_method_get_set(body, "Bullet",
                    {
                        getter = "Is",
                        values = { true, false, true }
                    })
            w:Destroy()
        end)

        test("Set/Is SleepingAllowed()", function()
            local w = box2d.NewWorld()
            local body = create_body(w)
            UTILS.test_method_get_set(body, "SleepingAllowed",
                    {
                        getter = "Is",
                        values = { true, false, true }
                    })
            w:Destroy()
        end)

        test("Set/Is Awake()", function()
            local w = box2d.NewWorld()
            local body = create_body(w, { type = box2d.b2BodyType.b2_dynamicBody })
            UTILS.test_method_get_set(body, "Awake",
                    {
                        getter = "Is",
                        values = { true, false, true }
                    })
            w:Destroy()
        end)

        test("Set/Is Enabled()", function()
            local w = box2d.NewWorld()
            local body = create_body(w)
            UTILS.test_method_get_set(body, "Enabled",
                    {
                        getter = "Is",
                        values = { true, false, true }
                    })
            w:Destroy()
        end)

        test("Set/Is FixedRotation()", function()
            local w = box2d.NewWorld()
            local body = create_body(w)
            UTILS.test_method_get_set(body, "Enabled",
                    {
                        getter = "Is",
                        values = { true, false, true }
                    })
            w:Destroy()
        end)

        test("getNext()", function()
            local world = box2d.NewWorld()
            local body_1 = world:CreateBody({})
            local body_2 = world:CreateBody({})

            local body_1_next = body_1:GetNext()
            local body_2_next = body_2:GetNext()

            assert_nil(body_1_next)
            assert_equal(body_2_next, body_1)



            world:Destroy()
        end)

        test("GetFixtureList()", function()
            local world = box2d.NewWorld()
            local body = world:CreateBody({})
            assert_nil(body:GetFixtureList())
            local fixture = body:CreateFixture({shape = {shape = box2d.b2Shape.e_circle,circle_position = vmath.vector3(0,0,0),circle_radius = 1}})
            assert_equal(fixture,body:GetFixtureList())
            local fixture2 = body:CreateFixture({shape = {shape = box2d.b2Shape.e_circle,circle_position = vmath.vector3(0,0,0),circle_radius = 1}})
            assert_equal(fixture2,body:GetFixtureList())

            world:Destroy()
        end)

        test("Set/Get UserData()", function()
            local world = box2d.NewWorld()
            local body = world:CreateBody()

            assert_nil(body:GetUserData())


            local userdata = {}
            body:SetUserData(userdata)
            assert_equal(body:GetUserData(), userdata)

            world:Destroy()
        end)

        test("GetWorld()", function()
            local world = box2d.NewWorld()
            local body = world:CreateBody()

            local body_world = body:GetWorld()
            assert_equal(body_world,world)

            world:Destroy()
        end)

        test("Dump()", function()
            local world = box2d.NewWorld()
            local body = world:CreateBody()

            UTILS.test_method(body,"Dump",{})

            world:Destroy()
        end)

    end)
end