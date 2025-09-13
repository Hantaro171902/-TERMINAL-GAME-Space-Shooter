#pragma once

#include <vector>
#include <string>
#include "cursor_input.hpp"
#include "color.hpp"
#include "utils.hpp"
#include <iostream>
#include <chrono>
#include <thread>

class Asteroid {
private:
    int x;
    int y;
public:
    int getX();
    int getY();
    Asteroid(int _x, int _y);
    ~Asteroid();
    void Draw();
    void Collision(class SpaceShip & ss); // The asteroid finds the spaceship

};