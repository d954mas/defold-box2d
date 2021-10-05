local UTILS = require "tests.test_utils"

return function()
    describe("BaseUserData", function()
        before(function()
            UTILS.set_env(getfenv(1))
        end)
        after(function() end)

        test("create", function()
            local w = box2d.NewWorld()
            assert_not_nil(w)
            assert_not_nil(w.__userdata_box2d)
            assert_equal(w.__userdata_type_box2d, "world")
            w:Destroy()
        end)

        test("destroy", function()
            local w = box2d.NewWorld()
            w:Destroy()
            assert_nil(w.__userdata_box2d)
            assert_equal(w.__userdata_type_box2d, "world")

        end)

        test("call destroyed", function()
            local w = box2d.NewWorld()
            w:Destroy()
            local status, value = pcall(w.IsLocked, w)
            assert_false(status)
            UTILS.test_error(value, "world was destroyed")
        end)

        test("call userdata obj with nil", function()
            local w = box2d.NewWorld()

            local status, error = pcall(w.IsLocked, nil)
            assert_false(status)
            UTILS.test_error(error, "can't get world. Need table get:nil")
            w:Destroy()
        end)

        test("call userdata obj with empty table", function()
            local w = box2d.NewWorld()

            local status, error = pcall(w.IsLocked, {})
            assert_false(status)
            UTILS.test_error(error, "unknown userdata type. Need world. Get (null)")
            w:Destroy()
        end)

        test("call userdata obj with another userdata type", function()
            local w = box2d.NewWorld()
            local b = w:CreateBody()

            local status, error = pcall(w.IsLocked, b)
            assert_false(status)
            UTILS.test_error(error, "Need world. Get body.")
            w:Destroy()
        end)


    end)
end
