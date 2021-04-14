#pragma once

#include "gameObj.h"
#include "config.h"
#include "bullet.h"



class Player : public GameObj<float> , public Collidable<Disk>
{
    bullet main_bullet;
    bool n = false;
    float speed = 10.0f;
    float pos_x = CANVAS_WIDTH/2, pos_y = CANVAS_HEIGHT-50;
    float height = 1.0f;
    float level = 0.0f;
    bool not_alive = false;
    bool attack = false;
    std::vector<bullet> bulletlist;
    const char* vector = "spaceship.png";
public:
    bool get_life_condition() const { return not_alive; }
    void set_life_condition(bool a) { not_alive = a; }
    Player(const class Game& mygame);
    std::vector<bullet> &get_bulletlist();

    void update() override;
    void draw() override;
    void init() override;
    void set_player_vector(const char* vec);
    float get_pos_x() const override;
    float get_pos_y() const override;
    bool get_Attack() const;
    void set_Attack(bool b);
    Disk getCollisionHull() const override;
    Disk getCollisionBullet(bullet current_bullet) const;
    float getLevelState() const { return level; };
    void PlusLEvel(float amount) { level = std::max<float>(0.0f, level + amount); }
    void spawn_fire();
};