#include "bullet.hpp"

using namespace std;

Bullet::Bullet(int _x, int _y) : x(_x), y(_y) {
    // Constructor logic (if needed)
    srand(time(nullptr));
}

Bullet::~Bullet() {
    // Destructor logic (if needed)
}

int Bullet::getX() { return x; }
int Bullet::getY() { return y; }

bool Bullet::isOut() {
    if (y <= 3) { // If the bullet reaches the top of the map
      move_cursor(x, y);
      cout << " "; // Makes the bullet invisible
      return true;
    } else {
      return false;
    }
}

void Bullet::Move() {
    move_cursor(x, y);
    cout << " ";
    y--;
    move_cursor(x, y);
    cout << "."; // The shape of the bullet
}