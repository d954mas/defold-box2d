local DEFTEST = require "deftest.deftest"
local TEST_BASE_USERDATA = require "tests.test_base_userdata"
local TEST_EXTENSION = require "tests.test_extension"
local TEST_WORLD = require "tests.test_world"
local TEST_BODY_DEF = require "tests.test_body_def"
local TEST_FIXTURE_DEF = require "tests.test_fixture_def"
local TEST_SHAPE = require "tests.test_shape"
local TEST_BODY = require "tests.test_body"
local TEST_FIXTURE = require "tests.test_fixture"
local TEST_JOINT_DEF = require "tests.test_joint_def"
local TEST_JOINT = require "tests.test_joint"
local TEST_DRAW = require "tests.test_draw"
local TEST_CONTACT = require "tests.test_contact"
local TELESCOPE = require "deftest.telescope"

local M = {}

function M.run()
    TELESCOPE.make_assertion(
            "equals_v3",
            function(_, a,b) return string.format(TELESCOPE.assertion_message_prefix .. "'%s' to be equal to '%s'",a,b) end,
            function(a, b)
                if(type(a) ~= "userdata" or type(b)~= "userdata") then assert("not v3") end
                return a.x == b.x and a.y == b.y and a.z == b.z
            end
    )
    TELESCOPE.make_assertion(
            "equal_v3",
            function(_, a,b) return string.format(TELESCOPE.assertion_message_prefix .. "'%s' to be equal to '%s'",tostring(a),tostring(b)) end,
            function(a, b)
                if(type(a) ~= "userdata" or type(b)~= "userdata") then assert("not v3") end
                local dx = math.abs(a.x-b.x)
                local dy = math.abs(a.y-b.y)
                local dz = math.abs(a.z-b.z)
                return dx <= 0.0000001 and dy <= 0.0000001 and dz <= 0.0000001
            end
    )
    TELESCOPE.make_assertion(
            "equal_float",
            function(_, a,b) return string.format(TELESCOPE.assertion_message_prefix .. "'%s' to be equal to '%s'",a,b) end,
            function(a, b)
                if(type(a) ~= "number" or type(b)~= "number") then assert("not v3") end
                local d = math.abs(a-b)
                return d >=0 and d <= 0.0000001
            end
    )

    DEFTEST.add(TEST_BASE_USERDATA)
    DEFTEST.add(TEST_EXTENSION)
    DEFTEST.add(TEST_DRAW)
    DEFTEST.add(TEST_WORLD)
    DEFTEST.add(TEST_BODY_DEF)
    DEFTEST.add(TEST_BODY)
    DEFTEST.add(TEST_SHAPE)
    DEFTEST.add(TEST_FIXTURE_DEF)
    DEFTEST.add(TEST_FIXTURE)
    DEFTEST.add(TEST_JOINT_DEF)
    DEFTEST.add(TEST_JOINT)
    DEFTEST.add(TEST_CONTACT)
    DEFTEST.run()
end

return M