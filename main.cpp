#define FPS_LIMIT 60

#include <iostream>
#include <fstream>
#include <thread>

//CHANGER LES CHEMINS !!

#include "MinGL/include/mingl/mingl.h"

#include "MinGL/include/mingl/gui/sprite.h"

#include <MinGL/include/mingl/graphics/vec2d.h>

#include "MinGL/include/mingl/shape/rectangle.h"

#include "MinGL/include/mingl/gui/text.h"

#include "MinGL/include/mingl/shape/line.h"

#include <MinGL/include/mingl/gui/glut_font.h>

#include "MinGL/include/mingl/transition/transition_engine.h"

#include "MinGL/include/mingl/audio/audioengine.h"

//CHANGER LES CHEMINS !!

#include "bgtext.h"


using namespace std;
using namespace nsGraphics;
using namespace nsGui;
using namespace chrono;
using namespace nsAudio;


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

unsigned chooseTheme(MinGL &window, Sprite &image, unsigned &baseTheme)
{

    if (window.isPressed({'x', false})) {
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

unsigned entrerMenu(MinGL &window, Sprite &image)
{

    if (window.isPressed({'x', false})) {
        window.resetKey({'x', false});
        Vec2D position = image.getPosition();
        int mugY = position.getY();
        if (mugY == 585) {
            exit(0);
        }
        else if (mugY == 490) {
            return 3;
        }
        else if (mugY == 395) {
            return 2;
        }else if(mugY == 305){
            return 1;
        }

    }
    return 0;
}

void dessiner(MinGL &window, Sprite &image)
{
    window << image;
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

void choixLightDark (MinGL &window, unsigned &choixpsgom,Sprite &themelight, Sprite &themedark){
    if (choixpsgom == 0) {
        dessiner(window, themelight);
    }
    else {
        dessiner(window, themedark);
    }
}



Vec2D misPos;
Vec2D torPos;

struct mugStruct {
    vector<Sprite> vecMug;
    unsigned index;
};

struct enemy {
    vector<Sprite> vecSprite;
    int rightOrLeft;
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
void keyboard(MinGL &window, Sprite &mug)
{
    if (window.isPressed({'q', false}) && mug.getPosition().getX() > 50 ) {
        Vec2D position = mug.getPosition();
        int mugX = position.getX();
        int mugY = position.getY();
        Vec2D positionF (mugX-5, mugY);
        mug.setPosition(positionF);
    }
    if (window.isPressed({'d', false}) && mug.getPosition().getX() < (600-64+50)) {
        Vec2D position = mug.getPosition();
        int mugX = position.getX();
        int mugY = position.getY();
        Vec2D positionF (mugX+5, mugY);
        mug.setPosition(positionF);
    }
}
//Verify if an ennmy is still alive
bool allDead(const enemy & PPs) {
    for (size_t i = 0; i < PPs.state.size(); ++i) {
        //If the ennemy is alive
        if (PPs.state[i] == true) {
            return false;
        }
    }
    //There is no enemy alive anymore
    return true;
}

bool isTouching (const Vec2D firstCorner, const Vec2D secondCorner, const Vec2D test){
    return ((test.getX() <= secondCorner.getX() && test.getY() <= secondCorner.getY()) && (test.getX() >= firstCorner.getX() && test.getY() >= firstCorner.getY()));
}

bool colision(const Vec2D misPos, enemy &vecSprite){
    for (size_t i = 0; i < vecSprite.vecSprite.size(); ++i) {
        Vec2D a = vecSprite.vecSprite[i].getPosition();
        int bX = vecSprite.vecSprite[i].getPosition().getX()+55;
        int bY = vecSprite.vecSprite[i].getPosition().getY()+50;
        Vec2D b {bX,bY};
        if(isTouching(a,b,misPos) && (vecSprite.state[i] == true)) {
            vecSprite.state[i] = false;
            return true;
        }
    }
    return false;
}

bool missile(MinGL &window, Sprite &mug, enemy &IPPs, enemy &KPPs, enemy &JPPs, unsigned &playerLifeUnsigned, bool &firstShootM, bool &isPressed){
    if (window.isPressed({'x', false})){
        isPressed = true;
    }
    if (isPressed == true){
        if(firstShootM == true){//Si première apparition/clique
            Vec2D position = mug.getPosition();
            int mugX = position.getX();
            int mugY = position.getY();
            misPos.setX(mugX + 16);
            misPos.setY(mugY);
        }//Test si il y a colision avec la fenètre ou avec un enemi
        if (misPos.getY() <= 150){
            firstShootM = true;
            return isPressed = false;
        }
            else if (colision(misPos, IPPs) || colision(misPos, KPPs) || colision(misPos, JPPs)){
                ++playerLifeUnsigned;
                firstShootM = true;
                return isPressed = false;
            }
        firstShootM = false;
        misPos.setY(misPos.getY() - 16);
        return isPressed;
    }
    return false;
}

bool torpedo(mugStruct &mug, enemy &IPPs, bool &firstShootT){

    srand (time(NULL));
    int n = rand() % IPPs.vecSprite.size();

    if((firstShootT == true) && (IPPs.state[n] == true)){//Si première apparition et qu'il n'est pas détruit
        Vec2D position = IPPs.vecSprite[n].getPosition();
        int IPPsX = position.getX();
        int IPPsY = position.getY();
        torPos.setX(IPPsX + 16);
        torPos.setY(IPPsY);
    }//Test si il y a colision avec la fenètre ou le joueur

    Vec2D pos = mug.vecMug[mug.index].getPosition();
    int X = pos.getX() + 50;
    int Y = pos.getY() + 55;
    Vec2D posTwo = {X,Y};

    if(torPos.getY() >= 696){
        firstShootT = true;
        return false;
    }else if(isTouching(pos,posTwo,torPos)){
        firstShootT = true;
        if (mug.index < 4){
            int posX = mug.vecMug[mug.index].getPosition().getX();
            int posY = mug.vecMug[mug.index].getPosition().getY();
            ++mug.index;
            mug.vecMug[mug.index].setPosition({posX,posY});
        }
        else{
            cout << "1111111111" << endl;
            exit(0);
        }

        return false;
    }
    firstShootT = false;
    torPos.setY(torPos.getY() + 16);
    return true;
}

bool ovniShoot(mugStruct & mug, enemy & ovni, bool & ovniShootT, Vec2D & posTorOvni) {
    if ((ovniShootT == true) && (ovni.state[0] == true)) {
        Vec2D position = ovni.vecSprite[0].getPosition();
        int ovniX = position.getX();
        int ovniY = position.getY();
        posTorOvni.setX(ovniX + 16);
        posTorOvni.setY(ovniY);
    }

    Vec2D pos = mug.vecMug[mug.index].getPosition();
    int X = pos.getX() + 50;
    int Y = pos.getY() + 50;
    Vec2D posTwo = {X, Y};

    if (posTorOvni.getY() >= 696) {
        ovniShootT = true;
        return false;
    }
    else if (isTouching(pos, posTwo, posTorOvni)) {
        ovniShootT = true;
        if (mug.index < 4) {
            int posX = mug.vecMug[mug.index].getPosition().getX();
            int posY = mug.vecMug[mug.index].getPosition().getY();
            ++mug.index;
            mug.vecMug[mug.index].setPosition({posX, posY});
        }
        else {
            cout << "22222222222";
            exit(0);
        }

        return false;
    }

    ovniShootT = false;
    posTorOvni.setY(posTorOvni.getY() + 16);
    return true;
}

void move(Sprite &position, const int &x, const int &y) {
    position.setPosition(Vec2D(position.getPosition().getX() + x, position.getPosition().getY() + y));
}

void moveOpen(enemy & open) {
    if (open.vecSprite[0].getPosition().getX() < (600 - 470) || open.vecSprite[open.vecSprite.size() - 1].getPosition().getX() > 50) {
        for(Sprite & letter : open.vecSprite) {
            move(letter, open.rightOrLeft*5, 0);
        }
    }
    //Marche
    if (open.vecSprite[open.vecSprite.size() - 1].getPosition().getX() > (600 - 99) && open.rightOrLeft == 1) {
        open.rightOrLeft = -1;
        for (Sprite & letter : open.vecSprite) {
            move(letter, 0, 10);
        }
    }
    else if(open.vecSprite[0].getPosition().getX() <  (600 - 470) && open.rightOrLeft == -1) {
        open.rightOrLeft = 1;
        for (Sprite & letter : open.vecSprite) {
            move(letter, 0, 10);
        }
    }
    if (open.vecSprite[0].getPosition().getY() > 600) exit(0);
}
void moveVecSprite(enemy &vecSprite){
    // Si les sprites au extrémité ne touches pas les bords, bouger tout les sprites en même temps
    if (vecSprite.vecSprite[0].getPosition().getX() < (600-64+50) ||
        vecSprite.vecSprite[vecSprite.vecSprite.size() - 1].getPosition().getX() > 0+50){
        for(Sprite &sprite : vecSprite.vecSprite){
            move(sprite, vecSprite.rightOrLeft *5, 0);
        }
    }
    // Si les sprites au extrémité touches les bords, changer de direction et dessendre les sprites de 10 pixels
    if(vecSprite.vecSprite[vecSprite.vecSprite.size() - 1].getPosition().getX() > (600-64+50) && vecSprite.rightOrLeft == 1){
        vecSprite.rightOrLeft = -1;
        for(Sprite &sprite : vecSprite.vecSprite){
            move(sprite, 0, 10);
        }
    }else if(vecSprite.vecSprite[0].getPosition().getX() < 0+50 && vecSprite.rightOrLeft == -1){
        vecSprite.rightOrLeft = 1;
        for(Sprite &sprite : vecSprite.vecSprite){
            move(sprite, 0, 10);
        }
    }
    if(vecSprite.vecSprite[0].getPosition().getY()>(600)){
        exit(0);
        cout << "33333333333";
    }
}

void moveOVNI(enemy & ovni) {
    // Si les sprites au extrémité ne touches pas les bords, bouger tout les sprites en même temps
    if (ovni.vecSprite[0].getPosition().getX() < (600-64+50) ||
        ovni.vecSprite[ovni.vecSprite.size() - 1].getPosition().getX() > 0+50){
        for(Sprite &sprite : ovni.vecSprite){
            move(sprite, ovni.rightOrLeft *10, 0);
        }
    }
    // Si les sprites au extrémité touches les bords, changer de direction et dessendre les sprites de 10 pixels
    if(ovni.vecSprite[ovni.vecSprite.size() - 1].getPosition().getX() > (600-64+50) && ovni.rightOrLeft == 1){
        ovni.rightOrLeft = -1;
    }
    else if(ovni.vecSprite[0].getPosition().getX() < 0+50 && ovni.rightOrLeft == -1){
        ovni.rightOrLeft = 1;
    }
    if(ovni.vecSprite[0].getPosition().getY()>(600))exit(0);
}

void generateVecSprite(enemy &IPPs, const int posY, const string pathSprite){
    // liste de sprite
    for (size_t i = 0; i < 5; ++i) {
        Vec2D ipp;
        ipp.setX(50+124+72*i);
        ipp.setY(138+posY);
        Sprite sprite(pathSprite, ipp);
        IPPs.vecSprite.push_back(sprite);
        IPPs.state.push_back(true);
    }
}

void generateOPEN(enemy & open, const int posY) {
    //Generate letters one by one
    Vec2D firstO;
    firstO.setX(280);
    firstO.setY(138+posY);

    Vec2D p;
    p.setX(firstO.getX()+33);
    p.setY(138+posY);

    Vec2D e;
    e.setX(p.getX()+33);
    e.setY(138+posY);

    Vec2D n;
    n.setX(e.getX()+33);
    n.setY(138 + posY);

    Sprite spriteO("spritesi2/first-O.si2", firstO);
    Sprite spriteP("spritesi2/P.si2", p);
    Sprite spriteE("spritesi2/E.si2", e);
    Sprite spriteN("spritesi2/N.si2", n);

    //Gathers very sprite in a vector so we can add them to OPEN
    vector<Sprite> vecOPEN = {spriteO, spriteP, spriteP, spriteE, spriteN};
    for (size_t i = 0; i < vecOPEN.size(); ++i) {
        open.vecSprite.push_back(vecOPEN[i]);
        open.state.push_back(true);
    }
}

void generateCLASSROOM(enemy & classroom, const int posY) {
    //Generate all the letters one by one

    //Genretate C
    Vec2D c;
    c.setX(200);
    c.setY(105+posY);

    //Generate L
    Vec2D l;
    l.setX(c.getX()+33);
    //We use the .getX() of the previous letter
    l.setY(105+posY);

    //Generate A
    Vec2D a;
    a.setX(l.getX()+33);
    a.setY(105+posY);

    //Generate S
    Vec2D s;
    s.setX(a.getX()+33);
    s.setY(105+posY);

    //Generate the second S
    Vec2D sTwo;
    sTwo.setX(s.getX()+33);
    sTwo.setY(105+posY);

    //Generate R
    Vec2D r;
    r.setX(sTwo.getX()+33);
    r.setY(105+posY);

    //Generate O
    Vec2D o;
    o.setX(r.getX()+33);
    o.setY(105+posY);

    //Generate the second O
    Vec2D oTwo;
    oTwo.setX(o.getX()+33);
    oTwo.setY(105+posY);

    //Generate M
    Vec2D m;
    m.setX(oTwo.getX()+33);
    m.setY(105+posY);

    //Create sprites with the Vec2D
    Sprite spriteC("spritesi2/C.si2", c);
    Sprite spriteL("spritesi2/L.si2", l);
    Sprite spriteA("spritesi2/A.si2", a);
    Sprite spriteS("spritesi2/S.si2", s);
    Sprite spriteSTwo("spritesi2/S.si2", sTwo);
    Sprite spriteR("spritesi2/R.si2", r);
    Sprite spriteO("spritesi2/O.si2", o);
    Sprite spriteOTwo("spritesi2/O.si2", oTwo);
    Sprite spriteM("spritesi2/M.si2", m);

    //Gather all the sprites in a vector
    vector<Sprite> vecClassroom = {spriteC, spriteL, spriteA, spriteS, spriteSTwo, spriteR, spriteO, spriteOTwo, spriteM};

    //Adding all the sprite in the CLASSROOM vecSprite
    for (size_t i = 0; i < vecClassroom.size(); ++i) {
        classroom.vecSprite.push_back(vecClassroom[i]);
        classroom.state.push_back(true);
    }

}

void generateOVNI(enemy & ovni, const string pathSprite) {
    Vec2D vecOvni;
    vecOvni.setX(rand() % 559 + 50);
    vecOvni.setY(150);
    Sprite sprite(pathSprite, vecOvni);
    ovni.vecSprite.push_back(sprite);
    ovni.state.push_back(true);
}

void generateVecMug(mugStruct &mug){
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

    srand(time(NULL));

    enemy open;
    open.rightOrLeft = 1;
    generateOPEN(open, 50);

    enemy classroom;
    classroom.rightOrLeft = 1;
    generateCLASSROOM(classroom, 125);

    vector<enemy> vecOvni;
    for (size_t i = 0; i < 5; ++i) {
        enemy ovni;
        ovni.rightOrLeft = 1;
        generateOVNI(ovni, "spritesi2/OVNI.si2");
        vecOvni.push_back(ovni);
    }

    enemy IPPs;
    IPPs.rightOrLeft = 1;
    generateVecSprite(IPPs, 50, "spritesi2/i++.si2");

    enemy JPPs;
    JPPs.rightOrLeft = 1;
    generateVecSprite(JPPs, 100, "spritesi2/j++.si2");

    enemy KPPs;
    KPPs.rightOrLeft = 1;
    generateVecSprite(KPPs, 150, "spritesi2/k++.si2");

    mugStruct mug;
    generateVecMug(mug);
    mug.index = 0;
    mug.vecMug[mug.index].setPosition(Vec2D(50+284, 138+500));


    // Initialise le système
    MinGL window("CasaliShooter", Vec2D(700, 1000), Vec2D(50, 0), KBlack);
    window.initGlut();
    window.initGraphic();
    // Initialise toutes les images
    Sprite background("img/fondarcade.si2", Vec2D(0, 0));
    Sprite backgroundpsg("img/fond_psg.si2", Vec2D(0, 0));
    Sprite scoreboardbg("img/scoreboard.si2", Vec2D(125, 250));
    Sprite titrescoreboard("img/titrescore.si2", Vec2D(0, 0));
    Sprite titreaccueil("img/casaliheader.si2", Vec2D(155, 138));
    Sprite startb("img/start-button.si2", Vec2D(222, 283));
    Sprite scoreb("img/scoreboard-button.si2", Vec2D(222, 378));
    Sprite settingsb("img/options-button.si2", Vec2D(222, 473));
    Sprite quitb("img/quit-button.si2", Vec2D(222, 568));
    Sprite casali("img/casali.si2", Vec2D(160, 305));
    Sprite moon("img/moon.si2", Vec2D(160, 350));
    Sprite sun("img/sun.si2", Vec2D(400, 338));
    Sprite arrow("img/arrow.si2", Vec2D(188, 460));
    Sprite backb("img/back-button.si2", Vec2D(66, 666));

    BgText choosethemode(Vec2D(150, 240), "Choose between light and dark theme with a or z", KWhite, KBlack);
    nsTransition::TransitionEngine transitionEngine;


    // On démarre les transitions sur notre objet custom
    transitionEngine.startContract(nsTransition::TransitionContract(choosethemode, choosethemode.TRANSITION_TEXT_COLOR, chrono::seconds(1), {0, 0, 0},
                                                                    chrono::seconds::zero(), nsTransition::Transition::MODE_LOOP_SMOOTH));
    transitionEngine.startContract(nsTransition::TransitionContract(choosethemode, choosethemode.TRANSITION_BACKGROUND_COLOR, chrono::seconds(1), {255, 255, 0},
                                                                    chrono::seconds::zero(), nsTransition::Transition::MODE_LOOP_SMOOTH));

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();
    unsigned choixobjet=0;
    unsigned choixpsgom=0;



    unsigned playerLifeUnsigned = 0;
    bool firstShootM = true;
    bool isPressed = false;
    bool firstShootT = true;
    //Vecteur pour savoir si un ovni tire
    bool ovniTorOne = true;
    bool ovniTorTwo = true;
    bool ovniTorThree = true;
    bool ovniTorFour = true;
    bool ovniTorFive = true;
    //Vecteur des Vec2D pour le tire des torpedos des ovnis
    vector<Vec2D> vecOvniTorpedo;
    for (size_t i = 0; i < vecOvni.size(); ++i) {
        Vec2D ovniTor;
        vecOvniTorpedo.push_back(ovniTor);
    }

    AudioEngine PPsMusic;
    PPsMusic.setMusic("music/I_Attack.wav", true);
    PPsMusic.toggleMusicPlaying();

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        transitionEngine.update(frameTime);

        if (choixobjet==0) { //ouverture de l'écran d'accueil de casali shooter
            window.clearScreen();
            choixLightDark(window,choixpsgom, background, backgroundpsg);
            dessiner(window, titreaccueil);
            dessiner(window, startb);
            dessiner(window, scoreb);
            dessiner(window, settingsb);
            dessiner(window, quitb);
            dessiner(window, casali);
            menu(window, casali);
            choixobjet = entrerMenu(window, casali);
        }else if (choixobjet == 2){ //ouverture du menu scoreboard
            window.clearScreen();
            choixLightDark(window,choixpsgom, background, backgroundpsg);
            dessiner(window, scoreboardbg);
            dessiner(window, titrescoreboard);
            dessiner(window, backb);
            if (window.isPressed({'b', false})) {
                choixobjet = 0;
            }
            scoreboard(window);
        }else if (choixobjet == 3){ //ouverture du menu option
            window.clearScreen();
            choixLightDark(window,choixpsgom, background, backgroundpsg);
            window << choosethemode;
            dessiner(window, moon);
            dessiner(window, sun);
            dessiner(window, arrow);
            dessiner(window, backb);
            selectTheme(window, arrow);
            choixpsgom = chooseTheme(window, arrow, choixpsgom);
            if (window.isPressed({'b', false})) {
                choixobjet = 0;
            }
        }else if(choixobjet == 1){ // ouverture du jeu
            window.clearScreen();

            choixLightDark(window,choixpsgom, background, backgroundpsg);
            window << mug.vecMug[mug.index];

            IPPs.update(window);
            JPPs.update(window);
            KPPs.update(window);

            keyboard(window, mug.vecMug[mug.index]);

            moveVecSprite(IPPs);
            moveVecSprite(KPPs);
            moveVecSprite(JPPs);

            isPressed = missile(window, mug.vecMug[mug.index], IPPs, KPPs, JPPs, playerLifeUnsigned, firstShootM, isPressed);
            if(isPressed == true) window << nsShape::Rectangle(misPos, misPos + Vec2D(2, 10), KCyan);
            string playerLifeString = to_string(playerLifeUnsigned);
            //Points generator
            window << Text(Vec2D(60, 160), "Pts:", KWhite, GlutFont::BITMAP_9_BY_15);
            window << Text(Vec2D(100, 160), playerLifeString, KWhite, GlutFont::BITMAP_9_BY_15);

            if (torpedo(mug, IPPs, firstShootT)) window << nsShape::Rectangle(torPos, torPos + Vec2D(5, 10), KGreen);


            //Verify if enemies are still alive
            if (allDead(IPPs) && allDead(JPPs) && allDead(KPPs)) {
                PPsMusic.setMusicPlaying(false);
                AudioEngine openclassroomMusic;
                openclassroomMusic.setMusic("music/OCmusic.wav", true);
                openclassroomMusic.toggleMusicPlaying();
                while (!allDead(open) || !allDead(classroom)) {

                    // Récupère l'heure actuelle
                    //chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

                    window.clearScreen();

                    choixLightDark(window,choixpsgom, background, backgroundpsg);
                    window << mug.vecMug[mug.index];

                    keyboard(window, mug.vecMug[mug.index]);


                    for (size_t i = 0; i < vecOvni.size(); ++i) {
                        vecOvni[i].update(window);
                    }
                    open.update(window);
                    classroom.update(window);

                    //OPEN and CLASSROOM movements

                    for (size_t i = 0; i <  vecOvni.size(); ++i) {
                        moveOVNI(vecOvni[i]);
                    }
                    moveVecSprite(classroom);
                    moveOpen(open);

                    isPressed = missile(window, mug.vecMug[mug.index], open, classroom, JPPs, playerLifeUnsigned, firstShootM, isPressed);
                    if(isPressed == true) window << nsShape::Rectangle(misPos, misPos + Vec2D(2, 10), KCyan);
                    string playerLifeString = to_string(playerLifeUnsigned);
                    //Points generator
                    window << Text(Vec2D(60, 160), "Pts:", KWhite, GlutFont::BITMAP_9_BY_15);
                    window << Text(Vec2D(100, 160), playerLifeString, KWhite, GlutFont::BITMAP_9_BY_15);

                    //Open shooting
                    if (torpedo(mug, open, firstShootT)) window << nsShape::Rectangle(torPos, torPos + Vec2D(5, 10), KGreen);

                    //Ovnis shooting
                    if (ovniShoot(mug, vecOvni[0], ovniTorOne, vecOvniTorpedo[0])) window << nsShape::Rectangle(vecOvniTorpedo[0], vecOvniTorpedo[0] + Vec2D(5, 10), KGreen);
                    if (ovniShoot(mug, vecOvni[1], ovniTorTwo, vecOvniTorpedo[1])) window << nsShape::Rectangle(vecOvniTorpedo[1], vecOvniTorpedo[1] + Vec2D(5, 10), KGreen);
                    if (ovniShoot(mug, vecOvni[2], ovniTorThree, vecOvniTorpedo[2])) window << nsShape::Rectangle(vecOvniTorpedo[2], vecOvniTorpedo[2] + Vec2D(5, 10), KGreen);
                    if (ovniShoot(mug, vecOvni[3], ovniTorFour, vecOvniTorpedo[3])) window << nsShape::Rectangle(vecOvniTorpedo[3], vecOvniTorpedo[3] + Vec2D(5, 10), KGreen);
                    if (ovniShoot(mug, vecOvni[4], ovniTorFive, vecOvniTorpedo[4])) window << nsShape::Rectangle(vecOvniTorpedo[4], vecOvniTorpedo[4] + Vec2D(5, 10), KGreen);

                    // On finit la frame en cours
                    window.finishFrame();

                    // On vide la queue d'évènements
                    window.getEventManager().clearEvents();

                    // On attend un peu pour limiter le framerate et soulager le CPU
                    this_thread::sleep_for(chrono::milliseconds(2000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

                    // On récupère le temps de frame
                    frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);

                }
                openclassroomMusic.setMusicPlaying(false);
                break;
            }
        }

        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(2000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }


    return 0;
}
