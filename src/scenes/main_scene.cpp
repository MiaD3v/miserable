#include "../renderer.hpp"
#include "main_scene.hpp"
#include <print>
#include <SDL3/SDL.h>
#include "../deltatime.hpp"

namespace MS = Miserable;

MS::MainScene::MainScene(SDL_Renderer *ren)
    : mBG(new MS::Layer)
    , mTestImage("assets/test.png", ren) {

    mBG->rects = new MS::Rectangle;
    *mBG->rects = {
        .x = 0, .y = 0,
        .w = 50, .h = 50,
        .r = 0x28, .g = 0x28, .b = 0x28, .a = 0xff,
        .image = &mTestImage,
    };

}

MS::Layer *MS::MainScene::frame() {
    int numKeys = 0;
    const bool *kbState = SDL_GetKeyboardState(&numKeys);

    if (kbState[SDL_SCANCODE_A]) {
        mBG->rects->x -= MS::dt * 1500;
    }

    if (kbState[SDL_SCANCODE_D]) {
        mBG->rects->x += MS::dt * 1500;
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

