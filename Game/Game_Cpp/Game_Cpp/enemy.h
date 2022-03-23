#pragma once
#include "gameObj.h"
#include "graphics.h"


class Enemy : public GameObj<float> , public Collidable<Disk>
{
    float pos_x, pos_y , size , rotation , speed ,x , y;
    graphics::Brush brush;
    unsigned int points = 0;   
    bool _delete = false;
public:
    bool get_delete() const { return _delete; }
    void set_delete(bool a) { _delete = a; }
    void set_points(int pts);
    int get_points() const ;
    float get_pos_x() const override;
    bool check = false;
    float get_pos_y() const override { return y; }
    void set_pos_x(float x1) {pos_x = x1 ; }
    void set_pos_y(float y1) { pos_y = y1; }
    float get_size() const;
    void update() override;
    void draw() override;
    void init() override;
    void initialize(float x , float y, float siz, float sp, float x_axis, float y_axis);
    Enemy(const class Game& mygame , float x, float y, float siz, float sp,  float x_axis, float y_axis);
    ~Enemy();
    Disk getCollisionHull() const override;  
};