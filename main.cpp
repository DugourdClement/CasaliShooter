#define FPS_LIMIT 60

#include <iostream>
#include <thread>
#include <chrono>
#include<unistd.h>

#include "mingl/shape/rectangle.h"

#include "MinGL/include/mingl/mingl.h"

#include "MinGL/include/mingl/gui/sprite.h"

#include <MinGL/include/mingl/graphics/vec2d.h>

#include "MinGL/include/mingl/shape/rectangle.h"


using namespace std;
using namespace nsGraphics;

Vec2D rectPos;

void clavier(MinGL &window, nsGui::Sprite &mug)
{
    if (window.isPressed({'q', false})) {
        Vec2D position = mug.getPosition();
        int mugX = position.getX();
        int mugY = position.getY();
        if (!(mugX < 0)) {
             mugX = mugX-2;
             Vec2D positionF (mugX, mugY);
             mug.setPosition(positionF);
          }
    }
    if (window.isPressed({'d', false})) {
        Vec2D position = mug.getPosition();
        int mugX = position.getX();
        int mugY = position.getY();
        if (!(mugX > 568)) {
            mugX = mugX+2;
            Vec2D positionF (mugX, mugY);
            mug.setPosition(positionF);
        }
    }
}

void dessiner(MinGL &window)
{
    // On dessine le rectangle
        window << nsShape::Rectangle(rectPos, rectPos + nsGraphics::Vec2D(2, 10), nsGraphics::KCyan);
}

void deplacement(){
    rectPos.setY(rectPos.getY() - 16);
}

bool clavierM(MinGL &window, nsGui::Sprite &mug, bool &debut, bool &isPressed)
{
    if (window.isPressed({'x', false})){
        isPressed = true;
    }
    if (isPressed == true){
        if(debut == true){
            Vec2D position = mug.getPosition();
            int mugX = position.getX();
            int mugY = position.getY();
            rectPos.setX(mugX + 16);
            rectPos.setY(mugY);
        }
        debut = false;
        deplacement();
    }
    return isPressed;
}


/*
void affichage (nsGui::Sprite &missile, int misX, int misY){
    Vec2D positionF (misX, misY - 16);
    missile.setPosition(positionF);
}

void dessiner(MinGL &window, int mugX, int mugY)
{
    nsGui::Sprite missile("spritesi2/i++.si2", Vec2D(mugX, mugY - 32)); // 300 - taille sprite (32)/2 = 284
    window << missile;
}

bool tirer(MinGL &window)
{
    bool xPressed = false;
    if (window.isPressed({'x', false})){
        xPressed = true;
    }
    if (xPressed == true){
        Vec2D position = missile.getPosition();
        int misX = position.getX();
        int misY = position.getY();
        if (misY == -32) return false;
        Vec2D positionF (misX, misY - 16);
        missile.setPosition(positionF);
        return true;
    }
}
*/



int main()
{

    // Initialise le système
    MinGL window("03 - Clavier", Vec2D(600, 600), Vec2D(128, 128), KBlack);
    window.initGlut();
    window.initGraphic();

    nsGui::Sprite mug("spritesi2/mug-full-vie.si2", Vec2D(284, 500));// 300 - taille sprite (32)/2 = 284
    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    bool debut = true;
    bool isPressed = false;

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // On fait tourner les procédures
        clavier(window, mug);
        window << mug;

/*
        //Récupération des coords de mug
        bool missileIn = false;
        Vec2D position = mug.getPosition();
        int mugX = position.getX();
        int mugY = position.getY();
        missileIn = tirer(window);
        if (missileIn == true) dessiner(window, mugX, mugY);
*/

        isPressed = clavierM(window, mug, debut, isPressed);
        dessiner(window);

        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(2500 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }
//ON COMPTE LES FRAMES
    return 0;
}
