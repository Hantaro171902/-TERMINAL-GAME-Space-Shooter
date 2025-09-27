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
      // Clear hearts area
    move_cursor(5, 1);
    cout << "     ";            // 5 cols cleared for hearts

    // Draw hearts
    setTextColor(RED);
    for (int i = 0; i < hp; ++i) {
        move_cursor(5 + i, 1);
        cout << HEART_SOLID;
    }
    resetTextColor();

    // Clear energy area (reserve space for up to 5 blocks spaced by 2 => ~11 cols)
    move_cursor(23, 1);
    cout << "           ";     // 11 spaces

    // Draw energy blocks with 2-column spacing (so wide glyphs won't collide)
    setTextColor(GREEN);
    for (int i = 0; i < energy; ++i) {
        move_cursor(23 + i * 2, 1); // step by 2
        cout << BLOCK_FULL;
    }
    resetTextColor();

    cout << flush;
}

void SpaceShip::Draw() { // This is our spaceship
    // clearScreen();
    // Row 0:   "  ▲  "
    setTextColor(YELLOW);
    move_cursor(x, y);
    cout << "  " << "A" << "  ";

    // Row 1:   " ◀ █ ▶ "
    move_cursor(x, y + 1);
    cout  << TRIANGLE_LEFT << "[" << BLOCK_FULL << "]" << TRIANGLE_RIGHT;

    // Row 2:   "◀ ▴ ▷" (stylized base)
    move_cursor(x, y + 2);
    cout << BLOCK_LEFT << " " << BLOCK_HALF << " " << BLOCK_RIGHT;

     // Row 2:   " ▼  ▼ " (stylized base)
    move_cursor(x, y + 2);
    cout << " ^" << " " << "^  ";
    resetTextColor();
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
      printf("  * ");
      move_cursor(x, y + 1);
      printf("  * ");
      move_cursor(x, y + 2);
      printf("*****");
      this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void SpaceShip::Explosion() { // When you lose a heart :c
    hp--;
    Erase();
    move_cursor(x, y);
    cout << ("  * ");
    move_cursor(x, y + 1);
    cout << ("  * ");
    move_cursor(x, y + 2);
    cout << ("*****");
    this_thread::sleep_for(chrono::milliseconds(100));
    Erase();
    move_cursor(x, y);
    cout << (" * * ");
    move_cursor(x, y + 1);
    cout << ("* * *");
    move_cursor(x, y + 2);
    cout << (" * * ");
    this_thread::sleep_for(chrono::milliseconds(100));
    Erase();
    move_cursor(x, y);
    cout << ("* *");
    move_cursor(x, y + 1);
    cout << (" * * ");
    move_cursor(x, y + 2);
    cout << ("* * *");
    this_thread::sleep_for(chrono::milliseconds(100));
    if (hp > 0) { // If you still have a heart or more
      energy = 5;
    } else { // If you don't
      imDead = true;
    }
}

void SpaceShip::Move(InputKey key) { // The main function of the spaceship
  // If no key pressed, just redraw the ship (keeps animation / display stable)
    if (key == InputKey::NONE) {
        Draw();
        return;
    }

    Erase(); // clear old

    switch (key) {
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
        case InputKey::SPACE:
            // do nothing here — shooting handled by Game (keeps separation of concerns)
            break;
        default:
            break;
    }
    Draw();
}
