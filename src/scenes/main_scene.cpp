#include "../renderer.hpp"
#include "main_scene.hpp"
#include <SDL3/SDL_scancode.h>
#include <print>
#include <SDL3/SDL.h>
#include <cstdlib>
#include <cmath>
#include <format>
#include "../deltatime.hpp"
#include "../inventory.hpp"
#include <cmath>

namespace MS = Miserable;
int getNextCountdown() {
    return 10 * (((unsigned) rand()) % 3);
}
float MS::MainScene::getReactionWindow() {
    return 0.5 + 1.5 / (1.0 + exp((frameCount - 90.0) / 20.0));
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
    upgradeImage("assets/Buttons/upgrade.png", ren),
    dollImage("assets/Buttons/Robot- grabbing box.png", ren),
    udollImage("assets/Buttons/Doll- holding box.png", ren),
    bottleImage("assets/Buttons/Lint Roller.png", ren),
    jankBoxImage("assets/Backgrounds/SecretFG.png", ren)
    {

    mTtfEngine = TTF_CreateRendererTextEngine(ren);
    mFont = TTF_OpenFont("assets/lazy_arie.ttf", 24.0);

    mBearzos->next = mBG;
    mBG->next = mPlayerArea;
    mPlayerArea->next = mBoxes;
    mBoxes->next = mShop;
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
        .x = 300+mLoadOffset, .y = 280 + 5*sin(SDL_GetTicks() / 200.0),
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
        .w = 70, .h = 70,
        .r = 0x00, .g = 0xFF, .b = 0xFF, .a = 0x5F,
        .image = &udollImage,
    };
    mShop->rects = unload_doll_button;

    upgrade_button = new MS::Rectangle;
    *upgrade_button = {
        .x = 155, .y = 50,
        .w = 70, .h = 70,
        .r = 0x00, .g = 0xFF, .b = 0xFF, .a = 0x5F,
        .image = &upgradeImage,
    };
    mShop->rects->next = upgrade_button;

    bottle_button = new MS::Rectangle;

    *bottle_button = {

        .x = 285, .y = 50,
        .w = 70, .h = 70,
        .r = 0x28, .g = 0x28, .b = 0x28, .a = 0xFF,
        .image = &bottleImage,
    };
    mShop->rects->next->next = bottle_button;

    load_doll_button = new MS::Rectangle;
    *load_doll_button = {
        .x = 512 - 95, .y = 50,
        .w = 70, .h = 70,
        .r = 0x28, .g = 0x28, .b = 0x28, .a = 0xFF,
        .image = &dollImage,
    };
    mShop->rects->next->next->next = load_doll_button;

    udollText = TTF_CreateText(mTtfEngine, mFont, "0", sizeof("0") - 1);
    udoll_display = new MS::Rectangle;
    *udoll_display = {
        .x = 80, .y = 118,
        .w = 100, .h = 100,
        .r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xfF,
        .image = nullptr, .text = udollText,
    };
    mShop->rects->next->next->next->next = udoll_display;
    
    ldollText = TTF_CreateText(mTtfEngine, mFont, "0", sizeof("0") - 1);
    ldoll_display = new MS::Rectangle;
    *ldoll_display = {
        .x = 512-40, .y = 118,
        .w = 1, .h = 1,
        .r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFF,
        .image = nullptr, .text = ldollText,
    };
    mShop->rects->next->next->next->next->next = ldoll_display;

    levelText = TTF_CreateText(mTtfEngine, mFont, "1", sizeof("1") - 1);
    level_display = new MS::Rectangle;
    *level_display = {
        .x = 210, .y = 118,
        .w = 100, .h = 100,
        .r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFF,
        .image = nullptr, .text = levelText,
    };
    mShop->rects->next->next->next->next->next->next = level_display;

    bottleText = TTF_CreateText(mTtfEngine, mFont, "0", sizeof("0") - 1);
    bottle_display = new MS::Rectangle;
    *bottle_display = {
        .x = 340, .y = 118,
        .w = 100, .h = 100,
        .r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFF,
        .image = nullptr, .text = bottleText,
    };
    mShop->rects->next->next->next->next->next->next->next = bottle_display;

    mGui->rects = new MS::Rectangle {
        .x = 10, .y = 502-50,
        .w = 196, .h = 50,
        .r = 0x77, .g = 0x77, .b = 0x77, .a = 0xFF,
        .image = nullptr,
    };
    mGui->rects->next = new MS::Rectangle {
        .x = 20, .y = 502-40 - 5,
        .w = 196 - 20, .h = 50 - 10,
        .r = 0x00, .g = 0x00, .b = 0x00, .a = 0xFF,
        .image = nullptr,
    };

    mGui->rects->next->next = new MS::Rectangle {
        .x = 20, .y = 502-40 - 5,
        .w = int((196 - 20) * 0.0), .h = 50 - 10,
        .r = 0xff, .g = 0xff, .b = 0xff, .a = 0xFF,
        .image = nullptr,
    };

    load_bar_bg = new MS::Rectangle;
    *load_bar_bg = {
        .x = 502-196, .y = 502 - 50,
        .w = 196, .h = 50,
        .r = 0x77, .g = 0x77, .b = 0x77, .a = 0x5F,
        .image = nullptr,
    };
    mGui->rects->next->next->next = load_bar_bg;

    load_bar_mg = new MS::Rectangle;
    *load_bar_mg = {
        .x = 492-176, .y =  502 - 45,
        .w = 196-20, .h = 40,
        .r = 0x00, .g = 0x00, .b = 0x00, .a = 0x5F,
        .image = nullptr,
    };
    mGui->rects->next->next->next->next = load_bar_mg;

    load_bar_fg = new MS::Rectangle;
    *load_bar_fg = {
        .x = 492-176, .y =  502 - 45,
        .w = 0, .h = 40,
        .r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x5F,
        .image = nullptr,
    };
    mGui->rects->next->next->next->next->next = load_bar_fg;

    hpText = TTF_CreateText(mTtfEngine, mFont, "100", sizeof("100") - 1);
    hp_display = new MS::Rectangle;
    *hp_display = {
        .x = 236, .y =  502 - 45,
        .w = 1, .h = 1,
        .r = 0x00, .g = 0x00, .b = 0x00, .a = 0xFF,
        .image = nullptr, .text = hpText,
    };
    mGui->rects->next->next->next->next->next->next = hp_display;
    

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
    frameCount += MS::dt;
    int numKeys = 0;
    const bool *kbState = SDL_GetKeyboardState(&numKeys);
    pissing = kbState[SDL_SCANCODE_P];

    if(!inventory.unload_dolls.empty()){
        if(inventory.unload_dolls.front() + 30 < frameCount){
            inventory.unload_dolls.pop();
            unloadMult = pow(0.85, inventory.unload_dolls.size());
            TTF_DestroyText(udoll_display->text);
            udoll_display->text = IntToTTF(inventory.unload_dolls.size());
        }
    }
    if(!inventory.load_dolls.empty()){
        if(inventory.load_dolls.front() + 30 < frameCount){
            inventory.load_dolls.pop();
            loadMult = pow(0.85, inventory.load_dolls.size());
            TTF_DestroyText(ldoll_display->text);
            ldoll_display->text = IntToTTF(inventory.load_dolls.size());
        }
    }

    mPlayerArea->rects->next->y = 280 + 5*sin(SDL_GetTicks() / 200.0);
    if (!pissing || inventory.bottleCount.empty()){
        mBladderFilled += MS::dt / 12;

    } else {
        mBladderFilled -= MS::dt / 2.2;
        if (mBladderFilled < 0.0) {
            mBladderFilled = 0.0;
        } else{
            inventory.bottleCount.front() -= MS::dt * 2;
            if(inventory.bottleCount.front() <= 0) {
                inventory.bottleCount.pop();
                TTF_DestroyText(bottle_display->text);
                bottle_display->text = IntToTTF(inventory.bottleCount.size());
            }
        }
    }
    while (mBladderFilled > 1 + 1.f/45) {
        std::print(stderr, "{}", player.hp);
        mBladderFilled -= (1.f / 45);
        if (decrementHealth(player.hp)) {
            dead = true;
        }
        TTF_DestroyText(hp_display->text);
        std::string hp_string = std::format("{}", player.hp);
        const char* c_hp_string = hp_string.c_str();
        hpText = TTF_CreateText(mTtfEngine, mFont, c_hp_string, sizeof(hp_string) - 1);
        hp_display->text = hpText;
    }
if(int((196 - 20) * mBladderFilled) < 176) 
    mGui->rects->next->next->w = int((196 - 20) * mBladderFilled);
else
    mGui->rects->next->next->w = 176;

bearzos.timeSinceBearzos += MS::dt;
if (bearzos.timeSinceBearzos > bearzos.fluff_bearzos_countdown)
    bearzos_attack();
float msX = -1;
float msY = -1;
const SDL_MouseButtonFlags msState = SDL_GetMouseState(&msX, &msY);
float divisor = std::min(width, height);
float offset = (std::max(width, height) - std::min(width, height))/2.0;
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

if (kbState[SDL_SCANCODE_SPACE] && !pissing) {
    load_bar_fg->w = (176*mLoaded);
    if (player.x <= 0.1) { // loading
        mLoaded += MS::dt / (loadTime * loadMult);
        if (mLoaded > 1) mLoaded = 1;
    } else if (player.x >= 0.9) { // un-loading
        float oldLoadScore = mLoaded;
        mLoaded -= MS::dt / (loadTime * unloadMult);
        
        float dif = oldLoadScore - mLoaded;
        
        if (mLoaded > 0) inventory.give_money(dif * moneyMult);
        if (mLoaded < 0) mLoaded = 0;
    }
}

if (true){
    if((msState == SDL_BUTTON_LEFT && !held_down && IsRectClicked(msX, msY, unload_doll_button)) || (kbState[SDL_SCANCODE_1] && !upgradeHotkeysHeld[0])){
        if(inventory.Buy_Unload_Doll(frameCount)){
            unloadMult = pow(0.85, inventory.unload_dolls.size());
            TTF_DestroyText(udoll_display->text);
            udoll_display->text = IntToTTF(inventory.unload_dolls.size());
        } else {
            std::print(stderr, "Not Enough Money");
        };
    }
    if((msState == SDL_BUTTON_LEFT && !held_down && IsRectClicked(msX, msY, bottle_button)) || (kbState[SDL_SCANCODE_3] && !upgradeHotkeysHeld[2])){
        if(inventory.Buy_Bottle()){
            TTF_DestroyText(bottle_display->text);
            bottle_display->text = IntToTTF(inventory.bottleCount.size());
        } else {
            std::print(stderr, "Not Enough Money");
        };
    }
    if((msState == SDL_BUTTON_LEFT && !held_down && IsRectClicked(msX, msY, upgrade_button)) || (kbState[SDL_SCANCODE_2] && !upgradeHotkeysHeld[1])){
        if(inventory.Upgrade_Dolly()){
            moneyMult = 500 * (inventory.dollyLevel + 0.2);
            loadTime = 7.5 * inventory.dollyLevel;
            TTF_DestroyText(level_display->text);
            level_display->text = IntToTTF(inventory.dollyLevel);
        } else {
            std::print(stderr, "Not Enough Money");
        };
    }
    if((msState == SDL_BUTTON_LEFT && !held_down && IsRectClicked(msX, msY, load_doll_button)) || (kbState[SDL_SCANCODE_4] && !upgradeHotkeysHeld[3])){
        if(inventory.Buy_Load_Doll(frameCount)){
            loadMult = pow(0.85, inventory.load_dolls.size());
            TTF_DestroyText(ldoll_display->text);
            ldoll_display->text = IntToTTF(inventory.load_dolls.size());
            std::print(stderr, "{}", inventory.load_dolls.size());
        } else {
            std::print(stderr, "Not Enough Money");
        };
    }
    held_down = true;

    upgradeHotkeysHeld[0] = kbState[SDL_SCANCODE_1];
    upgradeHotkeysHeld[1] = kbState[SDL_SCANCODE_2];
    upgradeHotkeysHeld[2] = kbState[SDL_SCANCODE_3];
    upgradeHotkeysHeld[3] = kbState[SDL_SCANCODE_4];
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
    if (bearzos.bearzosAttackStage >= 2 && bearzos.bearzosAttackStage != 3 && bearzos.bearzosAttackStage != 5) {
        if (pissing) {
            bearzos.bearzosAttackStage = 3;
            mBearzos->rects->image = &bearzosMadImage;
            for (int i = 0; i < 20; i++) {
                if (decrementHealth(player.hp))
                    dead = true;

            }
            TTF_DestroyText(hp_display->text);
            std::string hp_string = std::format("{}", player.hp);
            const char* c_hp_string = hp_string.c_str();
            hpText = TTF_CreateText(mTtfEngine, mFont, c_hp_string, sizeof(hp_string) - 1);
            hp_display->text = hpText;
        }
    }
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
                    dead = true;

                TTF_DestroyText(hp_display->text);
                std::string hp_string = std::format("{}", player.hp);
                const char* c_hp_string = hp_string.c_str();
                hpText = TTF_CreateText(mTtfEngine, mFont, c_hp_string, sizeof(hp_string) - 1);
                hp_display->text = hpText;
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

TTF_Text* MS::MainScene::IntToTTF(int i){
    std::string i_string = std::format("{}", i);
    const char* c_i_string = i_string.c_str();
    TTF_Text *iText = TTF_CreateText(mTtfEngine, mFont, c_i_string, sizeof(c_i_string) - 1);
    return iText;
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

