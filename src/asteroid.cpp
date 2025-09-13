#include "asteroid.hpp"
#include "space_ship.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

Asteroid::Asteroid(int _x, int _y) : x(_x), y(_y) {
    // Constructor logic (if needed)
    srand(time(nullptr));
}

int Asteroid::getX() { return x; }
int Asteroid::getY() { return y; }

void Asteroid::Collision(SpaceShip & ss) {// The asteroid finds the spaceship
    if (((x >= ss.getX()) && (x <= ss.getX() + 5)) && ((y >= ss.getY()) && (y <= ss.getY() + 2))) { // Depending on the shape of the spaceship you have to tinker when the asteroid really hits you
      ss.Damage(); // The asteroid hurts
      move_cursor(x, y);
      cout << " "; // And the asteroid is "destroyed"
      x = rand() % 74 + 3; // The truth is it just teleports to the top of the map
      y = 4;
    } else {
      move_cursor(x, y);
      cout << " ";
      y++;
      if (y > 22) { // If the asteroid goes too down in the map
        x = rand() % 74 + 3; // It will be teleported to the top
        y = 4;
      }
      Draw();
    }
}

void Asteroid::Draw() {
    move_cursor(x, y);
    cout << "*"; // Fear the asteroids!!
}

