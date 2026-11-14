#include <SDL3/SDL.h>

#include "miserable.hpp"
#include "panic.hpp"

namespace MS = Miserable;

const char *WINDOW_NAME = "Miserable";

constexpr int WIDTH  = 512;
constexpr int HEIGHT = 512;

MS::Game::Game() {
    if (!SDL_Init(SDL_INIT_VIDEO)) PANIC("Failed to initialize SDL3!");
    mWindow =
        SDL_CreateWindow(WINDOW_NAME, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    if (!SDL_CreateWindowAndRenderer(WINDOW_NAME,
                                     WIDTH, HEIGHT,
                                     SDL_WINDOW_RESIZABLE,
                                     &mWindow, &mRenderer))
        PANIC("Failed to create window and renderer!");
    SDL_FRect rect = {
        .x = 0,
        .y = 0,
        .w = 500,
        .h = 500,
    };
    if (!SDL_RenderClear(mRenderer)) PANIC("Failed to clear!");
    if (!SDL_RenderPresent(mRenderer))
        PANIC("Failed to present rendered image!");
}

int MS::Game::run() {

    SDL_Event event;
    for (;;) {
        if (SDL_PollEvent(&event)) switch (event.type) {
            case SDL_EVENT_QUIT: goto break_outer;
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED: goto break_outer;
        }

        if (!SDL_RenderClear(mRenderer)) PANIC("Failed to clear!");
        if (!SDL_RenderPresent(mRenderer))
            PANIC("Failed to present rendered image!");
    }
break_outer:

    return 0;
}

MS::Game::~Game() {
    ;
}

