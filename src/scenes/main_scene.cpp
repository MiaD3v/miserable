#include "../renderer.hpp"
#include "main_scene.hpp"
#include <print>
#include <SDL3/SDL.h>
#include "../deltatime.hpp"

namespace MS = Miserable;

static bool decrementHealth(int &hp) {
    hp--;
    if (hp <= 0) {
        hp = 0;
        return true;
    }
    return false;
}

MS::MainScene::MainScene(SDL_Renderer *ren) :
    mPlayerArea(new MS::Layer),
    mBG(new MS::Layer),
    mBoxes(new MS::Layer),
    mShop(new MS::Layer),
    mTestImage("assets/BG.png", ren),
    playerImageNeutral("assets/Player Sprites/Player Char-neutral.png", ren),
    backgroundImage("assets/Backgrounds/warehouse stage 3.png", ren),
    dollyImage("assets/programmer_art/dolly_prog_art.png", ren),
    boxImage("assets/programmer_art/box_prog_art.png", ren)
    {

    // mTtfEngine = TTF_CreateRendererTextEngine(ren);
    // mFont = TTF_OpenFont("assets/lazy_arie.ttf", 24.0);
    // mTtfText = TTF_CreateText(mTtfEngine, mFont, "Test Text", sizeof("Test Text") - 1);

    mBG->next = mBoxes;
    mBoxes->next = mPlayerArea;
    mPlayerArea->next = mShop;

    mPlayerArea->rects = new MS::Rectangle;
    *mPlayerArea->rects = {
        .x = mLoadOffset, .y = 400,
        .w = 350, .h = 0,
        .r = 0x28, .g = 0x28, .b = 0x28, .a = 0xff,
        .image = &dollyImage,
    };
    mPlayerArea->rects->next = new MS::Rectangle;
    *mPlayerArea->rects->next = {
        .x = 300+mLoadOffset, .y = 375,
        .w = 50, .h = 50,
        .r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xff,
        .image = &playerImageNeutral,
    };

    mBG->rects = new MS::Rectangle;
    *mBG->rects = {
        .x = 0, .y = 0,
        .w = 512, .h = 512,
        .r = 0x28, .g = 0x28, .b = 0x28, .a = 0xff,
        .image = &backgroundImage,
    };

    mBoxes->rects = new MS::Rectangle;
    *mBoxes->rects = {
        .x = 50, .y = 250,
        .w = 100, .h = 100,
        .r = 0x28, .g = 0x28, .b = 0x28, .a = 0xff,
        .image = &boxImage,
    };
    mBoxes->rects->next = new MS::Rectangle;
    *mBoxes->rects->next = {
        .x = 450, .y = 250,
        .w = 100, .h = 100,
        .r = 0x28, .g = 0x28, .b = 0x28, .a = 0xff,
        .image = &boxImage,
    };

    unload_doll_button = new MS::Rectangle;
    *unload_doll_button = {
        .x = 25, .y = 50,
        .w = 100, .h = 100,
        .r = 0x00, .g = 0xFF, .b = 0xFF, .a = 0x5F,
        .image = &mTestImage,
    };
    mShop->rects = unload_doll_button;

    upgrade_button = new MS::Rectangle;
    *upgrade_button = {
        .x = 150, .y = 50,
        .w = 100, .h = 100,
        .r = 0x00, .g = 0xFF, .b = 0xFF, .a = 0x5F,
        .image = &mTestImage,
    };
    mShop->rects->next = upgrade_button;

    bottle_button = new MS::Rectangle;

    *bottle_button = {

        .x = 275, .y = 50,
        .w = 100, .h = 100,
        .r = 0x00, .g = 0xFF, .b = 0xFF, .a = 0x5F,
        .image = &mTestImage,
    };
    mShop->rects->next->next = bottle_button;

    load_doll_button = new MS::Rectangle;
    *load_doll_button = {
        .x = 400, .y = 50,
        .w = 100, .h = 100,
        .r = 0x00, .g = 0xFF, .b = 0xFF, .a = 0x5F,
        .image = &mTestImage,
    };
    mShop->rects->next->next->next = load_doll_button;

    mPlayerArea->rects->next->x = (mPlayerArea->rects->w * (1 - player.x)) + mPlayerArea->rects->x;
    // mPlayerArea->rects->next->image = nullptr;
    // mPlayerArea->rects->next->r = 0x28;
    // mPlayerArea->rects->next->g = 0x28;
    // mPlayerArea->rects->next->b = 0x28;
    // mPlayerArea->rects->next->a = 0xff;
    // mPlayerArea->rects->next->text = mTtfText;
}

MS::Layer *MS::MainScene::frame() {

    mBladderFilled += MS::dt / 45;
    while (mBladderFilled > 1 + 1.f/45) {
        mBladderFilled -= (1.f / 45);
        if (decrementHealth(player.hp)) {
            std::print("YOU DIED!\n");
        }
        std::print(stderr, "hp: {}\n", player.hp);
    }

    int numKeys = 0;
    float msX = -1;
    float msY = -1;
    const bool *kbState = SDL_GetKeyboardState(&numKeys);
    const SDL_MouseButtonFlags msState = SDL_GetMouseState(&msX, &msY);
    float divisor = std::min(width, height);
    float offset = (std::max(width, height) - std::min(width, height))/2;
    msX /= (float)divisor/512;
    msY /= (float)divisor/512;
    if(width == std::max(width, height)){
        msX -= offset;
    } else{
        msY -= offset;
    }
    if (kbState[SDL_SCANCODE_A]) {
        player.x += MS::dt;
        if (player.x > 1) player.x = 1;
        mPlayerArea->rects->next->x = (mPlayerArea->rects->w * (1 - player.x)) + mPlayerArea->rects->x;
    }

    if (kbState[SDL_SCANCODE_D]) {
        player.x -= MS::dt;
        if (player.x < 0) player.x = 0;
        mPlayerArea->rects->next->x = (mPlayerArea->rects->w * (1 - player.x)) + mPlayerArea->rects->x;
    }
    
    if (msState == SDL_BUTTON_LEFT && !held_down){
        std::print(stderr, "{},{}\n", msX, msY);
        std::print(stderr, "{},{}\n", width, height);
        std::print(stderr, "{},{}\n", divisor, offset);
        if(IsRectClicked(msX, msY, unload_doll_button)){
            if(inventory.Buy_Unload_Doll()){
                std::print(stderr, "bought doll\n");
            } else {
                std::print(stderr, "Not Enough Money");
            };
        }
        if(IsRectClicked(msX, msY, bottle_button)){
            if(inventory.Buy_Bottle()){
                std::print(stderr, "{}", inventory.bottleCount);
            } else {
                std::print(stderr, "Not Enough Money");
            };
        }
        if(IsRectClicked(msX, msY, upgrade_button)){
            if(inventory.Upgrade_Dolly()){
                std::print(stderr, "{}", inventory.dollyLevel);
            } else {
                std::print(stderr, "Not Enough Money");
            };
        }
        if(IsRectClicked(msX, msY, load_doll_button)){
            if(inventory.Buy_Load_Doll()){
                std::print(stderr, "Buy Doll");
            } else {
                std::print(stderr, "Not Enough Money");
            };
        }
        held_down = true;
    }
    if (!msState){
        held_down = false;
    }

    return mBG;
}

void MS::MainScene::Resize(int w, int h) {
    width = w;
    height = h;

}

bool MS::MainScene::IsRectClicked(float msX, float msY, MS::Rectangle *button){
    return msX > button->x && msX < button->x + button->w && msY > button->y && msY < button->y + button->h;
}

MS::MainScene::~MainScene() {

    // TTF_CloseFont(mFont);
    // TTF_DestroyText(mTtfText);
    // TTF_DestroyRendererTextEngine(mTtfEngine);

    delete mPlayerArea;
    delete mBG;
    delete mBoxes;
    delete mShop;
}   

