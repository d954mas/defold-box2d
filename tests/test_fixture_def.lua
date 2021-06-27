local UTILS = require "tests.test_utils"

---@param world Box2dWorld
local function createFixture(world, def)
    local body = world:CreateBody()
    local f =  body:CreateFixture(def)
    assert_not_nil(f)
    return f;
end

local shape = {shape = box2d.b2Shape.e_circle, circle_radius = 1, circle_position = vmath.vector3(0)}

return function()
    describe("FixtureDef", function()
        before(function()
            UTILS.set_env(getfenv(1))
            setfenv(createFixture,getfenv(1))
        end)
        after(function() end)

        test("shape",function()
            local w = box2d.NewWorld()
            local f =createFixture(w,{
                shape = shape
            })
            assert_not_nil(f)

            w:Destroy()
        end)

        test("shape nil",function()
            local w = box2d.NewWorld()
            local status,error = pcall(createFixture,w,{})
            assert_false(status)
            assert_equal(error,"fixture def must have shape")
            w:Destroy()
        end)

        test("userData",function()
            local w = box2d.NewWorld()
            local userdata = {}
            local f =createFixture(w,{
                shape = shape, friction = 0, userData = userdata
            })
            assert_not_nil(f)
            assert_equal(f:GetUserData(),userdata)

            w:Destroy()
        end)


        test("friction",function()
            local w = box2d.NewWorld()
            local f =createFixture(w,{
                shape = shape, friction = 0.5
            })
            assert_not_nil(f)
            assert_equal(f:GetFriction(),0.5)

            w:Destroy()
        end)

        test("restitution",function()
            local w = box2d.NewWorld()
            local f =createFixture(w,{
                shape = shape, restitution = 0.5
            })
            assert_not_nil(f)
            assert_equal(f:GetRestitution(),0.5)

            w:Destroy()
        end)

        test("restitutionThreshold",function()
            local w = box2d.NewWorld()
            local f =createFixture(w,{
                shape = shape, restitutionThreshold = 0.5
            })
            assert_not_nil(f)
            assert_equal(f:GetRestitutionThreshold(),0.5)

            w:Destroy()
        end)
        test("density",function()
            local w = box2d.NewWorld()
            local f =createFixture(w,{
                shape = shape, density = 0.5
            })
            assert_not_nil(f)
            assert_equal(f:GetDensity(),0.5)

            w:Destroy()
        end)

        test("isSensor",function()
            local w = box2d.NewWorld()
            local f =createFixture(w,{
                shape = shape, isSensor = true
            })
            assert_not_nil(f)
            assert_true(f:IsSensor())

            w:Destroy()
        end)

        


    end)
end