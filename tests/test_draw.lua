local UTILS = require "tests.test_utils"

return function()
    describe("Draw", function()
        before(function()
            UTILS.set_env(getfenv(1))
        end)
        after(function() end)

        test("create debug draw", function()
            local cfg = {
                flags = 0,
                DrawPolygon = function() end,
                DrawSolidPolygon = function() end,
                DrawCircle = function() end,
                DrawSolidCircle = function() end,
                DrawSegment = function() end,
                DrawTransform = function() end,
                DrawPoint = function() end,
            }
            local draw = box2d.NewDebugDraw(cfg)
            assert_not_nil(draw)
            assert_not_nil(draw.__userdata_box2d)
            assert_equal(draw.__userdata_type_box2d,"draw")

            cfg.DrawBad = function() end

            local status, error = pcall(box2d.NewDebugDraw, cfg)
            assert_false(status)
            UTILS.test_error(error, "unknown key:DrawBad")
            draw:Destroy()
        end)

        test("Destroy()", function()
            local draw = box2d.NewDebugDraw({ })

            draw:GetFlags()
            draw:Destroy()

            assert_nil(draw.__userdata_box2d)
            assert_equal(draw.__userdata_type_box2d,"draw")

            local status, error = pcall(draw.GetFlags, draw)
            assert_false(status)
            UTILS.test_error(error, "draw was destroyed")
        end)

        test("world:DrawDebug()", function()
            local w = box2d.NewWorld()
            local circles = 0
            local draw = box2d.NewDebugDraw({
                DrawSolidCircle = function(...)
                    circles = circles + 1;
                end
            })
            local body = w:CreateBody({})
            body:CreateFixture({ shape = box2d.b2Shape.e_circle, circle_radius = 1 }, 1)

            w:DebugDraw()
            assert_equal(circles, 0)
            w:SetDebugDraw(draw)
            assert_equal(circles, 0)
            w:DebugDraw()
            assert_equal(circles, 0)

            draw:SetFlags(box2d.b2Draw.e_shapeBit)
            w:DebugDraw()
            assert_equal(circles, 1)

            w:SetDebugDraw(nil)
            w:DebugDraw()
            assert_equal(circles, 1)

            w:SetDebugDraw(draw)
            w:DebugDraw()
            assert_equal(circles, 2)

            draw:Destroy()
            w:DebugDraw()
        end)


    end)
end