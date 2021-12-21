#define FPS_LIMIT 60

#include <iostream>
#include <thread>
#include <chrono>
#include<unistd.h>
#include <ctime>

#include "mingl/gui/text.h"

#include "mingl/shape/line.h"

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
Vec2D torPos;

struct mugStruct {
    vector<Sprite> vecMug;
    unsigned index;
};

struct ennemi {
    vector<Sprite> vecSprite;
    int droiteOuGauche;
    vector<bool> state;
    void update(MinGL &window){
        for (unsigned i = 0; i < vecSprite.size(); ++i) {
            if (state[i]){
                window << vecSprite[i];
            }
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

bool CATOUCHE (const Vec2D a, const Vec2D b, const Vec2D test){
    return ((test.getX() <= b.getX() && test.getY() <= b.getY()) && (test.getX() >= a.getX() && test.getY() >= a.getY()));
}

bool colision(const Vec2D misPos, ennemi &vecSprite){
    for (unsigned i = 0; i < vecSprite.vecSprite.size(); ++i) {
        Vec2D a = vecSprite.vecSprite[i].getPosition();
        int bX = vecSprite.vecSprite[i].getPosition().getX()+55;
        int bY = vecSprite.vecSprite[i].getPosition().getY()+50;
        Vec2D b {bX,bY};
        if(CATOUCHE(a,b,misPos) && (vecSprite.state[i] == true)) {
            vecSprite.state[i] = false;
            return true;
        }
    }
    return false;
}

void dessiner(MinGL &window, const char c){
    if (c == 'm')window << nsShape::Rectangle(misPos, misPos + Vec2D(2, 10), KCyan);
    if (c == 't') window << nsShape::Rectangle(torPos, torPos + Vec2D(5, 10), KGreen);
}

bool missile(MinGL &window, nsGui::Sprite &mug, ennemi &IPPs, ennemi &KPPs, ennemi &JPPs, unsigned &ptsJoueur, bool &debut, bool &isPressed){
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
        }//Test si il y a colision avec la fenètre ou avec un enemi
        if (misPos.getY() <= 150){
            debut = true;
            return isPressed = false;
        }
            else if (colision(misPos, IPPs) || colision(misPos, KPPs) || colision(misPos, JPPs)){
                ++ptsJoueur;
                debut = true;
                return isPressed = false;
            }
        debut = false;
        misPos.setY(misPos.getY() - 16);
        return isPressed;
    }
    return false;
}

bool torpedo(mugStruct &mug, ennemi &IPPs, bool &firstShootT){

    srand (time(NULL));
    int ale = rand() % 6;

    if(firstShootT == true){//Si première apparition/clique
        Vec2D position = IPPs.vecSprite[ale].getPosition();
        int IPPsX = position.getX();
        int IPPsY = position.getY();
        torPos.setX(IPPsX + 16);
        torPos.setY(IPPsY);
    }//Test si il y a colision avec la fenètre ou si il y a colision avec un enemi

    Vec2D pos = mug.vecMug[mug.index].getPosition();
    int X = pos.getX() + 50;
    int Y = pos.getY() + 55;
    Vec2D pos2 = {X,Y};

    if(torPos.getY() >= 696){
        firstShootT = true;
        return false;
    }else if(CATOUCHE(pos,pos2,torPos)){
        firstShootT = true;
        if (mug.index < 4){
            int posX = mug.vecMug[mug.index].getPosition().getX();
            int posY = mug.vecMug[mug.index].getPosition().getY();
            mug.index += 1;
            mug.vecMug[mug.index].setPosition({posX,posY});
        }else{
            exit(0);
        }

        return false;
    }
    firstShootT = false;
    torPos.setY(torPos.getY() + 16);
    return true;
}

void move(Sprite &position, const int &x, const int &y) {
    position.setPosition(Vec2D(position.getPosition().getX() + x, position.getPosition().getY() + y));
}

void moveVecSprite(ennemi &vecSprite){
    // Si les sprites au extrémité ne touches pas les bords, bouger tout les sprites en même temps
    if (vecSprite.vecSprite[0].getPosition().getX() < (600-64+50) ||
        vecSprite.vecSprite[vecSprite.vecSprite.size() - 1].getPosition().getX() > 0+50){
        for(Sprite &sprite : vecSprite.vecSprite){
            move(sprite, vecSprite.droiteOuGauche *5, 0);
        }
    }
    // Si les sprites au extrémité touches les bords, changer de direction et dessendre les sprites de 10 pixels
    if(vecSprite.vecSprite[vecSprite.vecSprite.size() - 1].getPosition().getX() > (600-64+50) && vecSprite.droiteOuGauche == 1){
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

void genereVecSprite(ennemi &IPPs, const int posY, const string pathSprite){
    // liste de sprite
    for (int i = 0; i < 5; ++i) {
        Vec2D ipp;
        ipp.setX(50+124+72*i);
        ipp.setY(138+posY);
        Sprite sprite(pathSprite, ipp);
        IPPs.vecSprite.push_back(sprite);
        IPPs.state.push_back(true);
    }
}

void genereVecMug(mugStruct &mug){
    Sprite mug3("spritesi2/mug-full-vie.si2");
    Sprite mug2("spritesi2/mug-2-vies.si2");
    Sprite mug1("spritesi2/mug-1-vies.si2");
    Sprite mug0("spritesi2/mug-is-finito.si2");
    mug.vecMug.push_back(mug3);
    mug.vecMug.push_back(mug2);
    mug.vecMug.push_back(mug1);
    mug.vecMug.push_back(mug0);
}

void win(MinGL &window){
    window.clearScreen();
    exit(0);
}


int main()
{

    Sprite back("spritesi2/back.si2", Vec2D(0, 0));

    ennemi IPPs;
    IPPs.droiteOuGauche = 1;
    genereVecSprite(IPPs, 50, "spritesi2/i++.si2");

    ennemi KPPs;
    KPPs.droiteOuGauche = 1;
    genereVecSprite(KPPs, 100, "spritesi2/k++.si2");

    ennemi JPPs;
    JPPs.droiteOuGauche = 1;
    genereVecSprite(JPPs, 150, "spritesi2/j++.si2");

    mugStruct mug;
    genereVecMug(mug);
    mug.index = 0;
    mug.vecMug[mug.index].setPosition(Vec2D(50+284, 138+500));

    // Initialise le système
    MinGL window("CasaliShooter", Vec2D(700, 1000), Vec2D(128, 128), KBlack);
    window.initGlut();
    window.initGraphic();


    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    unsigned ptsJoueur = 0;
    bool debut = true;
    bool isPressed = false;
    bool firstShootT = true;


    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen()){
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // On fait tourner les procédures
        window << back;
        window << mug.vecMug[mug.index];

        IPPs.update(window);
        JPPs.update(window);
        KPPs.update(window);


        clavier(window, mug.vecMug[mug.index]);

        moveVecSprite(IPPs);
        moveVecSprite(KPPs);
        moveVecSprite(JPPs);


        isPressed = missile(window, mug.vecMug[mug.index], IPPs, KPPs, JPPs,ptsJoueur, debut, isPressed);
        if(isPressed == true) dessiner(window, 'm');
        string pts = to_string(ptsJoueur);
        window << Text(nsGraphics::Vec2D(60, 160), "Pts:", nsGraphics::KWhite, nsGui::GlutFont::BITMAP_9_BY_15);
        window << Text(nsGraphics::Vec2D(100, 160), pts, nsGraphics::KWhite, nsGui::GlutFont::BITMAP_9_BY_15);

        if (torpedo(mug, IPPs, firstShootT)) dessiner(window, 't');

        if (ptsJoueur == 15) win(window);



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
