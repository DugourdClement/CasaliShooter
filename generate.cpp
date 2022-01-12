/**
* @file generate.cpp
* @brief Generate the sprites in the window
* @author Gonzales, Djerian, Leydier, Volpei, Dugourd
* @version 1.0
* @date 11/01/2022
*/

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

#include "generate.h"

using namespace std;
using namespace nsGraphics;
using namespace nsGui;
using namespace chrono;
using namespace nsAudio;

/** @brief Generate in the window IPPS,JPPS,KPPS
*
*@param[in] IPPs :
*@param[in] posY :
*@param[in] pathSprite :
*@returns void
*
*/
void generateVecSprite(enemyStruct &IPPs, const int posY, const string pathSprite){
    // liste de sprite
    for (size_t i = 0; i < 5; ++i) {
        Vec2D ipp;
        ipp.setX(50+124+72*i);
        ipp.setY(138+posY);
        Sprite sprite(pathSprite, ipp);
        IPPs.vecSprite.push_back(sprite);
        IPPs.state.push_back(true);
    }
}

/** @brief Generate in the window 'OPEN'
*
*@param[in] open : Correspond to open and his informations
*@param[in] posY : Correspond to a defined position
*@returns void
*
*/
void generateOPEN(enemyStruct & open, const int posY) {
    //Generate letters one by one
    Vec2D firstO;
    firstO.setX(280);
    firstO.setY(138+posY);

    Vec2D p;
    p.setX(firstO.getX()+33);
    p.setY(138+posY);

    Vec2D e;
    e.setX(p.getX()+33);
    e.setY(138+posY);

    Vec2D n;
    n.setX(e.getX()+33);
    n.setY(138 + posY);

    Sprite spriteO("spritesi2/first-O.si2", firstO);
    Sprite spriteP("spritesi2/P.si2", p);
    Sprite spriteE("spritesi2/E.si2", e);
    Sprite spriteN("spritesi2/N.si2", n);

    //Gathers very sprite in a vector so we can add them to OPEN
    vector<Sprite> vecOPEN = {spriteO, spriteP, spriteP, spriteE, spriteN};
    for (size_t i = 0; i < vecOPEN.size(); ++i) {
        open.vecSprite.push_back(vecOPEN[i]);
        open.state.push_back(true);
    }
}

/** @brief Generate in the window 'CLASSROOM'
*
*@param[in] classroom : Correspond to classroom and his informations
*@param[in] posY : Correspond to a defined position
*@returns void
*
*/
void generateCLASSROOM(enemyStruct & classroom, const int posY) {
    //Generate all the letters one by one

    //Genretate C
    Vec2D c;
    c.setX(200);
    c.setY(105+posY);

    //Generate L
    Vec2D l;
    l.setX(c.getX()+33);
    //We use the .getX() of the previous letter
    l.setY(105+posY);

    //Generate A
    Vec2D a;
    a.setX(l.getX()+33);
    a.setY(105+posY);

    //Generate S
    Vec2D s;
    s.setX(a.getX()+33);
    s.setY(105+posY);

    //Generate the second S
    Vec2D sTwo;
    sTwo.setX(s.getX()+33);
    sTwo.setY(105+posY);

    //Generate R
    Vec2D r;
    r.setX(sTwo.getX()+33);
    r.setY(105+posY);

    //Generate O
    Vec2D o;
    o.setX(r.getX()+33);
    o.setY(105+posY);

    //Generate the second O
    Vec2D oTwo;
    oTwo.setX(o.getX()+33);
    oTwo.setY(105+posY);

    //Generate M
    Vec2D m;
    m.setX(oTwo.getX()+33);
    m.setY(105+posY);

    //Create sprites with the Vec2D
    Sprite spriteC("spritesi2/C.si2", c);
    Sprite spriteL("spritesi2/L.si2", l);
    Sprite spriteA("spritesi2/A.si2", a);
    Sprite spriteS("spritesi2/S.si2", s);
    Sprite spriteSTwo("spritesi2/S.si2", sTwo);
    Sprite spriteR("spritesi2/R.si2", r);
    Sprite spriteO("spritesi2/O.si2", o);
    Sprite spriteOTwo("spritesi2/O.si2", oTwo);
    Sprite spriteM("spritesi2/M.si2", m);

    //Gather all the sprites in a vector
    vector<Sprite> vecClassroom = {spriteC, spriteL, spriteA, spriteS, spriteSTwo, spriteR, spriteO, spriteOTwo, spriteM};

    //Adding all the sprite in the CLASSROOM vecSprite
    for (size_t i = 0; i < vecClassroom.size(); ++i) {
        classroom.vecSprite.push_back(vecClassroom[i]);
        classroom.state.push_back(true);
    }

}

/** @brief Generate in the window 'OVNI'
*
*@param[in] ovni : Correspond to the UFO and their informations
*@param[in] posY : Correpsond to a defined position
*@returns void
*
*/
void generateOVNI(enemyStruct & ovni, const string pathSprite) {
    Vec2D vecOvni;
    vecOvni.setX(rand() % 559 + 50);
    vecOvni.setY(150);
    Sprite sprite(pathSprite, vecOvni);
    ovni.vecSprite.push_back(sprite);
    ovni.state.push_back(true);
}

/** @brief Generate in the window the mug
*
*@param[in] mug :
*@returns void
*
*/
void generateVecMug(mugStruct &mug){
    Sprite mug3("spritesi2/mug-full-vie.si2");
    Sprite mug2("spritesi2/mug-2-vies.si2");
    Sprite mug1("spritesi2/mug-1-vies.si2");
    Sprite mug0("spritesi2/mug-is-finito.si2");
    mug.vecMug.push_back(mug3);
    mug.vecMug.push_back(mug2);
    mug.vecMug.push_back(mug1);
    mug.vecMug.push_back(mug0);
}
