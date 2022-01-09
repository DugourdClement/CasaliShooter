#define FPS_LIMIT 60

#include <iostream>
#include <fstream>
#include <thread>

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
#include "mystruct.h"
#include "move.h"
#include "check.h"
#include "generate.h"

using namespace std;
using namespace nsGraphics;
using namespace nsGui;
using namespace chrono;
using namespace nsAudio;

void keyboardWrite(MinGL &window, string &nameStr){

    if(window.isPressed({' ', false}) && nameStr.size() > 0) {
            //window.resetKey({' ', false});
            nameStr.pop_back();
    }else if (window.isPressed({'a', false})) {
        window.resetKey({'a', false});
        nameStr += "A";
    }else if(window.isPressed({'z', false})) {
        window.resetKey({'z', false});
        nameStr += "Z";
    }else if(window.isPressed({'e', false})) {
        window.resetKey({'e', false});
        nameStr += "E";
    }else if(window.isPressed({'r', false})) {
        window.resetKey({'r', false});
        nameStr += "R";
    }else if(window.isPressed({'t', false})) {
        window.resetKey({'t', false});
        nameStr += "T";
    }else if(window.isPressed({'y', false})) {
        window.resetKey({'y', false});
        nameStr += "Y";
    }else if(window.isPressed({'u', false})) {
        window.resetKey({'u', false});
        nameStr += "U";
    }else if(window.isPressed({'i', false})) {
        window.resetKey({'i', false});
        nameStr += "I";
    }else if(window.isPressed({'o', false})) {
        window.resetKey({'o', false});
        nameStr += "O";
    }else if(window.isPressed({'p', false})) {
        window.resetKey({'p', false});
        nameStr += "P";
    }else if(window.isPressed({'q', false})) {
        window.resetKey({'q', false});
        nameStr += "Q";
    }else if(window.isPressed({'s', false})) {
        window.resetKey({'s', false});
        nameStr += "S";
    }else if(window.isPressed({'d', false})) {
        window.resetKey({'d', false});
        nameStr += "D";
    }else if(window.isPressed({'f', false})) {
        window.resetKey({'f', false});
        nameStr += "F";
    }else if(window.isPressed({'g', false})) {
        window.resetKey({'g', false});
        nameStr += "G";
    }else if(window.isPressed({'h', false})) {
        window.resetKey({'h', false});
        nameStr += "H";
    }else if(window.isPressed({'j', false})) {
        window.resetKey({'j', false});
        nameStr += "J";
    }else if(window.isPressed({'k', false})) {
        window.resetKey({'k', false});
        nameStr += "K";
    }else if(window.isPressed({'l', false})) {
        window.resetKey({'l', false});
        nameStr += "L";
    }else if(window.isPressed({'m', false})) {
        window.resetKey({'m', false});
        nameStr += "M";
    }else if(window.isPressed({'w', false})) {
        window.resetKey({'w', false});
        nameStr += "W";
    }else if(window.isPressed({'c', false})) {
        window.resetKey({'c', false});
        nameStr += "C";
    }else if(window.isPressed({'v', false})) {
        window.resetKey({'v', false});
        nameStr += "V";
    }else if(window.isPressed({'b', false})) {
        window.resetKey({'b', false});
        nameStr += "B";
    }else if(window.isPressed({'n', false})) {
        window.resetKey({'n', false});
        nameStr += "N";
    }else if(window.isPressed({'x', false})) {
        window.resetKey({'x', false});
        nameStr += "X";
    }
}

void askName(MinGL &window, string &nameStr){
    window << Sprite ("spritesi2/name.si2", Vec2D(100, 250));
    window << Sprite ("spritesi2/spacebar2.si2", Vec2D(100, 500));
    keyboardWrite(window, nameStr);
    window << Text(Vec2D(275, 400), nameStr , KBlue, GlutFont::BITMAP_HELVETICA_18);
}

int main()
{

    Vec2D misPos;
    Vec2D torPos;
    Vec2D torPos2;

    srand(time(NULL));

    enemy open;
    open.rightOrLeft = 1;
    generateOPEN(open, 50);

    enemy classroom;
    classroom.rightOrLeft = 1;
    generateCLASSROOM(classroom, 125);

    vector<enemy> vecOvni;
    for (size_t i = 0; i < 5; ++i) {
        enemy ovni;
        ovni.rightOrLeft = 1;
        generateOVNI(ovni, "spritesi2/OVNI.si2");
        vecOvni.push_back(ovni);
    }

    enemy IPPs;
    IPPs.rightOrLeft = 1;
    generateVecSprite(IPPs, 50, "spritesi2/i++.si2");

    enemy JPPs;
    JPPs.rightOrLeft = 1;
    generateVecSprite(JPPs, 100, "spritesi2/j++.si2");

    enemy KPPs;
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
    // Initializes all images
    Sprite background("spritesi2/fondarcade.si2", Vec2D(0, 0));
    Sprite backgroundpsg("spritesi2/fond_psg.si2", Vec2D(0, 0));
    Sprite scoreboardbg("spritesi2/scoreboard.si2", Vec2D(125, 250));
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

    BgText choosethemode(Vec2D(150, 240), "Choose between light and dark theme with a or z", KWhite, KBlack);
    nsTransition::TransitionEngine transitionEngine;


    // Start the transitions on our custom object
    transitionEngine.startContract(nsTransition::TransitionContract(choosethemode, choosethemode.TRANSITION_TEXT_COLOR, chrono::seconds(1), {0, 0, 0},
                                                                    chrono::seconds::zero(), nsTransition::Transition::MODE_LOOP_SMOOTH));
    transitionEngine.startContract(nsTransition::TransitionContract(choosethemode, choosethemode.TRANSITION_BACKGROUND_COLOR, chrono::seconds(1), {255, 255, 0},
                                                                    chrono::seconds::zero(), nsTransition::Transition::MODE_LOOP_SMOOTH));

    // Variable that keeps the frame time
    chrono::microseconds frameTime = chrono::microseconds::zero();
    unsigned choixobjet=0;
    unsigned choixpsgom=0;



    unsigned playerLifeUnsigned = 0;
    bool firstShootM = true;
    bool isPressed = false;
    bool firstShootT = true;
    bool firstShootT2 = true;
    //Vector to determine if a UFO is firing
    bool ovniTorOne = true;
    bool ovniTorTwo = true;
    bool ovniTorThree = true;
    bool ovniTorFour = true;
    bool ovniTorFive = true;
    //Vector of Vec2D for UFO torpedo fire
    vector<Vec2D> vecOvniTorpedo;
    for (size_t i = 0; i < vecOvni.size(); ++i) {
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
            menu(window, casali);
            choixobjet = entrerMenu(window, casali);
        }else if (choixobjet == 2){ //Opening of the scoreboard menu
            window.clearScreen();
            choixLightDark(window,choixpsgom, background, backgroundpsg);
            window << scoreboardbg;
            window << titrescoreboard;
            window << backb;
            if (window.isPressed({'&', false})) {
                choixobjet = 0;
            }
            scoreboard(window);
        }else if (choixobjet == 3){ //Opening of the option menu
            window.clearScreen();
            choixLightDark(window,choixpsgom, background, backgroundpsg);
            window << choosethemode;
            window << moon;
            window << sun;
            window << arrow;
            window << backb;
            selectTheme(window, arrow);
            choixpsgom = chooseTheme(window, arrow, choixpsgom);
            if (window.isPressed({'&', false})) {
                choixobjet = 0;
            }
        }else if(choixobjet == 1){ // Opening of the name window
            window.clearScreen();
            choixLightDark(window,choixpsgom, background, backgroundpsg);
            askName(window, nameStr);

            if (window.isPressed({'"', false})) {
                choixobjet = 4;
            }else if (window.isPressed({'&', false})) {
                window.resetKey({'&', false});
                choixobjet = 0;
                nameStr = "";
            }

        }else if(choixobjet == 4){ // Opening of the game
            window.clearScreen();

            choixLightDark(window,choixpsgom, background, backgroundpsg);
            window << mug.vecMug[mug.index];

            IPPs.update(window);
            JPPs.update(window);
            KPPs.update(window);

            keyboard(window, mug.vecMug[mug.index]);

            moveVecSprite(IPPs);
            moveVecSprite(KPPs);
            moveVecSprite(JPPs);

            isPressed = missile(window, mug.vecMug[mug.index], IPPs, KPPs, JPPs, playerLifeUnsigned, firstShootM, isPressed, misPos);
            if(isPressed == true) window << nsShape::Rectangle(misPos, misPos + Vec2D(2, 10), KCyan);
            string playerLifeString = to_string(playerLifeUnsigned);
            //Points generator
            window << Text(Vec2D(60, 160), "Pts:", KWhite, GlutFont::BITMAP_9_BY_15);
            window << Text(Vec2D(100, 160), playerLifeString, KWhite, GlutFont::BITMAP_9_BY_15);

            if (torpedo(mug, IPPs, firstShootT, torPos)) window << nsShape::Rectangle(torPos, torPos + Vec2D(5, 10), KGreen);
            if (torpedo(mug, IPPs, firstShootT2, torPos2)) window << nsShape::Rectangle(torPos2, torPos2 + Vec2D(5, 10), KGreen);


            //Verify if enemies are still alive
            if (allDead(IPPs) && allDead(JPPs) && allDead(KPPs)) {
                PPsMusic.setMusicPlaying(false);
                AudioEngine openclassroomMusic;
                openclassroomMusic.setMusic("music/OCmusic.wav", true);
                openclassroomMusic.toggleMusicPlaying();
                while (!allDead(open) || !allDead(classroom)) {

                    window.clearScreen();

                    choixLightDark(window,choixpsgom, background, backgroundpsg);
                    window << mug.vecMug[mug.index];

                    keyboard(window, mug.vecMug[mug.index]);


                    for (size_t i = 0; i < vecOvni.size(); ++i) {
                        vecOvni[i].update(window);
                    }
                    open.update(window);
                    classroom.update(window);

                    //OPEN and CLASSROOM movements

                    for (size_t i = 0; i <  vecOvni.size(); ++i) {
                        moveOVNI(vecOvni[i]);
                    }
                    moveVecSprite(classroom);
                    moveOpen(open);

                    isPressed = missile(window, mug.vecMug[mug.index], open, classroom, JPPs, playerLifeUnsigned, firstShootM, isPressed, misPos);
                    if(isPressed == true) window << nsShape::Rectangle(misPos, misPos + Vec2D(2, 10), KCyan);
                    string playerLifeString = to_string(playerLifeUnsigned);
                    //Points generator
                    window << Text(Vec2D(60, 160), "Pts:", KWhite, GlutFont::BITMAP_9_BY_15);
                    window << Text(Vec2D(100, 160), playerLifeString, KWhite, GlutFont::BITMAP_9_BY_15);

                    //Open shooting
                    if (torpedo(mug, open, firstShootT, torPos)) window << nsShape::Rectangle(torPos, torPos + Vec2D(5, 10), KGreen);

                    //Ovnis shooting
                    if (ovniShoot(mug, vecOvni[0], ovniTorOne, vecOvniTorpedo[0])) window << nsShape::Rectangle(vecOvniTorpedo[0], vecOvniTorpedo[0] + Vec2D(5, 10), KGreen);
                    if (ovniShoot(mug, vecOvni[1], ovniTorTwo, vecOvniTorpedo[1])) window << nsShape::Rectangle(vecOvniTorpedo[1], vecOvniTorpedo[1] + Vec2D(5, 10), KGreen);
                    if (ovniShoot(mug, vecOvni[2], ovniTorThree, vecOvniTorpedo[2])) window << nsShape::Rectangle(vecOvniTorpedo[2], vecOvniTorpedo[2] + Vec2D(5, 10), KGreen);
                    if (ovniShoot(mug, vecOvni[3], ovniTorFour, vecOvniTorpedo[3])) window << nsShape::Rectangle(vecOvniTorpedo[3], vecOvniTorpedo[3] + Vec2D(5, 10), KGreen);
                    if (ovniShoot(mug, vecOvni[4], ovniTorFive, vecOvniTorpedo[4])) window << nsShape::Rectangle(vecOvniTorpedo[4], vecOvniTorpedo[4] + Vec2D(5, 10), KGreen);

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
                break;
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
