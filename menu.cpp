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

#include "bgtext.h"
#include "menu.h"
#include "mystruct.h"


using namespace std;
using namespace nsGraphics;
using namespace nsGui;
using namespace chrono;
using namespace nsAudio;

struct players { //Structure for the scoreboard
    string player;
    unsigned point;
};

void addScore(string &playerLifeString, string &nameStr){
    string line;
    fstream ofs;
    ofs.open("score.txt", ios_base::app);
    if(ofs.is_open()){
        ofs << nameStr << " " << playerLifeString << endl;
    }
}

//// Selects the theme and moves the cursor
void selectTheme(MinGL &window, Sprite &image)
{
        if (window.isPressed({'a', false})) {
            Vec2D position = image.getPosition();
            int arrowX = 188;
            int arrowY = position.getY();
            Vec2D positionF (arrowX, arrowY);
            image.setPosition(positionF);
        }
        else if (window.isPressed({'z', false})) {
            Vec2D position = image.getPosition();
            int arrowX = 435;
            int arrowY = position.getY();
            Vec2D positionF (arrowX, arrowY);
            image.setPosition(positionF);
        }
}

//Change theme to theme select
unsigned chooseTheme(MinGL &window, Sprite &image, unsigned &baseTheme)
{

    if (window.isPressed({'"', false})) {
        Vec2D position = image.getPosition();
        int arrowX = position.getX();
        if (arrowX == 188) {
            return 1;
        }
        else {
            return 0;
        }
    }
    return baseTheme;
}

//Change the place of the cursor in the menu
void menu(MinGL &window, Sprite &image)
{
        if (window.isPressed({'a', false})) {
            Vec2D position = image.getPosition();
            int mugX = position.getX();
            int mugY = 305;
            Vec2D positionF (mugX, mugY);
            image.setPosition(positionF);
        }
        else if (window.isPressed({'z', false})) {
            Vec2D position = image.getPosition();
            int mugX = position.getX();
            int mugY = 395;
            Vec2D positionF (mugX, mugY);
            image.setPosition(positionF);
        }
        else if (window.isPressed({'e', false})) {
            Vec2D position = image.getPosition();
            int mugX = position.getX();
            int mugY = 490;
            Vec2D positionF (mugX, mugY);
            image.setPosition(positionF);
        }
        else if (window.isPressed({'r', false})) {
            Vec2D position = image.getPosition();
            int mugX = position.getX();
            int mugY = 585;
            Vec2D positionF (mugX, mugY);
            image.setPosition(positionF);
        }
}

// Choice of menu
unsigned entrerMenu(MinGL &window, Sprite &image)
{

    if (window.isPressed({'"', false})) {
        window.resetKey({'"', false});
        Vec2D position = image.getPosition();
        int mugY = position.getY();
        if (mugY == 585) {
            exit(0); // quitter
        }
        else if (mugY == 490) {
            return 3; //menu 3
        }
        else if (mugY == 395) {
            return 2; // menu 2
        }else if(mugY == 305){
            return 1; // menu 1
        }

    }
    return 0;
}

bool isBetter (const players & joueur1, const players & joueur2){ // Bool used to sort player
    return joueur1.point >= joueur2.point;
}

void showScore(MinGL & window) //Function which shows the scoreboard
{
    ifstream data_file("name.txt");
    vector<players> playerScore;
    players playerStruc;
    while (data_file >> playerStruc.player >> playerStruc.point) { //Place every elements of the file in the structure
        playerScore.emplace_back(playerStruc);
    }
    sort (playerScore.begin (), playerScore.end(), isBetter); // Sort all players by their score
    vector<string> stringScore;
    if (playerScore.size()>10) { //Make that the structure only retains the 10 best players
        playerScore.resize(10);
    }
    for (size_t i = 0; i<playerScore.size(); ++i) { //Place every score and player on the screen
        stringScore.push_back(to_string(playerScore[i].point)); //Transform the score of the players into String so i can use nsGui::Text to show them
        window << nsGui::Text(nsGraphics::Vec2D(190, 294+(30*i)), playerScore[i].player, nsGraphics::KWhite, nsGui::GlutFont::BITMAP_9_BY_15)
               << nsGui::Text(nsGraphics::Vec2D(525, 294+(30*i)), stringScore[i], nsGraphics::KWhite, nsGui::GlutFont::BITMAP_9_BY_15);
    }
}

//Applies the selected theme
void choixLightDark (MinGL &window, unsigned &choixpsgom,Sprite &themelight, Sprite &themedark){
    if (choixpsgom == 0) {
        window << themelight;
    }
    else {
        window << themedark;
    }
}
