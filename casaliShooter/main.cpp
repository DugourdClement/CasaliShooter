#define FPS_LIMIT 60

#include <iostream>
#include <thread>
#include <chrono>
#include<unistd.h>

#include "mingl/mingl.h"

#include "mingl/gui/sprite.h"

#include "mingl/graphics/vec2d.h"
#include "mingl/shape/rectangle.h"


using namespace std;

nsGraphics::Vec2D rectPos;

void clavier(MinGL &window, nsGui::Sprite &doggo)
{
    if (window.isPressed({'q', false})) {
        nsGraphics::Vec2D position = doggo.getPosition();
        int mugX = position.getX();
        int mugY = position.getY();
        nsGraphics::Vec2D positionF (mugX-2, mugY);
        doggo.setPosition(positionF);
    }
    if (window.isPressed({'d', false})) {
        nsGraphics::Vec2D position = doggo.getPosition();
        int mugX = position.getX();
        int mugY = position.getY();
        nsGraphics::Vec2D positionF (mugX+2, mugY);
        doggo.setPosition(positionF);
    }
}
void dessiner(MinGL &window, nsGui::Sprite &doggo)
{
    //sleep(1);
    // On dessine le rectangle
    window << doggo;
    chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
    this_thread::sleep_for(chrono::milliseconds(20000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

}
void tirer(MinGL &window, nsGui::Sprite &doggo){

    if (window.isPressed({'x', false})){
        nsGraphics::Vec2D position = doggo.getPosition();
        int mugX = position.getX();
        int mugY = position.getY();
        while(mugY > -32){
            nsGraphics::Vec2D position = doggo.getPosition();
            mugY = position.getY();
            nsGraphics::Vec2D positionF (mugX, mugY-30);
            doggo.setPosition(positionF);
            dessiner(window,doggo);
        }
    }
}

int main()
{

    // Initialise le système
    MinGL window("03 - Clavier", nsGraphics::Vec2D(600, 600), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();
    nsGui::Sprite doggo("spritesi2/mug-full-vie.si2", nsGraphics::Vec2D(284, 500)); // 300 - taille sprite (32)/2 = 284
    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // On fait tourner les procédures
        clavier(window, doggo);
        dessiner(window, doggo);
        tirer(window, doggo);

        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }

    return 0;
}
