#include <cstdlib>
#include <iostream>
#include <cstdlib>
#include <SDL3/SDL.h>

#include "miserable.hpp"
#include "scene.hpp"

namespace MS = Miserable;

int main(void) {

    MS::Game game;
    MS::Scene scene;
    srand((int)SDL_GetTicksNS());
    game.run();
    return 0;
}

