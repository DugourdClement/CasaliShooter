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

#include "move.h"
#include "mystruct.h"

using namespace std;
using namespace nsGraphics;
using namespace nsGui;
using namespace chrono;
using namespace nsAudio;

// If a key is pressed, the position of the mug is retrieved
// Add or remove 5 to the X position with Q and D ( move the mug ) 
void keyboard(MinGL &window, Sprite &mug)
{
    if (window.isPressed({'q', false}) && mug.getPosition().getX() > 50 ) {
        Vec2D position = mug.getPosition();
        int mugX = position.getX();
        int mugY = position.getY();
        Vec2D positionF (mugX-5, mugY);
        mug.setPosition(positionF);
    }
    if (window.isPressed({'d', false}) && mug.getPosition().getX() < (600-64+50)) {
        Vec2D position = mug.getPosition();
        int mugX = position.getX();
        int mugY = position.getY();
        Vec2D positionF (mugX+5, mugY);
        mug.setPosition(positionF);
    }
}

// Adds x and y to the coordinates of the sprite passed as parameters
void moveSprite(Sprite &position, const int &x, const int &y) {
    position.setPosition(Vec2D(position.getPosition().getX() + x, position.getPosition().getY() + y));
}

// Move the sprites of "open"
void moveOpen(enemy & open){
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
     if (open.vecSprite[0].getPosition().getY() > 600) exit(0);
}

void moveVecSprite(enemy &vecSprite){
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
        exit(0);
    }
}

void moveOVNI(enemy & ovni) {
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
    if(ovni.vecSprite[0].getPosition().getY()>(600))exit(0);
}
