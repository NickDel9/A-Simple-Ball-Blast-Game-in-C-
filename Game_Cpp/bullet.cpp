#include "bullet.h"
#include "graphics.h"

float bullet::get_pos_x() const
{
    return pos_x;
}

float bullet::get_pos_y() const
{
    return pos_y;
}

void bullet::draw()
{
        graphics::Brush br;
        br.outline_opacity = 1.0f;
        br.texture = "";
        br.fill_color[0] = 0.0f;
        br.fill_color[1] = 0.0f;
        br.fill_color[2] = 0.0f;
        br.fill_opacity = 1.0f;
        br.outline_opacity = 0.0f;
        graphics::drawDisk(pos_x, pos_y - 30, 5, br);
}

void bullet::setPosition(float a , float b)
{
    pos_x = a;
    pos_y = b;
}

Disk bullet::getCollisionHull() const
{
    Disk disk;
    disk.cx = pos_x;
    disk.cy = pos_y;
    disk.radius = 15.0f;
    return disk;
}

bullet::bullet() { speed = 2.0f; }
