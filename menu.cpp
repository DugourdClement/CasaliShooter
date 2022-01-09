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


using namespace std;
using namespace nsGraphics;
using namespace nsGui;
using namespace chrono;
using namespace nsAudio;

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

void dataSort(vector<string> &names, vector<unsigned> &scores){

    for(unsigned i=0;i<names.size();i++){

        for(unsigned j=0;j<names.size();j++){

            if(scores[i]>scores[j]){

                unsigned tempscore=scores[i];

                scores[i]=scores[j];

                scores[j]=tempscore;

                string tempname=names[i];

                names[i]=names[j];

                names[j]=tempname;

            }

        }

    }

}
//Displays the scores of the different players
void scoreboard(MinGL &window) {
    ifstream score_name("name.txt");

    vector<string> player;
    string name;
    while(score_name >> name)
        player.push_back(name);


    ifstream score_point("point.txt");

    vector<unsigned> score;
    unsigned points;
    while (score_point >> points)
        score.push_back(points);

    dataSort(player, score);

    remove("point.txt");
    ofstream outputFile;
    outputFile.open("point.txt");
    for (unsigned i = 0; i<score.size(); ++i) {
        outputFile << score[i] << endl;
    }
    remove("name.txt");
    ofstream outputFileName;
    outputFileName.open("name.txt");
    for (unsigned i = 0; i<player.size(); ++i) {
        outputFileName << player[i] << endl;
    }

    ifstream name_sort("name.txt");
    vector<string> sortedName;
    string sorted2;
    while(getline(name_sort,sorted2))
        sortedName.push_back(sorted2);

    ifstream score_sort("point.txt");
    vector<string> sortedScore;
    string sorted;
    while(getline(score_sort,sorted))
        sortedScore.push_back(sorted);

    for (unsigned i = 0; i<player.size(); ++i) {
        window << Text(Vec2D(200, 293+(50*i)), sortedName[i], KWhite, GlutFont::BITMAP_HELVETICA_18)
               << Text(Vec2D(539, 293+(50*i)), sortedScore[i], KWhite, GlutFont::BITMAP_HELVETICA_18);
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
