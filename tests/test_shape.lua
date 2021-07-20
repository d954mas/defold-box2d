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

        test("circle", function()
            local w = box2d.NewWorld()
            local f = createFixture(w, {
                shape = box2d.b2Shape.e_circle,
                circle_radius = 1
            })

            f = createFixture(w, {
                shape = box2d.b2Shape.e_circle,
                circle_radius = 1,
                circle_position = vmath.vector3(0)
            })
            w:Destroy()
        end)

        test("edge", function()
            local w = box2d.NewWorld()
            local f = createFixture(w, {
                shape = box2d.b2Shape.e_edge,
                edge_two_sided = true,
                edge_v1 = vmath.vector3(0),
                edge_v2 = vmath.vector3(0),
            })

            f = createFixture(w, {
                shape = box2d.b2Shape.e_edge,
                edge_v0 = vmath.vector3(0),
                edge_v1 = vmath.vector3(0),
                edge_v2 = vmath.vector3(0),
                edge_v3 = vmath.vector3(0),
            })

            local status, error = pcall(createFixture, w, {
                shape = box2d.b2Shape.e_edge
            })
            assert_false(status)
            assert_equal(error, "edge_v1 not vector3")

            status, error = pcall(createFixture, w, {
                shape = box2d.b2Shape.e_edge,
                edge_v1 = vmath.vector3(0),
            })
            assert_false(status)
            assert_equal(error, "edge_v2 not vector3")

            status, error = pcall(createFixture, w, {
                shape = box2d.b2Shape.e_edge,
                edge_v1 = vmath.vector3(0),
                edge_v2 = vmath.vector3(0),
            })
            assert_false(status)
            assert_equal(error, "edge_v0 not vector3")

            status, error = pcall(createFixture, w, {
                shape = box2d.b2Shape.e_edge,
                edge_v1 = vmath.vector3(0),
                edge_v2 = vmath.vector3(0),
                edge_v0 = vmath.vector3(0),
            })
            assert_false(status)
            assert_equal(error, "edge_v3 not vector3")
            w:Destroy()
        end)

        test("box", function()
            local w = box2d.NewWorld()

            createFixture(w, {
                shape = box2d.b2Shape.e_polygon,
                box = true,
                box_hx = 1, box_hy = 1,
            })

            local status, error = pcall(createFixture, w, {
                shape = box2d.b2Shape.e_polygon,
                box = true,
                box_hx = 1
            })
            assert_false(status)
            assert_equal(error, "no box_hy")

            status, error = pcall(createFixture, w, {
                shape = box2d.b2Shape.e_polygon,
                box = true,
                box_hy = 1
            })
            assert_false(status)
            assert_equal(error, "no box_hx")

            createFixture(w, {
                shape = box2d.b2Shape.e_polygon,
                box = true,
                box_hx = 1, box_hy = 1,
                box_center = vmath.vector3(0, 0, 0), box_angle = math.pi / 4
            })

            status, error = pcall(createFixture, w, {
                shape = box2d.b2Shape.e_polygon,
                box = true,
                box_hx = 1, box_hy = 1,
                box_angle = math.pi / 4
            })
            assert_false(status)
            assert_equal(error, "box_angle exist but box_center not exist")

            status, error = pcall(createFixture, w, {
                shape = box2d.b2Shape.e_polygon,
                box = true,
                box_hx = 1, box_hy = 1,
                box_center = vmath.vector3(0)
            })
            assert_false(status)
            assert_equal(error, "box_center exist but box_angle not exist")

            w:Destroy()
        end)

        test("polygon", function()
            local w = box2d.NewWorld()

            createFixture(w, {
                shape = box2d.b2Shape.e_polygon,
                polygon_vertices = { vmath.vector3(0, 0, 0), vmath.vector3(1, 0, 0), vmath.vector3(1, 1, 0) }
            })

            w:Destroy()
        end)

        test("chain", function()
            local w = box2d.NewWorld()
            createFixture(w, {
                shape = box2d.b2Shape.e_chain,
                chain_vertices = { vmath.vector3(0, 0, 0), vmath.vector3(1, 0, 0), vmath.vector3(1, 1, 0) },
                chain_prev_vertex = vmath.vector3(0, 0, 0),
                chain_next_vertex = vmath.vector3(1, 1, 0)
            })

            createFixture(w, {
                shape = box2d.b2Shape.e_chain,
                chain_loop = true;
                chain_vertices = { vmath.vector3(0, 0, 0), vmath.vector3(1, 0, 0), vmath.vector3(1, 1, 0) },
            })

            local status, error = pcall(createFixture, w, {
                shape = box2d.b2Shape.e_chain,
            })
            assert_false(status)
            assert_equal(error, "no chain_vertices")

            status, error = pcall(createFixture, w, {
                shape = box2d.b2Shape.e_chain,
                chain_loop = true;
            })
            assert_false(status)
            assert_equal(error, "no chain_vertices")

            status, error = pcall(createFixture, w, {
                shape = box2d.b2Shape.e_chain,
                chain_vertices = { vmath.vector3(0, 0, 0), vmath.vector3(1, 0, 0), vmath.vector3(1, 1, 0) },
            })
            assert_false(status)
            assert_equal(error, "chain_prev_vertex not vector3")

            status, error = pcall(createFixture, w, {
                shape = box2d.b2Shape.e_chain,
                chain_vertices = { vmath.vector3(0, 0, 0), vmath.vector3(1, 0, 0), vmath.vector3(1, 1, 0) },
                chain_prev_vertex = vmath.vector3(0, 0, 0),
            })
            assert_false(status)
            assert_equal(error, "chain_next_vertex not vector3")

            w:Destroy()
        end)

        test("polygon", function()
            local w = box2d.NewWorld()

            local shape = box2d.NewPolygonShape()
            assert_equal(shape:GetType(), box2d.b2Shape.e_polygon)

            assert_equal_float(shape:GetRadius(), 0.01)

            local shape_clone = shape:Clone()
            --change
            assert_not_equal(shape, shape_clone)

            assert_equal(shape:GetChildCount(), 1)

            shape:TestPoint({ p = vmath.vector3(0), q = 1 }, vmath.vector3(0))

            local raycast = shape:RayCast({ p1 = vmath.vector3(0, 0, 0), p2 = vmath.vector3(1, 0, 0),
                                            maxFraction = 1 }, { p = vmath.vector3(0), q = 1 })
            pprint(raycast)
            assert_not_nil(raycast)
            assert_not_nil(raycast.normal)
            assert_not_nil(raycast.fraction)

            local aabb = shape:ComputeAABB({ p = vmath.vector3(0), q = 1 })
            assert_not_nil(aabb.lowerBound)
            assert_not_nil(aabb.upperBound)

            --   local massData = shape:ComputeMass(1)

            shape:Set({ vmath.vector3(0, 0, 0), vmath.vector3(1, 0, 0), vmath.vector3(1, 1, 0) })

            w:Destroy()
        end)
    end)

end