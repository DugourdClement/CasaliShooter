/**
* @file menu.cpp
* @brief Menu manager
* @author Gonzales, Djerian, Leydier, Volpei, Dugourd
* @version 1.0
* @date 11/01/2022
*/
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
#include "yaml.h"


using namespace std;
using namespace nsGraphics;
using namespace nsGui;
using namespace chrono;
using namespace nsAudio;

/** @brief Run the credit
*
*@param[in] window : window in which we inject the element and detect key presses
*@param[in] backgroundNoScreen : background sprite to inject in the window
*@param[in] creditSprite : credit
*@returns void
*
*/
void credit(MinGL &window, Sprite &backgroundNoScreen, Sprite &creditSprite){

    while(creditSprite.getPosition().getY() > -1250){
        window.clearScreen();
        window << creditSprite;
        window << backgroundNoScreen;
        Vec2D positionGenerique = creditSprite.getPosition();
        int posGenX = positionGenerique.getX();
        int posGenY = positionGenerique.getY()-5;
        Vec2D positionF (posGenX, posGenY);
        creditSprite.setPosition(positionF);

        // We finish the current frame
        window.finishFrame();
        // Empty the queue of events
        window.getEventManager().clearEvents();
    }
    sleep(5);
}


/** @brief Selects the theme and moves the **cursor**
*
*@param[in] window : window in which we inject the element and detect key presses
*@param[in] image : get position and change cursor position
*@returns void
*
*/
void selectTheme(MinGL &window, Sprite &image, vector<unsigned> vecKey)
{
        if (window.isPressed({char(vecKey[2]), false})) {
            Vec2D position = image.getPosition();
            int arrowX = 188;
            int arrowY = position.getY();
            Vec2D positionF (arrowX, arrowY);
            image.setPosition(positionF);
        }
        else if (window.isPressed({char(vecKey[3]), false})) {
            Vec2D position = image.getPosition();
            int arrowX = 435;
            int arrowY = position.getY();
            Vec2D positionF (arrowX, arrowY);
            image.setPosition(positionF);
        }
}

/** @brief Change theme to **theme select**
*
*@param[in] window : window in which we inject the element and detect key presses
*@param[in] image : get the position of the cursor
*@param[in] baseTheme : Unsigned representing the chosen theme
*@returns unsigned
*
*/
unsigned chooseTheme(MinGL &window, Sprite &image, unsigned &baseTheme, vector<unsigned> vecKey)
{

    if (window.isPressed({char(vecKey[1]), false})) {
        Vec2D position = image.getPosition();
        int arrowX = position.getX();
        if (arrowX == 188) {
            return 1;
        }
        else {
            return 0;
        }
    }
    return baseTheme;
}

/** @brief Change the place of the cursor in the menu
*
*@param[in] window : window in which we inject the element and detect key presses
*@param[in] image : image that moves according to the key press **s** or **z**
*@returns void
*
*/
void menu(MinGL &window, nsGui::Sprite &image, vector<unsigned> vecKey) {
    if (window.isPressed({char(vecKey[4]), false})) {
        window.resetKey({char(vecKey[4]), false});
        Vec2D position = image.getPosition();
        if (position.getY()==575) {
            int mugX = position.getX();
            int mugY = 305;
            Vec2D positionF (mugX, mugY);
            image.setPosition(positionF);
        }
        else {
            int mugX = position.getX();
            int mugY = position.getY()+90;
            Vec2D positionF (mugX, mugY);
            image.setPosition(positionF);
        }

    }
    if (window.isPressed({char(vecKey[5]), false})) {
        window.resetKey({char(vecKey[5]), false});
        Vec2D position = image.getPosition();
        if (position.getY()==305) {
            int mugX = position.getX();
            int mugY = 575;
            Vec2D positionF (mugX, mugY);
            image.setPosition(positionF);
        }
        else {
            int mugX = position.getX();
            int mugY = position.getY()-90;
            Vec2D positionF (mugX, mugY);
            image.setPosition(positionF);
        }

    }
}

/** @brief Choice of **menu**
*
*@param[in] window : window in which we inject the element and detect key presses
*@param[in] image : Image that will determine the menu selected
*@returns unsigned according to the selected menu between 0 and 3
*
*/
unsigned entrerMenu(MinGL &window, nsGui::Sprite &image, vector<unsigned> vecKey)
{
    if (window.isPressed({char(vecKey[1]), false})) {
        window.resetKey({char(vecKey[1]), false});
            Vec2D position = image.getPosition();
            int mugY = position.getY();
            if (mugY == 575) {
                exit(0); // exit
            }
            else if (mugY == 485) {
                return 3; // menu 3
            }
            else if (mugY == 395) {
                return 2; // menu 2
            }else if(mugY == 305){
                return 1; // menu 1
            }
    }
    return 0;
}

/** @brief Applies the **selected theme**
*
*@param[in] window : window in which we inject the element
*@param[in] choixpsgom : detect which theme to apply
*@param[in] themelight : OM background to inject in the window
*@param[in] themedark : PSG background to inject in the window
*@returns void
*
*/
void choixLightDark (MinGL &window, unsigned &choixpsgom,Sprite &themelight, Sprite &themedark){
    if (choixpsgom == 0) {
        window << themelight;
    }
    else {
        window << themedark;
    }
}

/** @brief Determines if the player1 is better than the player 2 **sort player**
*
*@param[in] joueur1 player1
*@param[in] joueur2 player2
*@return **true** if the player1 is better than the player2 and **false** if the player2 is better than the player1
*
*/
bool isBetter (const playersStruct & joueur1, const playersStruct & joueur2){ // Bool used to sort player
    return joueur1.point >= joueur2.point;
}

/** @brief Function which sort the **scoreboard** and shows it by using a txt file
*
*@param[in] window : window that displays the scores
*@returns void
*
*/
void showScore(MinGL & window) //Function which shows the scoreboard
{
    ifstream data_file("score.txt");
    vector<playersStruct> playerScore;
    playersStruct playerStruc;
    while (data_file >> playerStruc.player >> playerStruc.point) { //Place every elements of the file in the structure
        playerScore.emplace_back(playerStruc);
    }
    sort (playerScore.begin (), playerScore.end(), isBetter); // Sort all players by their score
    vector<string> stringScore;
    if (playerScore.size()>10) { //Make that the structure only retains the 10 best players
        playerScore.resize(10);
    }
    for (size_t i = 0; i<playerScore.size(); ++i) { //Place every score and player on the screen
        stringScore.push_back(to_string(playerScore[i].point)); //Transform the score of the players into String so i can use nsGui::Text to show them
        window << nsGui::Text(Vec2D(190, 294+(30*i)), playerScore[i].player, KWhite, nsGui::GlutFont::BITMAP_9_BY_15)
               << nsGui::Text(Vec2D(525, 294+(30*i)), stringScore[i], KWhite, nsGui::GlutFont::BITMAP_9_BY_15);
    }
}
