#pragma once

#include <vector>
#include <string>
#include "cursor_input.hpp"
#include "color.hpp"
#include "utils.hpp"
#include <iostream> 

class Bullet {
private:
    int x;
    int y;  
public:
    int getX();
    int getY();
    Bullet(int _x, int _y);
    ~Bullet();
    bool isOut();
    void Move();
};
