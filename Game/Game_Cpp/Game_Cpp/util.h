#pragma once

#include <random>
#include <graphics.h>

float rand0to1();

template <typename T>

T random(T min, T max)
{
    return min + (rand() / (RAND_MAX / (max - min)));
}

struct Disk 
{
    float cx, cy;
    float radius;
};

struct Brush_Buttons
{
public :
    graphics::Brush declare_brush_color(graphics::Brush br );
    graphics::Brush change_brush_color(graphics::Brush br);
    graphics::Brush change_brush_text(graphics::Brush text_br);
    graphics::Brush declare_brush_text(graphics::Brush text_br);
};