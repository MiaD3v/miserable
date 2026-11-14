#include <SDL3/SDL.h>

#include "miserable.hpp"
#include "panic.hpp"

namespace MS = Miserable;

const char *WINDOW_NAME = "Miserable";

constexpr int WIDTH  = 512;
constexpr int HEIGHT = 512;

MS::Game::Game() {
    if (!SDL_Init(SDL_INIT_VIDEO)) PANIC("Failed to initialize SDL3!");

    if (!SDL_CreateWindowAndRenderer(WINDOW_NAME,
                                     WIDTH, HEIGHT,
                                     SDL_WINDOW_RESIZABLE,
                                     &mWindow, &mRenderer))
        PANIC("Failed to create window and renderer!");

    mRendererEngine = MS::Renderer(mWindow, mRenderer, WIDTH, HEIGHT);

    mRendererEngine.render(nullptr);

}

int MS::Game::run() {

    SDL_Event event;
    bool running = true;
    while (running) {
        if (SDL_PollEvent(&event)) switch (event.type) {
            case SDL_EVENT_QUIT: running = false; continue;
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED: running = false; continue;
        }

        MS::Rectangle testRect = {
            .x = 0,
            .y = 0,
            .w = 50,
            .h = 50,
            .r = 0x28, .g = 0x28, .b = 0x28, .a = 255,
        };

        MS::Layer testLayer = {
            .rects = &testRect,
        };

        mRendererEngine.render(&testLayer);

    }

    return 0;
}

MS::Game::~Game() {
    ;
}

