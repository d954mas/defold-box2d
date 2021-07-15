local BOX2D_UTILS = require "box2d.utils"

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

M.debug_draw = {
    draw = BOX2D_UTILS.create_debug_draw(0.04),
    flags = bit.bor(box2d.b2Draw.e_shapeBit,box2d.b2Draw.e_jointBit)
}

M.debug_draw.draw:SetFlags(M.debug_draw.flags)

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
        cfg.world:Step(cfg.dt * cfg.time_scale,cfg.velocityIterations,cfg.positionIterations)
        cfg.world:DebugDraw()
    end
end

return M