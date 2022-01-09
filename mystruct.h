#ifndef MYSTRUCT_H
#define MYSTRUCT_H

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

struct mugStruct {
    std::vector<nsGui::Sprite> vecMug;
    unsigned index;
};

struct enemy {
    std::vector<nsGui::Sprite> vecSprite;
    int rightOrLeft;
    std::vector<bool> state;
    void update(MinGL &window){
        for (unsigned i = 0; i < vecSprite.size(); ++i) {
            if (state[i]){
                window << vecSprite[i];
            }
        }
    }
};


struct players { //Structure for the scoreboard
    std::string player;
    unsigned point;
};

#endif // MYSTRUCT_H
