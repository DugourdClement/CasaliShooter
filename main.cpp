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
using namespace nsGui;
using namespace chrono;

Vec2D misPos;

struct posEn{
    Vec2D positionXY;
    Vec2D positionXYbis;
};

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


void dessiner(MinGL &window){
    // On dessine le rectangle
        window << nsShape::Rectangle(misPos, misPos + nsGraphics::Vec2D(2, 10), nsGraphics::KCyan);
}

void deplacement(){
    misPos.setY(misPos.getY() - 16);
}

bool clavierM(MinGL &window, nsGui::Sprite &mug, jeu &vecSprite, bool &debut, bool &isPressed){
    if (window.isPressed({'x', false})){
        isPressed = true;
    }
    if (isPressed == true){
        if(debut == true){//Si première apparition/clique
            Vec2D position = mug.getPosition();
            int mugX = position.getX();
            int mugY = position.getY();
            misPos.setX(mugX + 16);
            misPos.setY(mugY);
        }//Test si il y a colision avec la fenètre
        if (misPos.getY() <= 150){
            debut = true;
            return isPressed = false;
        }
        else{ //Test si il y a colision avec un enemi
            for (unsigned i = 0; i < vecSprite.vecSprite.size(); ++i) {
                Vec2D a = vecSprite.vecSprite[i].getPosition();
                int bX = vecSprite.vecSprite[i].getPosition().getX()+64;
                int bY = vecSprite.vecSprite[i].getPosition().getY()+64;
                Vec2D b(bX,bY);
                if(misPos.isColliding(150, 600) == true){
                    debut = true;
                    return isPressed = false;
                }
            }
        }
        debut = false;
        deplacement();
        return isPressed;
    }
}

void move(Sprite &position, const int &x, const int &y) {
    position.setPosition(Vec2D(position.getPosition().getX() + x, position.getPosition().getY() + y));
}

void moveVecSprite(jeu &vecSprite){
    // Si les sprites au extrémité ne touches pas les bords, bouger tout les sprites en même temps
    if (vecSprite.vecSprite[0].getPosition().getX() < (600-64+50) ||
        vecSprite.vecSprite[4].getPosition().getX() > 0+50){
        for(Sprite &sprite : vecSprite.vecSprite){
            move(sprite, vecSprite.droiteOuGauche *5, 0);
        }
    }
    // Si les sprites au extrémité touches les bords, changer de direction et dessendre les sprites de 10 pixels
    if(vecSprite.vecSprite[4].getPosition().getX() > (600-64+50) && vecSprite.droiteOuGauche == 1){
        vecSprite.droiteOuGauche = -1;
        for(Sprite &sprite : vecSprite.vecSprite){
            move(sprite, 0, 10);
        }
    }else if(vecSprite.vecSprite[0].getPosition().getX() < 0+50 && vecSprite.droiteOuGauche == -1){
        vecSprite.droiteOuGauche = 1;
        for(Sprite &sprite : vecSprite.vecSprite){
            move(sprite, 0, 10);
        }
    }
    if(vecSprite.vecSprite[0].getPosition().getY()>(600))exit(0);
}

void genereVecSprite(jeu &IPPs, const int posY, const string pathSprite){
    // liste de sprite
    for (int i = 0; i < 5; ++i) {
        Vec2D ipp;
        ipp.setX(50+124+72*i);
        ipp.setY(138+posY);
        Sprite sprite(pathSprite, ipp);
        IPPs.vecSprite.push_back(sprite);
    }
}


int main()
{

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
    chrono::microseconds frameTime = chrono::microseconds::zero();

    bool debut = true;
    bool isPressed = false;


    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen()){
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // On fait tourner les procédures
        window << back;
        window << mug;

        IPPs.update(window);
        JPPs.update(window);
        KPPs.update(window);


        clavier(window, mug);

        moveVecSprite(IPPs);
        moveVecSprite(KPPs);
        moveVecSprite(JPPs);


        isPressed = clavierM(window, mug, IPPs, debut, isPressed);
        if(isPressed == true) dessiner(window);

        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(3000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }
    return 0;
}
