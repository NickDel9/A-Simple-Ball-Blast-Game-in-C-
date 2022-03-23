#pragma once

class customize 
{
    bool spaceship1 = false;
    bool spaceship = false;
    bool spaceship2 = false;
    int spaceship_num = 2 ;
public:
    void update();
    void draw();
    void init();
    int get_spaceship() const;
    customize();
};