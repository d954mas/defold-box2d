local BOX2D_UTILS = require "box2d.utils"

local M = {}

function M.get_debug_draw()
    if(not M.debug_draw)then
        M.debug_draw = BOX2D_UTILS.create_debug_draw(0.04)
        M.debug_draw:SetFlags(bit.bor(box2d.b2Draw.e_shapeBit,box2d.b2Draw.e_jointBit))
    end
    return M.debug_draw
end


return M