#ifndef GENERATE_H
#define GENERATE_H

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


void generateVecSprite(enemy &, const int, const std::string);
void generateOPEN(enemy &, const int);
void generateCLASSROOM(enemy &, const int);
void generateOVNI(enemy &, const std::string);
void generateVecMug(mugStruct &);

#endif // GENERATE_H
