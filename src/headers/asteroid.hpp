#pragma once

#include <vector>
#include <string>
#include "cursor_input.hpp"
#include <iostream>
#include <chrono>
#include <thread>

class Asteroid {
private:
    int x;
    int y;
public:
    int X();
    int Y();    
    Asteroid(int _x, int _y);
    void Draw();
    void Collision(class SpaceShip & ss); // The asteroid finds the spaceship

}