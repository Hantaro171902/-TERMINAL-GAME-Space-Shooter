#pragma once

#include <vector>
#include <string>
#include "cursor_input.hpp"
#include <iostream> 

class Bullet {
private:
    int x;
    int y;  
public:
    int X();    
    int Y();
    Bullet(int _x, int _y);
    bool isOut();
    void Move();
};
