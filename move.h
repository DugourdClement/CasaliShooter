#ifndef MOVE_H
#define MOVE_H

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

void moveSprite(nsGui::Sprite &, const int &, const int &);
void moveOpen(enemy &);
void moveVecSprite(enemy &);
void moveOVNI(enemy &);
void keyboard(MinGL &, nsGui::Sprite &);

#endif // MOVE_H
