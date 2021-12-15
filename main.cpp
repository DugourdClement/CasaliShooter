#define FPS_LIMIT 60

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include<unistd.h>

#include "mingl/mingl.h"

#include "mingl/gui/sprite.h"

#include "mingl/graphics/vec2d.h"
#include "mingl/shape/rectangle.h"


using namespace std;
using namespace nsGraphics;
using namespace nsGui;
using namespace chrono;


Vec2D rectPos;

struct jeu {
    vector<Sprite> vecSprite;
    int droiteOuGauche;

    void update(MinGL &window){
        for (const auto &sprite : vecSprite) {
            window << sprite;
        }
    }
};

// Si on appuie sur une touche, le mug bouge
void clavier(MinGL &window, Sprite &sprite)
{
    if (window.isPressed({'q', false}) && sprite.getPosition().getX() > 50 ) {
        Vec2D position = sprite.getPosition();
        int mugX = position.getX();
        int mugY = position.getY();
        Vec2D positionF (mugX-5, mugY);
        sprite.setPosition(positionF);
    }
    if (window.isPressed({'d', false}) && sprite.getPosition().getX() < (600-64+50)) {
        Vec2D position = sprite.getPosition();
        int mugX = position.getX();
        int mugY = position.getY();
        Vec2D positionF (mugX+5, mugY);
        sprite.setPosition(positionF);
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

void tirer(MinGL &window, int mugX, int mugY)
{
    if (window.isPressed({'x', false})){
        Sprite missile("spritesi2/i++.si2", Vec2D(mugX, mugY - 32)); // 300 - taille sprite (32)/2 = 284
        Vec2D position = missile.getPosition();
        int misX = position.getX();
        int misY = position.getY();
        while(misY > -32){
            window << missile;
            Vec2D position = missile.getPosition();
            misY = position.getY();
            Vec2D positionF (misX, misY-30);
            missile.setPosition(positionF);
        }
    }
}

void move(Sprite &position, const int &x, const int &y) {
    position.setPosition(Vec2D(position.getPosition().getX() + x, position.getPosition().getY() + y));
}

void moveVecSprite(jeu &vecSprite){
    // bouger tout les sprites en même temps
    for(Sprite &sprite : vecSprite.vecSprite){
        move(sprite, vecSprite.droiteOuGauche *10, 0);
        if (sprite.getPosition().getX() > (600-64+50) && vecSprite.droiteOuGauche == 1) vecSprite.droiteOuGauche = -1;
        if (sprite.getPosition().getX() < 0+50 && vecSprite.droiteOuGauche == -1) vecSprite.droiteOuGauche = 1;
    }
}

void genereVecSprite(jeu &IPPs, const unsigned posY, const string pathSprite){
    // liste de sprite
    for (unsigned i = 0; i < 5; ++i) {
        Vec2D ipp;
        ipp.setX(50+124+72*i);
        ipp.setY(138+posY);
        Sprite sprite(pathSprite, ipp);
        IPPs.vecSprite.push_back(sprite);
    }
}

int main(){

    Sprite back("spritesi2/back.si2", Vec2D(0, 0)); // 300 - taille sprite (32)/2 = 284

    jeu IPPs;
    IPPs.droiteOuGauche = 1;
    genereVecSprite(IPPs, 50, "spritesi2/i++.si2");

    jeu KPPs;
    KPPs.droiteOuGauche = 1;
    genereVecSprite(KPPs, 100, "spritesi2/k++.si2");

    jeu JPPs;
    JPPs.droiteOuGauche = 1;
    genereVecSprite(JPPs, 150, "spritesi2/j++.si2");

    Sprite mug("spritesi2/mug-full-vie.si2", Vec2D(50+284, 138+500)); //

    // Initialise le système
    MinGL window("CasaliShooter", Vec2D(700, 1000), Vec2D(128, 128), KBlack);
    window.initGlut();
    window.initGraphic();

    // Variable qui tient le temps de frame
    microseconds frameTime = microseconds::zero();

    bool debut = true;
    bool isPressed = false;

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        time_point<steady_clock> start = steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // On affiche le fond et les sprites
        window << back;
        window << mug;

        IPPs.update(window);
        JPPs.update(window);
        KPPs.update(window);

        //tirer(window, mug);

        clavier(window, mug);

        moveVecSprite(IPPs);
        moveVecSprite(KPPs);
        moveVecSprite(JPPs);

        isPressed = clavierM(window, mug, debut, isPressed);
        dessiner(window);


        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(milliseconds(1000 / FPS_LIMIT) - duration_cast<microseconds>(steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = duration_cast<microseconds>(steady_clock::now() - start);
    }

    return 0;
}
