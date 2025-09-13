#include "game_logic.hpp"
#include "space_ship.hpp"
#include "cursor_input.hpp"
#include "bullet.hpp"
#include "asteroid.hpp"
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
#include <list>

using namespace std;

void Game::run() { // The main function of the game

    clearTerminal();
    hideCursor();
    WelcomeMessage();
    getch();
    DrawGameLimits();

    // Use plural names to match the rest of the file
    std::list<Bullet*> Bullets;             // dynamic list for bullets
    std::list<Bullet*>::iterator bullet_it; // iterator for bullets

    std::list<Asteroid*> Asteroids;             // list for asteroids
    std::list<Asteroid*>::iterator asteroid_it; // iterator for asteroids

    // initialize asteroids
    for (int i = 0; i < 10; i++) {
        Asteroids.push_back(new Asteroid(rand() % 78 + 1, rand() % 4 + 3));
    }

    SpaceShip ss = SpaceShip(40, 20);
    int score = 0;

    using namespace std::chrono_literals;

    while (!ss.isDead() && score != 100) {
        if (kbhit()) {
            char key = getch();
            if (key == ' ') {
                Bullets.push_back(new Bullet(ss.getX() + 2, ss.getY() - 1)); // use getX/getY if those are your accessors
            }
        }

        // bullets update + erase
        for (bullet_it = Bullets.begin(); bullet_it != Bullets.end(); ) {
            (*bullet_it)->Move();
            if ((*bullet_it)->isOut()) {
                delete *bullet_it;
                bullet_it = Bullets.erase(bullet_it); // erase returns next iterator
            } else {
                ++bullet_it;
            }
        }

        // asteroid -> collision with ship and movement
        for (asteroid_it = Asteroids.begin(); asteroid_it != Asteroids.end(); ++asteroid_it) {
            (*asteroid_it)->Collision(ss);
        }

        // asteroid-bullet collisions
        for (asteroid_it = Asteroids.begin(); asteroid_it != Asteroids.end(); ++asteroid_it) {
            for (bullet_it = Bullets.begin(); bullet_it != Bullets.end(); ) {
                // use whichever getters your classes provide: here I assume getX/getY.
                int astX = (*asteroid_it)->getX();
                int astY = (*asteroid_it)->getY();
                int bulX = (*bullet_it)->getX();
                int bulY = (*bullet_it)->getY();

                if ((astX == bulX) && ((astY == bulY) || (astY + 1 == bulY))) {
                    move_cursor(bulX, bulY); printf(" ");
                    move_cursor(astX, astY); printf("X"); printf(" ");
                    // remove bullet and asteroid
                    delete *bullet_it;
                    bullet_it = Bullets.erase(bullet_it);

                    delete *asteroid_it;
                    asteroid_it = Asteroids.erase(asteroid_it);

                    // spawn a replacement asteroid
                    Asteroids.push_back(new Asteroid(rand() % 78 + 1, rand() % 4 + 3));
                    score += 10;
                    // break out of inner loop and continue scanning next asteroid
                    break;
                } else {
                    ++bullet_it;
                }
            } // bullets loop
        } // asteroids loop

        ss.Move();
        move_cursor(56, 1);
        printf("%d", score);

        // sleep 30 milliseconds
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }

    sleep(5000);
    SpecialMessage(); // Surprise
    sleep(5000);
}

Game::Game() : ship(40, 20), bullet(nullptr), asteroid(nullptr), score(0) {
    srand(time(nullptr));
    setTerminalNonBlocking();
}

Game::~Game() {
    restoreTerminalBlocking();
    showCursor();
    clearTerminal();
}

void Game::WelcomeMessage() { // Displays a welcome message
    DrawWindowFrame(20, 8, 60, 16);
    move_cursor(30, 10);
    cout << "WELCOME TO THE GAME!";
    move_cursor(22, 12);
    cout << "Press ENTER to start or ESC to exit.";
    move_cursor(1, 24);
    cout << flush;
    InputKey key;
    do {
        key = getInputKey();
        this_thread::sleep_for(chrono::milliseconds(100));
    } while (key != InputKey::ENTER && key != InputKey::ESC);
    if (key == InputKey::ESC) {
        exit(0);
    }
    DrawWhiteSpace(20, 8, 60, 16); // Clear the welcome message
}


void Game::DrawWhiteSpace(int ax, int ay, int bx, int by) { // To clean a certain space in the terminal
    for (int i = ax; i < bx; i++) {
        for (int j = ay; j < by; j++) {
            move_cursor(i, j);
            cout << " ";
        }
    }
}

void Game::DrawWindowFrame(int ax, int ay, int bx, int by) { // This will draw a rectangular frame defined by two points
    DrawWhiteSpace(ax, ay, bx, by);
    for (int i = ax; i < bx; i++) {
        move_cursor(i, ay);
        cout << (char)205;
        move_cursor(i, by);
        cout << (char)205;
    }
    for (int i = ay; i < by; i++) {
        move_cursor(ax, i);
        cout << (char)186;
        move_cursor(bx, i);
        cout << (char)186;
    }
    move_cursor(ax, ay);
    cout << (char)201;
    move_cursor(bx, ay);
    cout << (char)187;
    move_cursor(ax, by);
    cout << (char)200;
    move_cursor(bx, by);
    cout << (char)188;
}

void Game::DrawGameLimits() { // Draws the limits of the game area and the labels for HP and energy
    DrawWindowFrame(1, 2, 79, 23); // The game area
    move_cursor(2, 1);
    cout << "HP: "; // Label for HP
    move_cursor(16, 1);
    cout << "ENERGY: "; // Label for energy points
    move_cursor(50, 1);
    cout << "SCORE:";
}

void Game::GameOverVictoryMessage() { // Displays a victory message
    int a_x = 25;
    int a_y = 8;
    int b_x = 55;
    int b_y = 16;
    DrawWindowFrame(a_x, a_y, b_x, b_y);
    move_cursor(a_x + 1, a_y + 2);
    cout << "      VICTORY!!!";
    // move_cursor(a_x + 1, a_y + 4);
    // cout << "   You reached 100 points!";
    move_cursor(a_x + 1, a_y + 6);
    cout << " Press any key to continue";
    move_cursor(1, 24);
    cout << flush;
    while (getInputKey() == InputKey::NONE) {
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void Game::SpecialMessage() { // A special message for your special needs
    DrawWhiteSpace(1, 1, 80, 24);
    move_cursor(30, 11);
    cout << "Thanks for playing! :3";
}