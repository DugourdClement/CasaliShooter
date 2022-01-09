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

#include "mystruct.h"
#include "check.h"

using namespace std;
using namespace nsGraphics;
using namespace nsGui;
using namespace chrono;
using namespace nsAudio;

//Verify if an ennmy is still alive
bool allDead(const enemy & PPs) {
    for (size_t i = 0; i < PPs.state.size(); ++i) {
        //If the ennemy is alive
        if (PPs.state[i] == true) {
            return false;
        }
    }
    //There is no enemy alive anymore
    return true;
}

bool isTouching (const Vec2D firstCorner, const Vec2D secondCorner, const Vec2D test){
    return ((test.getX() <= secondCorner.getX() && test.getY() <= secondCorner.getY()) && (test.getX() >= firstCorner.getX() && test.getY() >= firstCorner.getY()));
}

bool colision(const Vec2D misPos, enemy &vecSprite){
    for (size_t i = 0; i < vecSprite.vecSprite.size(); ++i) {
        Vec2D a = vecSprite.vecSprite[i].getPosition();
        int bX = vecSprite.vecSprite[i].getPosition().getX()+55;
        int bY = vecSprite.vecSprite[i].getPosition().getY()+50;
        Vec2D b {bX,bY};
        if(isTouching(a,b,misPos) && (vecSprite.state[i] == true)) {
            vecSprite.state[i] = false;
            return true;
        }
    }
    return false;
}

bool missile(MinGL &window, Sprite &mug, enemy &IPPs, enemy &KPPs, enemy &JPPs, unsigned &playerLifeUnsigned, bool &firstShootM, bool &isPressed, Vec2D &misPos){
    if (window.isPressed({'x', false})){
        isPressed = true;
    }
    if (isPressed == true){
        if(firstShootM == true){//Si première apparition/clique
            Vec2D position = mug.getPosition();
            int mugX = position.getX();
            int mugY = position.getY();
            misPos.setX(mugX + 16);
            misPos.setY(mugY);
        }//Test si il y a colision avec la fenètre ou avec un enemi
        if (misPos.getY() <= 150){
            firstShootM = true;
            return isPressed = false;
        }
            else if (colision(misPos, IPPs) || colision(misPos, KPPs) || colision(misPos, JPPs)){
                ++playerLifeUnsigned;
                firstShootM = true;
                return isPressed = false;
            }
        firstShootM = false;
        misPos.setY(misPos.getY() - 16);
        return isPressed;
    }
    return false;
}

bool torpedo(mugStruct &mug, enemy &IPPs, bool &firstShootT, Vec2D &torPos){

    srand (time(NULL));
    int n = rand() % IPPs.vecSprite.size();

    if((firstShootT == true) && (IPPs.state[n] == true)){//Si première apparition et qu'il n'est pas détruit
        Vec2D position = IPPs.vecSprite[n].getPosition();
        int IPPsX = position.getX();
        int IPPsY = position.getY();
        torPos.setX(IPPsX + 16);
        torPos.setY(IPPsY);
    }//Test si il y a colision avec la fenètre ou le joueur

    Vec2D pos = mug.vecMug[mug.index].getPosition();
    int X = pos.getX() + 50;
    int Y = pos.getY() + 55;
    Vec2D posTwo = {X,Y};

    if(torPos.getY() >= 696){
        firstShootT = true;
        return false;
    }else if(isTouching(pos,posTwo,torPos)){
        firstShootT = true;
        if (mug.index < 4){
            int posX = mug.vecMug[mug.index].getPosition().getX();
            int posY = mug.vecMug[mug.index].getPosition().getY();
            ++mug.index;
            mug.vecMug[mug.index].setPosition({posX,posY});
        }
        else{
            cout << "1111111111" << endl;
            exit(0);
        }

        return false;
    }
    firstShootT = false;
    torPos.setY(torPos.getY() + 16);
    return true;
}

bool ovniShoot(mugStruct & mug, enemy & ovni, bool & ovniShootT, Vec2D & posTorOvni) {
    if ((ovniShootT == true) && (ovni.state[0] == true)) {
        Vec2D position = ovni.vecSprite[0].getPosition();
        int ovniX = position.getX();
        int ovniY = position.getY();
        posTorOvni.setX(ovniX + 16);
        posTorOvni.setY(ovniY);
    }

    Vec2D pos = mug.vecMug[mug.index].getPosition();
    int X = pos.getX() + 50;
    int Y = pos.getY() + 50;
    Vec2D posTwo = {X, Y};

    if (posTorOvni.getY() >= 696) {
        ovniShootT = true;
        return false;
    }
    else if (isTouching(pos, posTwo, posTorOvni)) {
        ovniShootT = true;
        if (mug.index < 4) {
            int posX = mug.vecMug[mug.index].getPosition().getX();
            int posY = mug.vecMug[mug.index].getPosition().getY();
            ++mug.index;
            mug.vecMug[mug.index].setPosition({posX, posY});
        }
        else {
            cout << "22222222222";
            exit(0);
        }

        return false;
    }

    ovniShootT = false;
    posTorOvni.setY(posTorOvni.getY() + 16);
    return true;
}
