local M = {}

local POS_START = vmath.vector3()
local POS_END = vmath.vector3()
local COLOR = vmath.vector4()

local COLOR_AXIS_X = vmath.vector4(1,0,0,1)
local COLOR_AXIS_Y = vmath.vector4(0,1,0,1)
local V3_AXIS_X = vmath.vector3()
local V3_AXIS_Y = vmath.vector3()

local message = {
    start_point = POS_START,
    end_point = POS_END,
    color = COLOR
}

local MSG_DRAW_LINE = hash("draw_line")

local function __draw_polygon(physics_scale,vertices,color)
    COLOR.x = color.r
    COLOR.y = color.g
    COLOR.z = color.b
    COLOR.w = color.a

    for i = 1, #vertices do
        local start = vertices[i]
        local finish = vertices[i + 1]
        if (not finish) then finish = vertices[1] end
        POS_START.x, POS_START.y = start.x / physics_scale, start.y / physics_scale
        POS_END.x, POS_END.y = finish.x / physics_scale, finish.y / physics_scale
        msg.post("@render:", MSG_DRAW_LINE, message)
    end
end

local function __draw_segment(physics_scale,p1,p2,color)
    COLOR.x = color.r
    COLOR.y = color.g
    COLOR.z = color.b
    COLOR.w = color.a

    message.start_point.x, message.start_point.y = p1.x/physics_scale, p1.y/physics_scale
    message.end_point.x, message.end_point.y = p2.x/physics_scale, p2.y/physics_scale
    msg.post("@render:", MSG_DRAW_LINE, message)
end

local function __draw_circle(physics_scale,center,radius,axis,color)
    COLOR.x = color.r
    COLOR.y = color.g
    COLOR.z = color.b
    COLOR.w = color.a

    local segments = 8
    local base_angle = 0
    local cx, cy = center.x / physics_scale, center.y / physics_scale
    radius = radius / physics_scale

    if( axis and axis.x ~= 0 and axis.y ~=0)then
        message.start_point.x, message.start_point.y = cx,cy
        message.end_point.x = cx + radius * axis.x
        message.end_point.y = cy + radius * axis.y
        msg.post("@render:", MSG_DRAW_LINE, message)
    end

    local a = math.pi * 2 / segments


    local x1 = cx + math.cos(base_angle) * radius
    local y1 = cy + math.sin(base_angle) * radius
    for i = 1, segments do
        local a2 = base_angle + i * a
        local x2, y2 = cx + math.cos(a2) * radius, cy + math.sin(a2) * radius
        message.start_point.x, message.start_point.y = x1,y1
        message.end_point.x, message.end_point.y = x2,y2
        msg.post("@render:", MSG_DRAW_LINE, message)
        x1, y1 = x2, y2
    end
end

---@param transform Box2dTransform
local function __draw_transform(physics_scale,transform)
    local position = transform.p
    position.x = position.x / physics_scale
    position.y = position.y / physics_scale

    local axis_x = V3_AXIS_X
    axis_x.x = 1
    axis_x.y = 0

    local axis_y =V3_AXIS_Y
    axis_y.x = 0
    axis_y.y = 1

    if(transform.q ~= 0)then
        local cos_q = math.cos(transform.q)
        local sin_q = math.sin(transform.q)
        axis_x.x = cos_q -- x * cos_q - y * sin_q
        axis_x.y = sin_q -- x * sin_q + y * cos_q

        axis_y.x = - sin_q -- x * cos_q - y * sin_q
        axis_y.y = cos_q -- x * sin_q + y * cos_q
    end

    local size = 0.4 / physics_scale

    message.start_point.x, message.start_point.y = position.x, position.y
    message.end_point.x, message.end_point.y = position.x + axis_x.x * size, position.y + axis_x.y * size
    message.color.x, message.color.y = COLOR_AXIS_X.x, COLOR_AXIS_X.y
    message.color.z, message.color.w = COLOR_AXIS_X.z, COLOR_AXIS_X.w
    msg.post("@render:", MSG_DRAW_LINE, message)

    message.end_point.x, message.end_point.y = position.x + axis_y.x * size, position.y + axis_y.y * size
    message.color.x, message.color.y = COLOR_AXIS_Y.x, COLOR_AXIS_Y.y
    message.color.z, message.color.w = COLOR_AXIS_Y.z, COLOR_AXIS_Y.w
    msg.post("@render:", MSG_DRAW_LINE, message)
end


function M.create_debug_draw(physics_scale)
    return box2d.NewDebugDraw({
        DrawPolygon = function(vertices,color) __draw_polygon(physics_scale,vertices,color) end,
        DrawSolidPolygon = function(vertices,color) __draw_polygon(physics_scale,vertices,color) end,
        DrawCircle = function(center,radius,color) __draw_circle(physics_scale,center,radius,nil,color) end,
        DrawSolidCircle = function(center,radius,axis,color) __draw_circle(physics_scale,center,radius,axis,color) end,
        DrawSegment = function(p1,p2,color) __draw_segment(physics_scale,p1,p2,color) end,
        DrawTransform = function(transform) __draw_transform(physics_scale,transform) end,
    })
end

return M