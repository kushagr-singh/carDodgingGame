#include "Game.h"
#include <ctime>
#include <cstdlib>

int main() {
    // Initialize random seed
    srand(static_cast<unsigned>(time(nullptr)));
    
    // Instantiate and run the game
    Game game;
    game.run();
    
    return 0;
}