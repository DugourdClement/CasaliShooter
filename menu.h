#ifndef MENU_H
#define MENU_H

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

void selectTheme(MinGL &, nsGui::Sprite &);
unsigned chooseTheme(MinGL &, nsGui::Sprite &, unsigned &);
void menu(MinGL &window, nsGui::Sprite &);
unsigned entrerMenu(MinGL &, nsGui::Sprite &);
void dessiner(MinGL &, nsGui::Sprite &);
void choixLightDark (MinGL &, unsigned &,nsGui::Sprite &, nsGui::Sprite &);
void showScore(MinGL &);
bool isBetter(const players &, const players &);

#endif // MENU_H
