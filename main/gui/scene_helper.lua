local BOX2D_UTILS = require "box2d.utils"
local LUME = require "libs.lume"

local M = {}

M.dirty = false -- if dirty update gui. Scene reload/changed

M.scene_config = {
    name = "",
    ---@type Box2dWorld
    world = nil,
    time_scale = 1,
    dt = 1 / 60,
    velocityIterations = 8,
    positionIterations = 3,
    dt = 1 / 60,
}

M.world_step_time = 0

M.debug_draw = {
    draw = BOX2D_UTILS.create_debug_draw(0.04),
    flags = bit.bor(box2d.b2Draw.e_shapeBit, box2d.b2Draw.e_jointBit)
}

function M.scene_new(cfg)
    M.dirty = true
    M.scene_config.name = assert(cfg.name)
    M.scene_config.world = assert(cfg.world)

    M.scene_config.world:SetDebugDraw(M.debug_draw.draw)
end

function M.scene_final()
    M.scene_config.world = nil
end

function M.update(dt)
    local cfg = M.scene_config
    if (cfg.world) then
        local time = socket.gettime()
        cfg.world:Step(cfg.dt * cfg.time_scale, cfg.velocityIterations, cfg.positionIterations)
        M.world_step_time = socket.gettime() - time
        cfg.world:DebugDraw()
    end
end

function M.reset()
    local cfg = M.scene_config
    M.dirty = true
    cfg.velocityIterations = 8
    cfg.positionIterations = 3
    M.debug_draw.flags =  bit.bor(box2d.b2Draw.e_shapeBit, box2d.b2Draw.e_jointBit)
    M.debug_draw.draw:SetFlags(M.debug_draw.flags)
end

function M.cfg_velocity_iterations_add(value)
    M.scene_config.velocityIterations = LUME.clamp(M.scene_config.velocityIterations + value, 1, 100)
end
function M.cfg_position_iterations_add(value)
    M.scene_config.positionIterations = LUME.clamp(M.scene_config.positionIterations + value, 1, 100)
end

function M.debug_draw_add_flag(flag)
    M.debug_draw.flags = bit.bor(M.debug_draw.flags, flag)
    M.debug_draw.draw:SetFlags(M.debug_draw.flags)
end

function M.debug_draw_remove_flag(flag)
    M.debug_draw.flags = bit.band(M.debug_draw.flags, bit.bnot(flag))
    M.debug_draw.draw:SetFlags(M.debug_draw.flags)
end

M.reset()

return M