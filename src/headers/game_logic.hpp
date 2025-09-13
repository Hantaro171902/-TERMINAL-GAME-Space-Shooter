#pragma once 

#include <vector>
#include <string>
#include "cursor_input.hpp"
#include "color.hpp"
#include "space_ship.hpp"
#include "bullet.hpp"
#include "asteroid.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>

class  Game {
private:
    SpaceShip ship;
    Bullet* bullet; // Pointer to a Bullet object
    Asteroid* asteroid; // Pointer to an Asteroid object
    int score;

public:
    Game(/* args */);
    ~Game();
    void DrawGameLimits(); // Draws the limits of the game area and the labels for HP and energy
    void WelcomeMessage(); // Displays a welcome message
    void GameOverVictoryMessage(); // Displays a victory message
    void GameOverDefeatMessage(); // Displays a defeat message
    void SpecialMessage(); // A special message for your special needs
    void DrawWindowFrame(int ax, int ay, int bx, int by); // Draws a window frame given two coordinates
    void DrawWhiteSpace(int ax, int ay, int bx, int by); // Draws white space in a
    void run(); // The main function of the game
};


