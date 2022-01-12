#ifndef MOVE_H
#define MOVE_H

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

#include "mugstruct.h"
#include "playersStruct.h"
#include "enemyStruct.h"
#include "yaml.h"

void moveSprite(nsGui::Sprite &, const int &, const int &);
void moveOpen(enemyStruct &, std::string &, std::string &, nsGui::Sprite &, nsGui::Sprite &, MinGL &);
void moveVecSprite(enemyStruct &, std::string &, std::string &, nsGui::Sprite &, nsGui::Sprite &, MinGL &);
void moveOVNI(enemyStruct &, std::string &, std::string &, nsGui::Sprite &, nsGui::Sprite &, MinGL &);
void keyboard(MinGL &, nsGui::Sprite &, std::vector<unsigned>);

#endif // MOVE_H
