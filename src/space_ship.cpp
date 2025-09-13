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
    // srand(time(nullptr));

}

SpaceShip::~SpaceShip() {
    // Destructor logic (if needed)
    // restoreTerminalBlocking();
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

    // Draw hearts 
    setTextColor(RED);
    for (int i = 0; i < hp; i++) {
      move_cursor(5 + i, 1);
      cout << HEART_SOLID;
    }
    resetTextColor();

    // Draw energy points
    move_cursor(23, 1);
    cout << "     ";
    setTextColor(GREEN);
    for (int i = 0; i < energy; i++) {
      move_cursor(23 + i, 1);
      cout << BLOCK_FULL << " ";
    }
    resetTextColor();
}

void SpaceShip::Draw() { // This is our spaceship
    // clearScreen();
     // Row 0:   "  ▲  "
    move_cursor(x, y);
    cout << "  " << TRIANGLE_UP << "  ";

    // Row 1:   " ◀ █ ▶ "
    move_cursor(x, y + 1);
    cout  << " " << TRIANGLE_LEFT << BLOCK_FULL << TRIANGLE_RIGHT << " ";

    // Row 2:   "◀ ▴ ▷" (stylized base)
    move_cursor(x, y + 2);
    cout << TRIANGLE_LEFT << " " << TRIANGLE_UP << " " << TRIANGLE_RIGHT;
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
      usleep(10000);
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
    usleep(10000);
    if (hp > 0) { // If you still have a heart or more
      energy = 5;
    } else { // If you don't
      imDead = true;
    }
}

void SpaceShip::Move() { // The main function of the spaceship
    if (kbhit()) { // If you move the spaceship
      Erase(); // Look I'm invisible
      InputKey key = getInputKey();  // What did you type?
      switch (key) { // Checks if the spaceship won't leave the game boundaries
        case 'A': case 'a': case InputKey::LEFT: // Left arrow or 'A' key
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
        default:
            break;
      }
    }
    // usleep(10000);
    Draw(); // The spaceship is drawn regardless if you moved it or not, if you did then it will appear in it's new position.
}

