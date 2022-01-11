/**
* @file menu.h
* @brief Gestion du menu
* @author Gonzales, Djerian, Leydier, Volpei, Dugourd
* @version 1.0
* @date 11/01/2022
*/

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

#include "mugstruct.h"
#include "playersStruct.h"
#include "enemyStruct.h"

/** @brief Selects the theme and moves the **cursor**
*
*@param[in] window 
*@param[in] image Cursor that moves according to the selection
*@return void
*
*/
void selectTheme(MinGL &, nsGui::Sprite &);

/** @brief Change theme to **theme select**
*
*@param[in] window 
*@param[in] image 
*@param[in] baseTheme
*@return void
*
*/
unsigned chooseTheme(MinGL &, nsGui::Sprite &, unsigned &);

/** @brief Change the place of the cursor in the menu
*
*@param[in] window 
*@param[in] image 
*@return void
*
*/
void menu(MinGL &window, nsGui::Sprite &);

/** @brief Choice of **menu**
*
*@param[in] window 
*@param[in] image 
*@return unsigned
*
*/
unsigned entrerMenu(MinGL &, nsGui::Sprite &);
void dessiner(MinGL &, nsGui::Sprite &);
/** @brief Applies the **selected theme**
*
*@param[in] window 
*@param[in] choixpsgom 
*@param[in] themelight OM choice Background
*@param[in] themedark PSG choice Background
*@return void
*
*/
void choixLightDark (MinGL &, unsigned &,nsGui::Sprite &, nsGui::Sprite &);

/** @brief Function which shows the **scoreboard**
*
*@param[in] window MinGL
*@return void
*
*/
void showScore(MinGL &);

/** @brief Bool used to **sort player**
*
*@param joueur1 
*@param joueur2 
*@return bool
*
*/
bool isBetter(const playersStruct &, const playersStruct &);

#endif // MENU_H
