#include "enemy.h"
#include "graphics.h"
#include "config.h"
#include "util.h"
#include "Game.h"

void Enemy::set_points(int pts)
{
    points = pts;
}

int Enemy::get_points() const
{
    return points;
}

float Enemy::get_pos_x() const
{
    return pos_x;
}


float Enemy::get_size() const
{
    return size;
}

void Enemy::update()
{
    float nx = pos_x + x;
    float ny = pos_y + y;

    if (nx - size + size / 2 <= 0 || nx + size - size / 2 >= CANVAS_WIDTH)
    {
        x = -x;
    }

    if (size == 75)
    {    
        if (ny - size + size / 2 <= CANVAS_HEIGHT/2 || ny + size - size / 2 >= CANVAS_HEIGHT)
        {
            y = -y;
        }
    }
    else 
    {
        if (ny - size + size / 2 <= CANVAS_HEIGHT / 3 - 200 || ny + size - size / 2 >= CANVAS_HEIGHT)
        {
            y = -y;
        }
    }
    pos_x += x + speed;
    pos_y += y + speed;
}

void Enemy::draw()
{
    graphics::setOrientation(rotation);
    brush.texture = std::string(ASSET_PATH) + "real_ball.png";
    graphics::drawRect(pos_x, pos_y, size, size, brush);
    graphics::resetPose();
    brush.outline_opacity = 0.0f;
    
    graphics::Brush text_life_br;
    text_life_br.fill_color[0] = 1.0f;
    text_life_br.fill_color[1] = 1.3f;
    text_life_br.fill_color[0] = 0.3f;
    text_life_br.fill_opacity = 0.8f;
    if (points < 120)
    {
        text_life_br.fill_color[0] = 0.0f;
        text_life_br.fill_color[1] = 1.0f;
        text_life_br.fill_color[0] = 1.0f;
    }

    char inf[40];
    std::string s = std::to_string(points);
    char const* pchar = s.c_str();
    sprintf_s(inf, pchar);
    graphics::drawText(pos_x- size / 3+5, pos_y+13, size/3, inf, text_life_br);
    

    if (game.get_debug_mode())
    {
        graphics::Brush br;
        br.outline_opacity = 1.0f;
        br.texture = "";
        br.fill_color[0] = 1.0f;
        br.fill_color[1] = 0.3f;
        br.fill_color[0] = 0.3f;
        br.fill_opacity = 0.3f;
        br.gradient = false;
        Disk hull = getCollisionHull();
        graphics::drawDisk(hull.cx, hull.cy, hull.radius, br);
    }
}

void Enemy::init()
{
}

void Enemy::initialize(float x1, float y1 , float siz , float sp, float x_axis, float y_axis)
{
    speed = sp;
    pos_x = x1;
    size = siz;
    pos_y = y1;
    x = x_axis;
    y = y_axis;
    rotation = 360 * random<float>(0.0f,1.0f);
}

Enemy::Enemy(const Game & mygame , float x, float y, float siz, float speed , float x_axis , float y_axis)
    :GameObj(mygame)
{
    initialize(x , y , siz , speed, x_axis , y_axis);
}

Enemy::~Enemy()
{
}

Disk Enemy::getCollisionHull() const
{

    Disk disk;
    disk.cx = pos_x;
    disk.cy = pos_y;
    disk.radius = size * 0.53f;
    return disk;
}



