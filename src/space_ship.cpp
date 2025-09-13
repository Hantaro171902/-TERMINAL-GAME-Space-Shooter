#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <memory>
#include <iomanip>
#include "space_ship.hpp"
#include "cursor_input.hpp"
#include "color.hpp"
#include "utils.hpp"

using namespace std;

SpaceShip::SpaceShip(int _x, int _y) : x(_x), y(_y), hp(3), energy(5), imDead(false) {
    // Constructor logic (if needed)
    srand(time(nullptr));

}

SpaceShip::~SpaceShip() {
    // Destructor logic (if needed)
    restoreTerminalBlocking();
}

int SpaceShip::getX() { return x; }
int SpaceShip::getY() { return y; }
int SpaceShip::getHP() { return hp; }

bool SpaceShip::isDead() { 
    DrawSpaceShipInfo(); // It's annoying to die and still see a heart on the screen
    return imDead; 
}

void SpaceShip::DrawSpaceShipInfo() { // Displays HP and energy points, I aligned them with the labels printed in DrawGameLimits
    move_cursor(5, 1);
    cout << "     ";
    for (int i = 0; i < hp; i++) {
      move_cursor(5 + i, 1);
      cout << ("%c", 3);
    }
    move_cursor(23, 1);
    cout << "     ";
    for (int i = 0; i < energy; i++) {
      move_cursor(23 + i, 1);
      cout << ("%c", 222);
    }
}

void SpaceShip::Draw() { // This is our spaceship
    move_cursor(x, y);
    cout << ("  %c  ", 30);
    move_cursor(x, y + 1);
    cout << ("  %c  ", 4);
    move_cursor(x, y + 2);
    cout << ("%c%c%c%c%c", 17, 30, 223, 30, 16);
}

void SpaceShip::Erase() { // This was or spaceship
    move_cursor(x, y);
    cout << ("     ");
    move_cursor(x, y + 1);
    cout << ("     ");
    move_cursor(x, y + 2);
    cout << ("     ");
}

void SpaceShip::Damage() { // The spaceship is damaged
    energy--;
    if (energy == 0) {
      Explosion();
    } else {
      Erase(); // You can omit this part, is meant to visually tell you that you were hit
      move_cursor(x, y);
      printf("  *  ");
      move_cursor(x, y + 1);
      printf("  *  ");
      move_cursor(x, y + 2);
      printf("*****");
      sleep(100);
    } 
}

void SpaceShip::Explosion() { // When you lose a heart :c
    hp--;
    Erase();
    move_cursor(x, y);
    cout << ("  *  ");
    move_cursor(x, y + 1);
    cout << ("  *  ");
    move_cursor(x, y + 2);
    cout << ("*****");
    sleep(100);
    Erase();
    move_cursor(x, y);
    cout << (" * * ");
    move_cursor(x, y + 1);
    cout << ("* * *");
    move_cursor(x, y + 2);
    cout << (" * * ");
    sleep(100);
    Erase();
    move_cursor(x, y);
    cout << ("*   *");
    move_cursor(x, y + 1);
    cout << (" * * ");
    move_cursor(x, y + 2);
    cout << ("* * *");
    sleep(100);
    if (hp > 0) { // If you still have a heart or more
      energy = 5;
    } else { // If you don't
      imDead = true;
    }
}

void SpaceShip::Move() { // The main function of the spaceship
    if (kbhit()) { // If you move the spaceship
      Erase(); // Look I'm invisible
      InputKey key; // What did you type?
      switch (key) { // Checks if the spaceship won't leave the game boundaries
      case InputKey::LEFT:
        if (x > 2) x -= 1;
        break;
      case InputKey::RIGHT:
        if (x + 4 < 77) x += 1;
        break;
      case InputKey::UP:
        if (y > 3) y -= 1;
        break;
      case InputKey::DOWN:
        if (y + 2 < 22) y += 1;
        break;
      }
    }
    Draw(); // The spaceship is drawn regardless if you moved it or not, if you did then it will appear in it's new position.
}

