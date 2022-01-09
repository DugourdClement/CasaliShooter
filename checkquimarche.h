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

#include "mystruct.h"

bool allDead(const enemy &);
bool isTouching (const nsGraphics::Vec2D, const nsGraphics::Vec2D, const nsGraphics::Vec2D);
bool colision(const nsGraphics::Vec2D, enemy &);
bool missile(MinGL &, nsGui::Sprite &, enemy &, enemy &, enemy &, unsigned &, bool &, bool &, nsGraphics::Vec2D &);
bool torpedo(mugStruct &, enemy &, bool &, nsGraphics::Vec2D &);
bool ovniShoot(mugStruct &, enemy &, bool &, nsGraphics::Vec2D &);

#endif // CHECK_H
