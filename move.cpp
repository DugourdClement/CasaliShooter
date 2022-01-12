/**
* @file move.cpp
* @brief Movements manager
* @author Gonzales, Djerian, Leydier, Volpei, Dugourd
* @version 1.0
* @date 11/01/2022
*/
#define FPS_LIMIT 60

#include <iostream>
#include <fstream>
#include <thread>
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

#include "move.h"
#include "yaml.h"
#include "mugstruct.h"
#include "playersStruct.h"
#include "enemyStruct.h"
#include "menu.h"

using namespace std;
using namespace nsGraphics;
using namespace nsGui;
using namespace chrono;
using namespace nsAudio;

/** @brief Adding scores + names into score.txt
*
*@param[in] playerLifeString :
*@param[in] nameStr :
*@returns void
*
*/
void addScore(string &playerLifeString, string &nameStr){
    fstream ofs;
    ofs.open("score.txt", ios_base::app);
    if(ofs.is_open()){
        cout << nameStr << " " << playerLifeString << endl;
        ofs << nameStr << " " << playerLifeString << endl;
    }
}

/** @brief If a key is pressed, the position of the mug is retrieved.  Add or remove 5 to the X position with Q and D ( move the mug )
*
*@param[in] window :
*@param[in] mug :
*@returns void
*
*/
void keyboard(MinGL &window, Sprite &mug, vector<unsigned> vecKey)
{
    if (window.isPressed({char(vecKey[6]), false}) && mug.getPosition().getX() > 50 ) {
        Vec2D position = mug.getPosition();
        int mugX = position.getX();
        int mugY = position.getY();
        Vec2D positionF (mugX-5, mugY);
        mug.setPosition(positionF);
    }
    if (window.isPressed({char(vecKey[7]), false}) && mug.getPosition().getX() < (600-64+50)) {
        Vec2D position = mug.getPosition();
        int mugX = position.getX();
        int mugY = position.getY();
        Vec2D positionF (mugX+5, mugY);
        mug.setPosition(positionF);
    }
}

/** @brief Adds x and y to the coordinates of the sprite passed as parameters
*
*@param[in] position :
*@param x :
*@param y :
*@returns void
*
*/
void moveSprite(Sprite &position, const int &x, const int &y) {
    position.setPosition(Vec2D(position.getPosition().getX() + x, position.getPosition().getY() + y));
}

/** @brief Move the sprites of "open"
*
*@param[in] open: Correspond to open and his informations
*@param[in] playerLifeString : Correspond to how many life the player has
*@param[in] nameStr : Correspond to the name of the current player
*@param[in] backgroundNoScreen :
*@param[in] generiqueSprite :
*@param[in] window :
*@returns void
*
*/
void moveOpen(enemyStruct & open, string &playerLifeString, string &nameStr, Sprite &backgroundNoScreen, Sprite &creditSprite,MinGL &window){
    //if the sprite vector does not exit the window, runs through all the letters and moves them by 5 px
    if (open.vecSprite[0].getPosition().getX() < (600 - 470) || open.vecSprite[open.vecSprite.size() - 1].getPosition().getX() > 50) {
        for(Sprite & letter : open.vecSprite) {
            moveSprite(letter, open.rightOrLeft*5, 0);
        }
    }
    //if the sprite vector comes out on the right side of the window, we move on the other side
    if (open.vecSprite[open.vecSprite.size() - 1].getPosition().getX() > (600 - 99) && open.rightOrLeft == 1) {
        open.rightOrLeft = -1;
        for (Sprite & letter : open.vecSprite) {
            moveSprite(letter, 0, 10);
        }
    }
    //if the sprite vector commes out on the left side of the window, we move on the other side
    else if(open.vecSprite[0].getPosition().getX() <  (600 - 470) && open.rightOrLeft == -1) {
        open.rightOrLeft = 1;
        for (Sprite & letter : open.vecSprite) {
            moveSprite(letter, 0, 10);
        }
    }
    // if the sprite vector reached the bottom, GAME OVER
     if (open.vecSprite[0].getPosition().getY() > 600){
         addScore(playerLifeString, nameStr);
         credit(window,backgroundNoScreen,creditSprite);
         exit(0);
     }
}

/** @brief Move JPPS,IPPS,KPPS
*
*@param[in] vecSprite:
*@param[in] playerLifeString :
*@param[in] nameStr :
*@param[in] backgroundNoScreen :
*@param[in] generiqueSprite :
*@param[in] window :
*@returns void
*
*/
void moveVecSprite(enemyStruct &vecSprite, string &playerLifeString, string &nameStr, Sprite &backgroundNoScreen, Sprite &creditSprite, MinGL &window){
    // If the sprites at the end do not touch the edges, move all the sprites at the same time
    if (vecSprite.vecSprite[0].getPosition().getX() < (600-64+50) ||
        vecSprite.vecSprite[vecSprite.vecSprite.size() - 1].getPosition().getX() > 0+50){
        for(Sprite &sprite : vecSprite.vecSprite){
            moveSprite(sprite, vecSprite.rightOrLeft *5, 0);
        }
    }
    // If the sprites at the end touch the edges, change direction and move down the sprites by 10 pixels
    if(vecSprite.vecSprite[vecSprite.vecSprite.size() - 1].getPosition().getX() > (600-64+50) && vecSprite.rightOrLeft == 1){
        vecSprite.rightOrLeft = -1;
        for(Sprite &sprite : vecSprite.vecSprite){
            moveSprite(sprite, 0, 10);
        }
    }else if(vecSprite.vecSprite[0].getPosition().getX() < 0+50 && vecSprite.rightOrLeft == -1){
        vecSprite.rightOrLeft = 1;
        for(Sprite &sprite : vecSprite.vecSprite){
            moveSprite(sprite, 0, 10);
        }
    }
    // if the sprite vector reached the bottom, GAME OVER
    if(vecSprite.vecSprite[0].getPosition().getY()>(600)){
        addScore(playerLifeString, nameStr);
        credit(window,backgroundNoScreen,creditSprite);
        exit(0);
    }
}

/** @brief Move the sprite "OVNI"
*
*@param[in] ovni: Correspond to the UFO and their informations
*@param[in] playerLifeString : Correspond to how many lifes the player has
*@param[in] nameStr : Correspond to the current name of the player
*@param[in] backgroundNoScreen :
*@param[in] generiqueSprite :
*@param[in] window :
*@returns void
*
*/
void moveOVNI(enemyStruct & ovni, string &playerLifeString, string &nameStr, Sprite &backgroundNoScreen, Sprite &creditSprite, MinGL &window) {
    // If the sprites at the end do not touch the edges, move all the sprites at the same time
    if (ovni.vecSprite[0].getPosition().getX() < (600-64+50) ||
        ovni.vecSprite[ovni.vecSprite.size() - 1].getPosition().getX() > 0+50){
        for(Sprite &sprite : ovni.vecSprite){
            moveSprite(sprite, ovni.rightOrLeft *10, 0);
        }
    }
     // If the sprites at the end touch the edges, change direction and move down the sprites by 10 pixels
    if(ovni.vecSprite[ovni.vecSprite.size() - 1].getPosition().getX() > (600-64+50) && ovni.rightOrLeft == 1){
        ovni.rightOrLeft = -1;
    }
    else if(ovni.vecSprite[0].getPosition().getX() < 0+50 && ovni.rightOrLeft == -1){
        ovni.rightOrLeft = 1;
    }
     // if the sprite vector reached the bottom, GAME OVER
    if(ovni.vecSprite[0].getPosition().getY()>(600)){
        addScore(playerLifeString, nameStr);
        credit(window,backgroundNoScreen,creditSprite);
        exit(0);
        }
}
