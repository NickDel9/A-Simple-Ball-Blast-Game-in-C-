
#include "graphics.h"
#include "player.h"
#include "Game.h"



Player::Player(const Game& mygame)
    :GameObj(mygame)
{
}

std::vector<bullet> &Player::get_bulletlist()
{
    return bulletlist;
}


void Player::update()
{ 
    //actions for main player

    if (graphics::getKeyState(graphics::SCANCODE_LEFT))
    {
        pos_x -= speed * graphics::getDeltaTime() / 15.0f;
    }
    if (graphics::getKeyState(graphics::SCANCODE_RIGHT))
    {
        pos_x += speed * graphics::getDeltaTime() / 15.0f;
    }

    // spawn bullets 
    if (graphics::getKeyState(graphics::SCANCODE_SPACE))
    {     
        attack = true;   
        spawn_fire();     
    }

    if (pos_x < 0) pos_x = 0;
    if (pos_x > CANVAS_WIDTH) pos_x = CANVAS_WIDTH;
    if (pos_y < 0) pos_y = 0;
    if (pos_y > CANVAS_HEIGHT) pos_y = CANVAS_HEIGHT;
    
}

void Player::draw()
{  
    graphics::Brush br;
    br.outline_opacity = 0.0f;
    
    //draw spaceship
    br.fill_opacity = 1.0f;
    br.texture = std::string(ASSET_PATH) + vector;
    graphics::drawRect(pos_x, pos_y, 80, 80, br);
   
    graphics::resetPose();

    // draw fire while attack
    if (attack)
    {
        if (game.get_sound_status()) {
            graphics::playSound(std::string(ASSET_PATH) + "bullet.mp3", 0.05f, false);
        }
        float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 10);
        br.texture = "";
        br.fill_color[0] = 1.0f;
        br.fill_color[1] = 0.5f + glow * 0.5f;
        br.fill_color[2] = 0.0f;
        br.fill_secondary_color[0] = 0.3f;
        br.fill_secondary_color[1] = 0.1f;
        br.fill_secondary_color[2] = 0.0f;
        br.fill_opacity = 1.0f;
        br.fill_secondary_opacity = 0.0f;
        br.gradient = true;
        br.outline_opacity = 0;
        graphics::setScale(height, height);
        graphics::drawDisk(pos_x * height, pos_y - 30, 18, br);
    }
    graphics::resetPose();
    if (bulletlist.size() > 0)
    {
       for (int i = 0; i < bulletlist.size(); i++)
       {
            bulletlist[i].draw();
        }
    }

    if(game.get_debug_mode()) 
    {
        br.outline_opacity = 1.0f;
        br.texture = "";
        br.fill_color[0] = 0.3f;
        br.fill_color[1] = 1.0f;
        br.fill_color[0] = 0.3f;
        br.fill_opacity = 0.3f;
        br.gradient = false;
        Disk hull = getCollisionHull();
        graphics::drawDisk(hull.cx, hull.cy,hull.radius, br);
    }
}

void Player::init()
{
}

void Player::set_player_vector(const char * vec)
{
    vector = vec;
}

float Player::get_pos_x() const
{
    return pos_x;
}

float Player::get_pos_y() const
{
    return pos_y;
}

bool Player::get_Attack() const
{
    return attack;
}

void Player::set_Attack(bool b)
{
    attack = b;
}

Disk Player::getCollisionHull() const
{
    Disk disk;
    disk.cx = get_pos_x();
    disk.cy = get_pos_y();
    disk.radius = 40.0f;
    return disk;
}

Disk Player::getCollisionBullet(bullet current_bullet) const
{
    return current_bullet.getCollisionHull();
}

void Player::spawn_fire()
{
    main_bullet.setPosition(pos_x, pos_y);
    bulletlist.push_back(main_bullet);
}

