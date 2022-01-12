#define FPS_LIMIT 60

#include <iostream>
#include <fstream>
#include <thread>
#include <unistd.h>
#include <vector>

#include "MinGL2/include/mingl/mingl.h"
#include "MinGL2/include/mingl/gui/sprite.h"
#include "MinGL2/include/mingl/graphics/vec2d.h"
#include "MinGL2/include/mingl/shape/rectangle.h"
#include "MinGL2/include/mingl/gui/text.h"
#include "MinGL2/include/mingl/shape/line.h"
#include "MinGL2/include/mingl/audio/audioengine.h"
#include "MinGL2/include/mingl/gui/glut_font.h"
#include "MinGL2/include/mingl/transition/transition_engine.h"

#include "bgtext.h"
#include "menu.h"
#include "move.h"
#include "check.h"
#include "generate.h"
#include "yaml.h"
#include "mugstruct.h"
#include "playersStruct.h"
#include "enemyStruct.h"

using namespace std;
using namespace nsGraphics;
using namespace nsGui;
using namespace chrono;
using namespace nsAudio;

// Initializes all images
Sprite background("spritesi2/fondarcade.si2", Vec2D(0, 0));
Sprite backgroundpsg("spritesi2/fond_psg.si2", Vec2D(0, 0));
Sprite scoreboardbg("spritesi2/scoreboard.si2", Vec2D(145, 272));
Sprite titrescoreboard("spritesi2/titrescore.si2", Vec2D(0, 0));
Sprite titreaccueil("spritesi2/casaliheader.si2", Vec2D(155, 138));
Sprite startb("spritesi2/start-button.si2", Vec2D(222, 283));
Sprite scoreb("spritesi2/scoreboard-button.si2", Vec2D(222, 378));
Sprite settingsb("spritesi2/options-button.si2", Vec2D(222, 473));
Sprite quitb("spritesi2/quit-button.si2", Vec2D(222, 568));
Sprite casali("spritesi2/casali.si2", Vec2D(160, 305));
Sprite moon("spritesi2/moon.si2", Vec2D(160, 350));
Sprite sun("spritesi2/sun.si2", Vec2D(400, 338));
Sprite arrow("spritesi2/arrow.si2", Vec2D(188, 460));
Sprite backb("spritesi2/back-button.si2", Vec2D(66, 666));
Sprite backgroundNoScreen("spritesi2/fondnoscreen.si2", Vec2D(0, 0));
Sprite creditSprite ("spritesi2/generique.si2", Vec2D(0, -100));

void keyboardWrite(MinGL &window, string &nameStr){
    for(unsigned i = 97; i < 123; ++i){
        if (window.isPressed({i, false})) {
            window.resetKey({i, false});
            nameStr += i-32;
        }
    }
    if(window.isPressed({8, false}) && nameStr.size() > 0) {
        nameStr.pop_back();
    }
}

void askName(MinGL &window, string &nameStr){
    window << Sprite ("spritesi2/name.si2", Vec2D(100, 250));
    window << Sprite ("spritesi2/spacebar2.si2", Vec2D(100, 500));
    keyboardWrite(window, nameStr);
    window << Text(Vec2D(275, 400), nameStr , KBlue, GlutFont::BITMAP_HELVETICA_18);
}

void menu(MinGL &window,microseconds frameTime, unsigned &choixobjet, unsigned &choixpsgom, string &nameStr,vector<unsigned> vecKey) {

    BgText choosethemode(Vec2D(150, 240), "Choose between light and dark theme with a or z", KWhite, KBlack);
    nsTransition::TransitionEngine transitionEngine;

    // Start the transitions on our custom object
    transitionEngine.startContract(nsTransition::TransitionContract(choosethemode, choosethemode.TRANSITION_TEXT_COLOR, chrono::seconds(1), {0, 0, 0},
                                                                    chrono::seconds::zero(), nsTransition::Transition::MODE_LOOP_SMOOTH));
    transitionEngine.startContract(nsTransition::TransitionContract(choosethemode, choosethemode.TRANSITION_BACKGROUND_COLOR, chrono::seconds(1), {255, 255, 0},
                                                                    chrono::seconds::zero(), nsTransition::Transition::MODE_LOOP_SMOOTH));
    transitionEngine.update(frameTime);

    if (choixobjet == 0) { //Casali shooter home screen opening
        window.clearScreen();
        choixLightDark(window,choixpsgom, background, backgroundpsg);
        window <<  titreaccueil;
        window << startb;
        window << scoreb;
        window << settingsb;
        window << quitb;
        window << casali;
        menu(window, casali, vecKey);
        choixobjet = entrerMenu(window, casali, vecKey);
    }else if (choixobjet == 2){ //Opening of the scoreboard menu
        window.clearScreen();
        choixLightDark(window,choixpsgom, background, backgroundpsg);
        window << scoreboardbg;
        window << titrescoreboard;
        window << backb;
        if (window.isPressed({27, false})) {
            choixobjet = 0;
        }
        showScore(window);
    }else if (choixobjet == 3){ //Opening of the option menu
        window.clearScreen();

        choixLightDark(window,choixpsgom, background, backgroundpsg);
        window << choosethemode;
        window << moon;
        window << sun;
        window << arrow;
        window << backb;
        selectTheme(window, arrow, vecKey);
        choixpsgom = chooseTheme(window, arrow, choixpsgom, vecKey);
        if (window.isPressed({27, false})) {
            choixobjet = 0;
        }
    }else if(choixobjet == 1){ // Opening of the name window
        window.clearScreen();
        choixLightDark(window,choixpsgom, background, backgroundpsg);
        askName(window, nameStr);

        if (window.isPressed({13, false})) {
            choixobjet = 4;
        }else if (window.isPressed({27, false})) {
            window.resetKey({27, false});
            choixobjet = 0;
            nameStr = "";
        }

    }


    ////////chrono::seconds::zero(), nsTransition::Transition::MODE_LOOP_SMOOTH));

}

void gameOpening (MinGL &window, enemyStruct &IPPs, enemyStruct &KPPs, enemyStruct &JPPs, unsigned choixpsgom, mugStruct &mug, string &nameStr, string &playerPointsString, vector<unsigned> vecKey){

    window.clearScreen();

    choixLightDark(window,choixpsgom, background, backgroundpsg);
    window << mug.vecMug[mug.index];

    IPPs.update(window);
    JPPs.update(window);
    KPPs.update(window);

    keyboard(window, mug.vecMug[mug.index], vecKey);

    moveVecSprite(IPPs, playerPointsString, nameStr, backgroundNoScreen, creditSprite, window);
    moveVecSprite(KPPs, playerPointsString, nameStr, backgroundNoScreen, creditSprite, window);
    moveVecSprite(JPPs, playerPointsString, nameStr, backgroundNoScreen, creditSprite, window);
}

void display(MinGL &window, string &playerPointsString){
    //Points generator
    window << Text(Vec2D(60, 160), "Pts:", KWhite, GlutFont::BITMAP_9_BY_15);
    window << Text(Vec2D(100, 160), playerPointsString, KWhite, GlutFont::BITMAP_9_BY_15);

}

void reset (enemyStruct &PPs){
    for (unsigned i = 0; i < PPs.state.size(); ++i) {
        PPs.state[i] = true;
    }
}
int main()

{
    vector<unsigned> vecKey = vecParam("config.yaml");

    Vec2D misPos;
    Vec2D torPos;
    Vec2D torPos2;

    srand(time(NULL));

    enemyStruct IPPs;
    IPPs.rightOrLeft = 1;
    generateVecSprite(IPPs, 50, "spritesi2/i++.si2");

    enemyStruct JPPs;
    JPPs.rightOrLeft = 1;
    generateVecSprite(JPPs, 100, "spritesi2/j++.si2");

    enemyStruct KPPs;
    KPPs.rightOrLeft = 1;
    generateVecSprite(KPPs, 150, "spritesi2/k++.si2");

    mugStruct mug;
    generateVecMug(mug);
    mug.index = 0;
    mug.vecMug[mug.index].setPosition(Vec2D(50+284, 138+500));


    // Initializes the system
    MinGL window("CasaliShooter", Vec2D(700, 1000), Vec2D(50, 0), KBlack);
    window.initGlut();
    window.initGraphic();


    // Variable that keeps the frame time
    chrono::microseconds frameTime = chrono::microseconds::zero();

    bool startBool = true;
    unsigned choixobjet=0;
    unsigned choixpsgom=0;


    unsigned playerLifeUnsigned = 0;
    bool firstShootM = true;
    bool isPressed = false;
    bool firstShootT = true;
    //Vector to determine if a UFO is firing
    bool ovniTorOne = true;
    bool ovniTorTwo = true;
    bool ovniTorThree = true;
    bool ovniTorFour = true;
    bool ovniTorFive = true;


    //Vector of Vec2D for UFO torpedo fire
    vector<Vec2D> vecOvniTorpedo;
    for (size_t i = 0; i < vecOvniTorpedo.size(); ++i) {
        Vec2D ovniTor;
        vecOvniTorpedo.push_back(ovniTor);
    }

    AudioEngine PPsMusic;
    PPsMusic.setMusic("music/I_Attack.wav", true);
    PPsMusic.toggleMusicPlaying();

    string nameStr ="";


    // Turn the loop as long as the window is open
    while (window.isOpen())
    {


        //Get current time
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        if(startBool){
            menu(window, frameTime, choixobjet, choixpsgom, nameStr, vecKey);
        }else if(window.isPressed({char(vecKey[0]), false})){
            startBool = true;
            choixobjet = 0;
            menu(window, frameTime, choixobjet, choixpsgom, nameStr, vecKey);
        }


        if(choixobjet == 4){ // Opening of the game

            string playerLifeString = to_string(playerLifeUnsigned);

            choixLightDark(window,choixpsgom, background, backgroundpsg);
            window << mug.vecMug[mug.index];


            gameOpening(window, IPPs, JPPs, KPPs, choixpsgom, mug, nameStr, playerLifeString, vecKey);


            isPressed = missile(window, mug.vecMug[mug.index], IPPs, KPPs, JPPs, playerLifeUnsigned, firstShootM, isPressed, misPos, vecKey);
            if(isPressed == true) window << nsShape::Rectangle(misPos, misPos + Vec2D(2, 10), KCyan);

            display(window, playerLifeString);

            if (torpedo(mug, IPPs, firstShootT, torPos, backgroundNoScreen, creditSprite, window)) window << nsShape::Rectangle(torPos, torPos + Vec2D(5, 10), KGreen);


            //Verify if enemies are still alive
            if (allDead(IPPs) && allDead(JPPs) && allDead(KPPs)) {
                PPsMusic.setMusicPlaying(false);
                AudioEngine openclassroomMusic;
                openclassroomMusic.setMusic("music/OCmusic.wav", true);
                openclassroomMusic.toggleMusicPlaying();

                enemyStruct open;
                open.rightOrLeft = 1;
                generateOPEN(open, 50);

                enemyStruct classroom;
                classroom.rightOrLeft = 1;
                generateCLASSROOM(classroom, 125);

                vector<enemyStruct> vecOvni;
                for (size_t i = 0; i < 5; ++i) {
                    enemyStruct ovni;
                    ovni.rightOrLeft = 1;
                    generateOVNI(ovni, "spritesi2/OVNI.si2");
                    vecOvni.push_back(ovni);
                }
                //Vector of Vec2D for UFO torpedo fire
                vector<Vec2D> vecOvniTorpedo;
                for (size_t i = 0; i < vecOvni.size(); ++i) {
                    Vec2D ovniTor;
                    vecOvniTorpedo.push_back(ovniTor);
                }

                while (!allDead(open) || !allDead(classroom)) {

                    window.clearScreen();

                    choixLightDark(window,choixpsgom, background, backgroundpsg);
                    window << mug.vecMug[mug.index];

                    keyboard(window, mug.vecMug[mug.index], vecKey);


                    for (size_t i = 0; i < vecOvni.size(); ++i) {
                        vecOvni[i].update(window);
                    }
                    open.update(window);
                    classroom.update(window);

                    //OPEN and CLASSROOM movements

                    for (size_t i = 0; i <  vecOvni.size(); ++i) {
                        moveOVNI(vecOvni[i], playerLifeString, nameStr, backgroundNoScreen, creditSprite, window);
                    }
                    moveVecSprite(classroom, playerLifeString, nameStr, backgroundNoScreen, creditSprite, window);
                    moveOpen(open, playerLifeString, nameStr, backgroundNoScreen, creditSprite, window);

                    isPressed = missile(window, mug.vecMug[mug.index], open, classroom, JPPs, playerLifeUnsigned, firstShootM, isPressed, misPos, vecKey);
                    if(isPressed == true) window << nsShape::Rectangle(misPos, misPos + Vec2D(2, 10), KCyan);
                    string playerLifeString = to_string(playerLifeUnsigned);
                    //Points generator
                    window << Text(Vec2D(60, 160), "Pts:", KWhite, GlutFont::BITMAP_9_BY_15);
                    window << Text(Vec2D(100, 160), playerLifeString, KWhite, GlutFont::BITMAP_9_BY_15);

                    //Open shooting
                    if (torpedo(mug, open, firstShootT, torPos, backgroundNoScreen, creditSprite, window)) window << nsShape::Rectangle(torPos, torPos + Vec2D(5, 10), KGreen);

                    //Ovnis shooting
                    if (ovniShoot(mug, vecOvni[0], ovniTorOne, vecOvniTorpedo[0], backgroundNoScreen, creditSprite, window)) window << nsShape::Rectangle(vecOvniTorpedo[0], vecOvniTorpedo[0] + Vec2D(5, 10), KGreen);
                    if (ovniShoot(mug, vecOvni[1], ovniTorTwo, vecOvniTorpedo[1], backgroundNoScreen, creditSprite, window)) window << nsShape::Rectangle(vecOvniTorpedo[1], vecOvniTorpedo[1] + Vec2D(5, 10), KGreen);
                    if (ovniShoot(mug, vecOvni[2], ovniTorThree, vecOvniTorpedo[2], backgroundNoScreen, creditSprite, window)) window << nsShape::Rectangle(vecOvniTorpedo[2], vecOvniTorpedo[2] + Vec2D(5, 10), KGreen);
                    if (ovniShoot(mug, vecOvni[3], ovniTorFour, vecOvniTorpedo[3], backgroundNoScreen, creditSprite, window)) window << nsShape::Rectangle(vecOvniTorpedo[3], vecOvniTorpedo[3] + Vec2D(5, 10), KGreen);
                    if (ovniShoot(mug, vecOvni[4], ovniTorFive, vecOvniTorpedo[4], backgroundNoScreen, creditSprite, window)) window << nsShape::Rectangle(vecOvniTorpedo[4], vecOvniTorpedo[4] + Vec2D(5, 10), KGreen);

                    // We finish the current frame
                    window.finishFrame();

                    // Empty the queue of events
                    window.getEventManager().clearEvents();

                    // We wait a bit to limit the framerate and relieve the CPU
                    this_thread::sleep_for(chrono::milliseconds(2000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

                    // We keep the frame time
                    frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);

                }
                openclassroomMusic.setMusicPlaying(false);
                reset(IPPs);
                reset(JPPs);
                reset(KPPs);
                PPsMusic.setMusic("music/I_Attack.wav", true);
                PPsMusic.toggleMusicPlaying();
            }
        }

        // We finish the current frame
        window.finishFrame();

        // Empty the queue of events
        window.getEventManager().clearEvents();

        // We wait a bit to limit the framerate and relieve the CPU
        this_thread::sleep_for(chrono::milliseconds(2000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // We keep the frame time
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }


    return 0;
}
