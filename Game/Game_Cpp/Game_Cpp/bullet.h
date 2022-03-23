#pragma once
#include "gameObj.h"

class bullet 
    : public Collidable<Disk> 
{
    float pos_x = 0.0f;
    float pos_y = 0.0f;
    float speed = 0.0f;
    bool _delete = false;
public:
    bool get_delete() const { return _delete; }
    void set_delete(bool a) { _delete = a; }
    float get_pos_x() const;
    float get_pos_y() const;
    void set_pos_y(float c) { pos_y = c; };
    float get_speed() const { return speed; }
    void draw();
    void setPosition(float a , float b);
    Disk getCollisionHull() const override;
    bullet();
};