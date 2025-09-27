//  * Space Shootter - a simple C++ game for Linux terminal
//  * developed by Hantaro1917 - 09/2025

#include "game_logic.hpp"
#include "space_ship.hpp"
#include "cursor_input.hpp"
#include <iostream>
#include <clocale>
#include <cstdlib>
#include <ctime>
#include <string>
#include <csignal>

using namespace std;    

void cleanup(int signal) {
    restoreTerminalBlocking();
    showCursor();
    exit(signal);
}

void showInfo(const string& arg, const string& programName) {
    if (arg == "-h" || arg == "--help") {
        cout << "Pacman Game - A simple terminal based Pacman implementation" << endl;
        cout << "Usage: " << programName << " [option]" << endl;
        cout << "Options: " << endl;
        cout << "  -h, --help   Show this help message" << endl;
        cout << "  -v, --version Show version information" << endl;
        cout << "\nControls:\n";
        cout << "  W/S or Up/Down - Move Paddle up/down\n";
        cout << "  A/D or Left/Right - Move Paddle left/right\n";
        cout << "  Q - Quit to menu\n";
        cout << "  R - Rotate\n";
    } else if (arg == "-v" || arg == "--version") {
        cout << "Pacman Game v1.0.0\n";
        cout << "A clean, object-oriented implementation of the classic Pacman game\n";
    } else {
        cout << "Unknown option: " << arg << "\n";
        cout << "Use -h or --help for usage information\n";
    }
}

int main () {

    setTerminalNonBlocking();   // if you use this
    srand((unsigned)time(nullptr));

    while (true) {
        Game game;            // fresh game state each run
        bool replay = game.run(); // true => restart, false => exit

        if (!replay) break;   // quit chosen

        // user chose replay: clear screen & loop to create a new Game
        clearTerminal();
        // optional: short pause to avoid instant restart
        this_thread::sleep_for(chrono::milliseconds(150));
    }

    // cleanup
    restoreTerminalBlocking(); // or reset terminal mode if you set it earlier
    return 0;
}
