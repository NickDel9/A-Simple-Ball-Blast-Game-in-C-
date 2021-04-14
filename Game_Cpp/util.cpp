
#include "util.h"
#include "config.h"



float rand0to1()
{
    return rand() / (float)RAND_MAX;
}

graphics::Brush Brush_Buttons::declare_brush_color(graphics::Brush br)
{
    br.fill_color[0] = 0.0f;
    br.fill_color[1] = 0.0f;
    br.fill_color[2] = 0.0f;
    br.fill_secondary_color[0] = 0.0f;
    br.fill_secondary_color[1] = 0.0f;
    br.fill_secondary_color[2] = 0.0f;
    br.fill_opacity = 0.3f;
    br.gradient = true;
    br.outline_opacity = 0.0f;
    
    return br;
}

graphics::Brush Brush_Buttons::change_brush_color(graphics::Brush br)
{
    br.fill_secondary_color[0] = 1.0f;
    br.fill_secondary_color[1] = 1.0f;
    br.fill_secondary_color[2] = 1.0f;
    br.fill_opacity = 1.0f;
    br.outline_opacity = 1.0f;

    return br;
}

graphics::Brush Brush_Buttons::change_brush_text( graphics::Brush text_br)
{
    text_br.fill_color[0] = 0.0f;
    text_br.fill_color[1] = 0.0f;
    text_br.fill_color[2] = 0.0f;

    return text_br;
}

graphics::Brush Brush_Buttons::declare_brush_text(graphics::Brush text_br)
{
    text_br.fill_color[0] = 1.0f;
    text_br.fill_color[1] = 1.0f;
    text_br.fill_color[2] = 1.0f;
    text_br.fill_opacity = 1.0f;

    return text_br;
}
