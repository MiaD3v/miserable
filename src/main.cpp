#include <cstdlib>
#include <iostream>

#include <SDL3/SDL.h>

#include "miserable.hpp"
#include "scene.hpp"

namespace MS = Miserable;

int main(void) {

    MS::Game game;
    MS::Scene scene;
    game.run();
    return 0;
}

