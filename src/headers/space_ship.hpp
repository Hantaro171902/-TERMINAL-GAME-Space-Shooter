#pragma once 

#include <vector>
#include <string>

class SpaceShip {
private:
    int x; // x coordinate
    int y; // y coordinate
    int hp; // heart points
    int energy; // energy points
    bool isDead; // is the ship dead?

public:
    int getX();
    int getY();
    int getHP();

    bool isDead();
    
    SpaceShip(int _x, int _y);
    ~SpaceShip();
    
    void DrawSpaceShipInfo(); // Displays HP and energy points, I aligned them with the labels printed in DrawGameLimits
    void Draw(); // Draws the spaceship
    void Erase(); // Erases the spaceship from its current position
    void Explosion(); // Handles the explosion animation and logic when the ship is hit
    void Move(); // The main function of the spaceship

};