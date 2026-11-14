#include <cstdlib>
#include <iostream>

#include <SDL3/SDL.h>

#include "miserable.hpp"

namespace MS = Miserable;

int main(void) {

    MS::Game game;
    game.run();

    return 0;
}

