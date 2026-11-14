#include "../renderer.hpp"
#include "main_scene.hpp"
#include <print>

namespace MS = Miserable;

MS::MainScene::MainScene() : mBG(new MS::Layer) {
    mBG->rects = new MS::Rectangle;
    *mBG->rects = {
        .x = 0, .y = 0,
        .w = 50, .h = 50,
        .r = 0x28, .g = 0x28, .b = 0x28, .a = 0xff,
    };
}

MS::Layer *MS::MainScene::frame() {
    int numKeys = 0;
    const bool *kbState = SDL_GetKeyboardState(&numKeys);

    if (kbState[SDL_SCANCODE_A]) {
        std::print(stderr, "A\n");
        --mBG->rects->x;
    }

    if (kbState[SDL_SCANCODE_D]) {
        std::print(stderr, "D\n");
        ++mBG->rects->x;
    }


    return mBG;
}

void MS::MainScene::Resize(int w, int h) {
    ;
}

MS::MainScene::~MainScene() {

    for (MS::Layer *lay = mBG; lay != nullptr;) {
        MS::Layer *next_lay = lay->next;
        for (MS::Rectangle *rect; rect != nullptr;) {
            MS::Rectangle *next_rect = rect->next;
            delete rect;
            rect = next_rect;
        }
        delete lay;
        lay = next_lay;
    }
}

