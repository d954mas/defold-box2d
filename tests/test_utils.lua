local telescope = require "deftest.telescope"

local M = {}

function M.set_env(env)
    for k, v in pairs(M) do
        if (type(v) == "function" and k ~= "set_env") then
            setfenv(v,env)
        end
    end
end


function M.__get_assert_f(config)
    local a_equal = assert_equal
    if(config.v3)then a_equal = assert_equal_v3 end
    if(config.float)then a_equal = assert_equal_float end
    return a_equal
end

function M.test_field(object, key, config)
    local a_equal = M.__get_assert_f(config)
    if (config.default) then a_equal(object[key], config.default) end
    assert(config.values)
    for _, value in ipairs(config.values) do
        object[key] = value
        a_equal(object[key], value)
    end
end

function M.test_method(object, key, config)
    local a_equal = M.__get_assert_f(config)
    config.args = config.args or {}
    local f = object[key]
    assert_not_nil(f)
    local result = f(object,unpack(config.args))
    if(config.result)then
        a_equal(result, config.result)
    end
end

function M.test_method_get_set(object, key, config)
    local a_equal = M.__get_assert_f(config)
    local get_f, set_f
    if(config.getter_full)then
        get_f = object[config.getter_full]
        assert(get_f) end
    if(config.setter_full)then
        set_f = object[config.setter_full]
        assert(set_f) end
    if(not get_f)then
        get_f = object[(config.getter or "Get") .. key]
    end
    if(not set_f)then
        set_f = object[(config.setter or "Set") .. key]
    end


    assert_not_nil(get_f)
    assert_not_nil(set_f)

    if (config.default) then a_equal(get_f(object), config.default) end
    assert(config.values)
    for _, value in ipairs(config.values) do
        set_f(object,value)
        a_equal(get_f(object), value)
    end
end

function M.test_error(error, result)
    --not worked in html no .lua in string
   -- local idx = string.find(error, "%.lua:")
   -- if(idx)then
    --    error = string.sub(error,idx + 5)
    --    local idx_2 = string.find(error, ":")
     --   error = string.sub(error,idx_2+2)
   -- end
    local start_error = error
    error = string.sub(error,#error-#result+1)
    if(error ~= result)then
        print("test error. Need:" .. result .. " Get:" .. start_error)
    end
    return assert_equal(error,result)
end

return M