#pragma once

#include "util.h"

template <class T>

class Collidable
{
public:
    virtual T getCollisionHull() const = 0;
};

template <class T>

class GameObj
{
protected:
    const class Game& game;
public:
    GameObj(const class Game& g1);
    virtual T get_pos_x() const = 0 ;
    virtual T get_pos_y() const = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void init() = 0;
};