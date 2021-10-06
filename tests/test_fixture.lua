local UTILS = require "tests.test_utils"

---@param world Box2dWorld
local function createFixture(world, def)
    local body = world:CreateBody({ type = box2d.b2BodyType.b2_dynamicBody })
    local f = body:CreateFixture(def)
    assert_not_nil(f)
    return f;
end

local shape = { shape = box2d.b2Shape.e_circle, circle_radius = 1, circle_position = vmath.vector3(0) }

return function()
    describe("Fixture", function()
        before(function()
            UTILS.set_env(getfenv(1))
            setfenv(createFixture, (getfenv(1)))
        end)
        after(function() end)

        test("body:CreateFixture(def)", function()
            local w = box2d.NewWorld()
            createFixture(w, {
                shape = shape
            })
            local shape_userdata = box2d.NewCircleShape()
            createFixture(w, { shape = shape_userdata })
            w:Destroy()
        end)

        test("body:CreateFixture(shape,density)", function()
            local w = box2d.NewWorld()
            local body = w:CreateBody()
            local f1 = body:CreateFixture({ shape = box2d.b2Shape.e_circle, circle_radius = 1, circle_position = vmath.vector3(0) }, 1)
            assert_not_nil(f1)

            local shape_userdata = box2d.NewCircleShape()
            f1 = body:CreateFixture(shape_userdata, 1)
            assert_not_nil(f1)
            w:Destroy()
        end)
        test("body:CreateFixture(shape) ERROR", function()
            local w = box2d.NewWorld()
            local body = w:CreateBody()
            --call with def but put shape
            local f = function()
                body:CreateFixture({ shape = box2d.b2Shape.e_circle, circle_radius = 1, circle_position = vmath.vector3(0) })
            end
            local status, error = pcall(f)
            assert_false(status)
            local error_1 = "unknown key:circle_position"
            local error_2 = "b2Shape should be table or userdata"
            local error_3 = "unknown key:circle_radius"

            local error_1_2 =  string.sub(error,#error-#error_1+1)
            local error_2_2 =  string.sub(error,#error-#error_2+1)
            local error_3_2 =  string.sub(error,#error-#error_3+1)

            assert_true(error_1 == error_1_2 or error_2 == error_2_2 or error_3 == error_3_2)
            w:Destroy()
        end)

        test("body:DestroyFixture(fixture)", function()
            local w = box2d.NewWorld()
            local body = w:CreateBody()
            local fixture = body:CreateFixture({ shape = box2d.b2Shape.e_circle, circle_radius = 1, circle_position = vmath.vector3(0) }, 1)
            body:DestroyFixture(fixture)
            assert_nil(fixture.__userdata_box2d)
            assert_equal(fixture.__userdata_type_box2d,"fixture")
            local f = function()
                tostring(fixture)
            end
            local status, error = pcall(f)
            assert_false(status)
            UTILS.test_error(error, "fixture was destroyed")
            w:Destroy()
        end)

        test("Equals", function()
            local world = box2d.NewWorld()
            local body = world:CreateBody()
            local f_1 = body:CreateFixture({ shape = shape })
            local f_2 = body:CreateFixture({ shape = shape })

            assert_equal(f_1, f_1)
            assert_not_equal(f_1, f_2)
            assert_not_equal(f_1, 1)

            local f_1_next_nil = f_1:GetNext()
            local f_2_next_1 = f_2:GetNext()
            assert_nil(f_1_next_nil)
            assert_not_nil(f_2_next_1)

            assert_equal(f_1, f_2_next_1)

            world:Destroy()
        end)

        test("destroy fixture after body destroyed", function()
            local w = box2d.NewWorld()
            local body = w:CreateBody({})
            local fixture = body:CreateFixture({ shape = shape })

            w:DestroyBody(body)

            local status, value = pcall(fixture.GetDensity, fixture)
            assert_false(status)
            UTILS.test_error(value, "fixture was destroyed")

            w:Destroy()
        end)

        test("destroy fixture after world destroyed", function()
            local w = box2d.NewWorld()
            local body = w:CreateBody({})
            local fixture = body:CreateFixture({ shape = shape })

            w:Destroy()
            local status, value = pcall(fixture.GetDensity, fixture)
            assert_false(status)
            UTILS.test_error(value, "fixture was destroyed")
        end)

        test("GetType()", function()
            local w = box2d.NewWorld()
            local f = createFixture(w, {
                shape = { shape = box2d.b2Shape.e_circle, circle_radius = 1, circle_position = vmath.vector3(0) }
            })
            assert_equal(f:GetType(), box2d.b2Shape.e_circle)
            f = createFixture(w, {
                shape = { shape = box2d.b2Shape.e_polygon, box = true, box_hx = 1, box_hy = 1 }
            })
            assert_equal(f:GetType(), box2d.b2Shape.e_polygon)

            w:Destroy()
        end)

        test("GetShape()", function()
            local w = box2d.NewWorld()
            local circle_shape = box2d.NewCircleShape()
            circle_shape:SetRadius(1)

            local body = w:CreateBody({ type = box2d.b2BodyType.b2_dynamicBody })
            local f = body:CreateFixture({ shape = circle_shape })
            assert_equal(f:GetType(), box2d.b2Shape.e_circle)
            local shape_fixture = f:GetShape()
            assert_equal(f:GetType(), shape_fixture:GetType())

            assert_equal(circle_shape:GetRadius(), shape_fixture:GetRadius())
            shape_fixture:SetRadius(2)
            assert_not_equal(shape_fixture:GetRadius(), circle_shape:GetRadius())

            w:Destroy()
        end)

        test("Set/Is Sensor()", function()
            local w = box2d.NewWorld()
            local f = createFixture(w, { shape = shape })
            UTILS.test_method_get_set(f, "Sensor", {
                getter = "Is",
                values = { true, false, true }
            })
            w:Destroy()
        end)

        test("Set/Get FilterData()", function()
            local w = box2d.NewWorld()
            local f = createFixture(w, { shape = shape })
            f:SetFilterData({
                categoryBits = 32,
                maskBits = 16,
                groupIndex = 10,
            })
            local filter = f:GetFilterData()
            assert_equal(filter.categoryBits, 32)
            assert_equal(filter.maskBits, 16)
            assert_equal(filter.groupIndex, 10)
            w:Destroy()

            local status, error = pcall(f.SetFilterData, f, {})
            assert_false(status)
        end)

        test("Refilter()", function()
            local w = box2d.NewWorld()
            local f = createFixture(w, { shape = shape })
            UTILS.test_method(f, "Refilter", {})
            w:Destroy()
        end)

        test("GetBody()", function()
            local w = box2d.NewWorld()
            local body = w:CreateBody({})
            local fixture = body:CreateFixture({ shape = shape })
            assert_equal(fixture:GetBody(), body)
            w:Destroy()
        end)

        test("GetNext()", function()
            local w = box2d.NewWorld()
            local body = w:CreateBody({})
            local fixture_1 = body:CreateFixture({ shape = shape })
            local fixture_2 = body:CreateFixture({ shape = shape })
            assert_nil(fixture_1:GetNext())
            assert_equal(fixture_2:GetNext(), fixture_1)
            w:Destroy()
        end)

        test("Set/Get UserData()", function()
            local w = box2d.NewWorld()
            local fixture = createFixture(w, { shape = shape })
            assert_nil(fixture:GetUserData())

            local userdata = {}
            fixture:SetUserData(userdata)
            assert_equal(fixture:GetUserData(), userdata)

            w:Destroy()
        end)

        test("TestPoint()", function()
            local w = box2d.NewWorld()
            local fixture = createFixture(w, { shape = shape })
            assert_true(fixture:TestPoint(vmath.vector3(0, 0, 0)))
            assert_false(fixture:TestPoint(vmath.vector3(1.1, 0, 0)))

            w:Destroy()
        end)

        test("RayCast()", function()
            local w = box2d.NewWorld()
            local shape_userdata = box2d.NewCircleShape()
            shape_userdata:SetRadius(1)
            local fixture = createFixture(w, { shape = shape_userdata })

            local raycast = fixture:RayCast({ p1 = vmath.vector3(-2, 2, 0), p2 = vmath.vector3(2, 2, 0), maxFraction = 1 }, 0)
            assert_nil(raycast)

            raycast = fixture:RayCast({ p1 = vmath.vector3(-2, 0, 0), p2 = vmath.vector3(2, 0, 0), maxFraction = 1 }, 0)

            assert_not_nil(raycast)
            assert_not_nil(raycast.normal)
            assert_not_nil(raycast.fraction)

            w:Destroy()
        end)

        test("GetMassData()", function()
            local w = box2d.NewWorld()
            local fixture = createFixture(w, {
                shape = { shape = box2d.b2Shape.e_circle, circle_radius = 1, circle_position = vmath.vector3(0) },
                density = 1 })

            local mass_data = fixture:GetMassData()
            assert_equal_float(mass_data.mass, 3.1415927410126)
            assert_equal_float(mass_data.I, 1.5707963705063)
            assert_equal(mass_data.center.x, 0)
            assert_equal(mass_data.center.y, 0)

            w:Destroy()
        end)

        test("Set/Get Density()", function()
            local w = box2d.NewWorld()
            local f = createFixture(w, { shape = shape })
            UTILS.test_method_get_set(f, "Density", {
                values = { 1, 0.5, 2 }, default = 0
            })
            w:Destroy()
        end)

        test("Set/Get Friction()", function()
            local w = box2d.NewWorld()
            local f = createFixture(w, { shape = shape })
            UTILS.test_method_get_set(f, "Friction", {
                values = { 1, 0.5, 2 }
            })
            w:Destroy()
        end)

        test("Set/Get Restitution()", function()
            local w = box2d.NewWorld()
            local f = createFixture(w, { shape = shape })
            UTILS.test_method_get_set(f, "Restitution", {
                values = { 1, 0.5, 2 }, default = 0
            })
            w:Destroy()
        end)

        test("Set/Get RestitutionThreshold()", function()
            local w = box2d.NewWorld()
            local f = createFixture(w, { shape = shape })
            UTILS.test_method_get_set(f, "RestitutionThreshold", {
                values = { 1, 0.5, 2 }
            })
            w:Destroy()
        end)

        test("GetAABB()", function()
            local w = box2d.NewWorld()
            local f = createFixture(w, { shape = shape })
            local aabb = f:GetAABB(0);
            assert_not_nil(aabb.lowerBound)
            assert_not_nil(aabb.upperBound)
            w:Destroy()
        end)

        test("Dump()", function()
            local w = box2d.NewWorld()
            local f = createFixture(w, { shape = shape })
            UTILS.test_method(f, "Dump", { args = { 0 } })
            w:Destroy()
        end)

    end)
end