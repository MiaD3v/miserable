#include "../renderer.hpp"
#include "main_scene.hpp"
#include <print>
#include <SDL3/SDL.h>
#include <cstdlib>
#include <format>
#include "../deltatime.hpp"
#include "../inventory.hpp"

namespace MS = Miserable;
int getNextCountdown() {
    return 40 * (rand() % 30);
}
float getReactionWindow() {
    return 2.0;
}
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
    mBearzos(new MS::Layer),
    mBoxes(new MS::Layer),
    mShop(new MS::Layer),
    mGui(new MS::Layer),
    mJankBox(new MS::Layer),
    mTestImage("assets/BG.png", ren),
    playerImageNeutral("assets/Player Sprites/Player Char-neutral-flipped.png", ren),
    playerImageRight("assets/Player Sprites/Player Char-neutral.png", ren),
    backgroundImage("assets/Backgrounds/warehouse stage 3.png", ren),
    backgroundPeekImage("assets/Backgrounds/warehouse stage 2.png", ren),
    backgroundOpenImage("assets/Backgrounds/warehouse stage.png", ren),
    bearzosNeutralImage("assets/Stuff Bearzos Sprites/Stuff Bearzos- observing.png", ren),
    bearzosMadImage("assets/Stuff Bearzos Sprites/Stuff Bearzos- Scolding.png", ren),
    bearzosGladImage("assets/Stuff Bearzos Sprites/Stuff Bearzos- happy.png", ren),
    dollyImage("assets/programmer_art/dolly_prog_art.png", ren),
    boxImage("assets/programmer_art/box_prog_art.png", ren),
    jankBoxImage("assets/Backgrounds/SecretFG.png", ren)
    {

    mTtfEngine = TTF_CreateRendererTextEngine(ren);
    mFont = TTF_OpenFont("assets/lazy_arie.ttf", 24.0);

    mBearzos->next = mBG;
    mBG->next = mBoxes;
    mBoxes->next = mPlayerArea;
    mPlayerArea->next = mShop;
    mShop->next = mJankBox;
    mJankBox->next = mGui;

    mBearzos->rects = new MS::Rectangle{
        .x = 128, .y = 128,
        .w = 256, .h = 256,
        .r = 0, .g = 0, .b = 0, .a=0,
        .image = &bearzosNeutralImage,
    };

    mPlayerArea->rects = new MS::Rectangle;
    *mPlayerArea->rects = {
        .x = mLoadOffset, .y = 400,
        .w = 300, .h = 0,
        .r = 0x28, .g = 0x28, .b = 0x28, .a = 0xff,
        .image = &dollyImage,
    };
    mPlayerArea->rects->next = new MS::Rectangle;
    *mPlayerArea->rects->next = {
        .x = 300+mLoadOffset, .y = 275,
        .w = 150, .h = 150,
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

    mJankBox->rects = new MS::Rectangle;
    *mJankBox->rects = {
        .x = 0, .y = 0,
        .w = 512, .h = 512,
        .r = 0x28, .g = 0x28, .b = 0x28, .a = 0xff,
        .image = &jankBoxImage,
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

    mGui->rects = new MS::Rectangle {
        .x = 10, .y = 502-50,
        .w = 492, .h = 50,
        .r = 0x77, .g = 0x77, .b = 0x77, .a = 0xFF,
        .image = nullptr,
    };
    mGui->rects->next = new MS::Rectangle {
        .x = 20, .y = 502-40 - 5,
        .w = 492 - 20, .h = 50 - 10,
        .r = 0x00, .g = 0x00, .b = 0x00, .a = 0xFF,
        .image = nullptr,
    };

    mGui->rects->next->next = new MS::Rectangle {
        .x = 20, .y = 502-40 - 5,
        .w = int((492 - 20) * 0.0), .h = 50 - 10,
        .r = 0xff, .g = 0xff, .b = 0xff, .a = 0xFF,
        .image = nullptr,
    };

    mPlayerArea->rects->next->x = (mPlayerArea->rects->w * (1 - player.x)) + mPlayerArea->rects->x;

    {
        std::string moneyStr = getMoneyAsString(inventory.getMoney());
        moneyText = TTF_CreateText(mTtfEngine, mFont, moneyStr.c_str(), moneyStr.length());
    }
    mGui->next = new Layer{
        .rects = new Rectangle{
            .x = 0, .y = 0, .w = 512, .h = 50,
            .r = 0xff, .g = 0xff, .b = 0xff, .a = 0xff,
            .next = new Rectangle{
            .x = 10, .y = 10, .w = 512-20, .h = 30,
            .r = 0x00, .g = 0x00, .b = 0x00, .a = 0xff,
            .next = new Rectangle{
            .x = 10, .y = 10,
            .r = 0xff, .g = 0xff, .b = 0xff, .a = 0xff,
            .text = moneyText,
        },
        },
        },
    };

}

MS::Layer *MS::MainScene::frame() {
    int numKeys = 0;
    const bool *kbState = SDL_GetKeyboardState(&numKeys);
    pissing = kbState[SDL_SCANCODE_P];
    
    if (!pissing){
        mBladderFilled += MS::dt / 45;
    } else {
        mBladderFilled -= MS::dt / 20;
        if (mBladderFilled < 0.0) {
            mBladderFilled = 0.0;
        }
    }
    while (mBladderFilled > 1 + 1.f/45) {
        std::print(stderr, "{}", player.hp);
        mBladderFilled -= (1.f / 45);
        if (decrementHealth(player.hp)) {
            dead = true;
        }
    }
    mGui->rects->next->next->w = int((492 - 20) * mBladderFilled);
    bearzos.timeSinceBearzos += MS::dt;
    if (bearzos.timeSinceBearzos > bearzos.fluff_bearzos_countdown)
        bearzos_attack();
    float msX = -1;
    float msY = -1;
    const SDL_MouseButtonFlags msState = SDL_GetMouseState(&msX, &msY);
    float divisor = std::min(width, height);
    float offset = (std::max(width, height) - std::min(width, height))/2;
    if(width == std::max(width, height)){
        msX -= offset;
    } else{
        msY -= offset;
    }
    msX /= (float)divisor/512;
    msY /= (float)divisor/512;
    
    if (kbState[SDL_SCANCODE_A] && !pissing) {
        mPlayerArea->rects->next->image = &playerImageNeutral;
        player.x += MS::dt;
        if (player.x > 1) player.x = 1;
        mPlayerArea->rects->next->x = (mPlayerArea->rects->w * (1 - player.x)) + mPlayerArea->rects->x;
    }

    if (kbState[SDL_SCANCODE_D] && !pissing) {
        mPlayerArea->rects->next->image = &playerImageRight;
        player.x -= MS::dt;
        if (player.x < 0) player.x = 0;
        mPlayerArea->rects->next->x = (mPlayerArea->rects->w * (1 - player.x)) + mPlayerArea->rects->x;
    }

    if (kbState[SDL_SCANCODE_SPACE]) {
        if (player.x <= 0.1) { // loading
            mLoaded += MS::dt / loadTime;
            if (mLoaded > 1) mLoaded = 1;
        } else if (player.x >= 0.9) { // un-loading
            float oldLoadScore = mLoaded;
            mLoaded -= MS::dt / loadTime;

            float dif = oldLoadScore - mLoaded;

            inventory.give_money(dif * 500);

            if (mLoaded < 0) mLoaded = 0;
        }
        std::print(stderr, "loaded: {}\n", mLoaded);
    }

    if (msState == SDL_BUTTON_LEFT && !held_down){
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

    {
        TTF_DestroyText(mGui->next->rects->next->next->text);
        std::string moneyStr = getMoneyAsString(inventory.getMoney());
        moneyText = TTF_CreateText(mTtfEngine, mFont, moneyStr.c_str(), moneyStr.length());
        mGui->next->rects->next->next->text = moneyText;
    }

    return mBearzos;
}

void MS::MainScene::Resize(int w, int h) {
    width = w;
    height = h;

}

bool MS::MainScene::IsRectClicked(float msX, float msY, MS::Rectangle *button){
    return msX > button->x && msX < button->x + button->w && msY > button->y && msY < button->y + button->h;
}

void MS::MainScene::bearzos_attack() {
    static float reactionWindow = 2.0;
    if (bearzos.bearzosAttackStage == 0) {
        bearzos.bearzosAttackStage = 1;
        reactionWindow = getReactionWindow();
        mBG->rects->image = &backgroundPeekImage;
    } else if (bearzos.bearzosAttackStage == 1 && bearzos.timeSinceBearzos - bearzos.fluff_bearzos_countdown > reactionWindow) {
        bearzos.bearzosAttackStage = 2; 
        mBG->rects->image = &backgroundOpenImage;
        bearzos.pissing_seen = pissing;
    } else if (bearzos.bearzosAttackStage == 2 && bearzos.timeSinceBearzos - bearzos.fluff_bearzos_countdown > reactionWindow + 1.) {
        if (bearzos.pissing_seen) {
            bearzos.bearzosAttackStage = 3;
            mBearzos->rects->image = &bearzosMadImage;
            for (int i = 0; i < 20; i++) {
                if (decrementHealth(player.hp))
                    std::print("YOU DIED!");
            }
        } else {
            bearzos.bearzosAttackStage = 4;
            mBearzos->rects->image = &bearzosGladImage;
        }
    } else if ((bearzos.bearzosAttackStage == 3 || bearzos.bearzosAttackStage == 4)&& bearzos.timeSinceBearzos - bearzos.fluff_bearzos_countdown > reactionWindow + 2.) {
        bearzos.bearzosAttackStage = 5;
        mBG->rects->image = &backgroundPeekImage;
        mBearzos->rects->image = &bearzosNeutralImage;
    } else if (bearzos.bearzosAttackStage == 5 && bearzos.timeSinceBearzos - bearzos.fluff_bearzos_countdown > reactionWindow + 2.5){
        mBG->rects->image = &backgroundImage;
        bearzos.bearzosAttackStage = 0;
        bearzos.timeSinceBearzos = 0.0;
        bearzos.fluff_bearzos_countdown = (float)getNextCountdown();
    }
}

std::string MS::MainScene::getMoneyAsString(uint64_t money) {
    uint64_t dollars = money / 100;
    uint64_t cents = money % 100;

    // Don't worry about it!
    return std::format("${}.{}{}", dollars, cents/10, cents % 10);

}

MS::MainScene::~MainScene() {

    TTF_CloseFont(mFont);
    TTF_DestroyRendererTextEngine(mTtfEngine);

    delete mPlayerArea;
    delete mBG;
    delete mBearzos;
    delete mBoxes;
    delete mShop;
}

