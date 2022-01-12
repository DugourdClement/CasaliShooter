#ifndef CHECK_H
#define CHECK_H

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

#include "mugstruct.h"
#include "playersStruct.h"
#include "enemyStruct.h"

bool allDead(const enemyStruct &);
bool isTouching (const nsGraphics::Vec2D, const nsGraphics::Vec2D, const nsGraphics::Vec2D);
bool colision(const nsGraphics::Vec2D, enemyStruct &);
bool missile(MinGL &, nsGui::Sprite &, enemyStruct &, enemyStruct &, enemyStruct &, unsigned &, bool &, bool &, nsGraphics::Vec2D &, std::vector<unsigned> &);
bool torpedo(mugStruct &, enemyStruct &, bool &, nsGraphics::Vec2D &, nsGui::Sprite &, nsGui::Sprite &, MinGL &);
bool ovniShoot(mugStruct &, enemyStruct &, bool &, nsGraphics::Vec2D &, nsGui::Sprite &, nsGui::Sprite &, MinGL &);

#endif // CHECK_H
