#include <iostream>
#include "game.h"

// terain size 28x31

int main() {
    Game *g = new Game();
    g->startRenderLoop();
    return 0;
}