/**
 *
 * @file    mingl.h
 * @author  Alexandre Sollier, Clément Mathieu--Drif, Alain Casali
 * @date    Janvier 2020
 * @version 2.0
 * @brief   La bête
 *
 **/

#ifndef MINGL_H
#define MINGL_H

#include <map>
#include <memory> // shared_ptr
#include <queue>
#include <string>
#include <vector>

#include <GL/freeglut.h>

#include "graphics/idrawable.h"
#include "graphics/rgbacolor.h"
#include "graphics/vec2d.h"

#include "event/event_manager.h"

/**
 * @brief Classe de base de minGL 2
 */

// Pour les polices et l'affichage des chaines de caractères, voir: https://www.opengl.org/resources/libraries/glut/spec3/node76.html

class MinGL
{

public:
    /**
     * @brief KeyType_t : Représente une touche du clavier
     * @details C'est une paire de nombre entier naturel et booléen <br>
     *          <ul><li> L'entier naturel représente le caractère pour une touche non spéciale,
     *                   ou l'identifiant de touche pour une touche spéciale
     *                   (<a href="https://www.opengl.org/resources/libraries/glut/spec3/node54.html">Voir ici</a> pour les identifiants). </li>
     *              <li> Le booléen indique si la touche est spéciale ou non.</li></ul>
     *
     */
    typedef std::pair<unsigned, bool> KeyType_t; // cle, spécial

    /**
     *
     * @brief   KeyMap_t : Map représentant des touches et leurs état (pressée ou non).
     * @details La clé de cette map est un @ref KeyType_t représentant une touche, et la valeur est son état.
     *
     */
    typedef std::map<KeyType_t, bool> KeyMap_t;

    /**
     * @brief Constructeur pour la classe MinGL
     * @param[in] name : Nom de la fenêtre
     * @param[in] windowSize : Taille de la fenêtre
     * @param[in] windowPosition : Position de la fenêtre
     * @param[in] backgroundColor : Couleur de fond de la fenêtre
     * @fn MinGL(const std::string& name, const nsGraphics::Vec2D& windowSize = nsGraphics::Vec2D(640, 480),
     *    const nsGraphics::Vec2D& windowPosition = nsGraphics::Vec2D(128, 128),
     *    const nsGraphics::RGBAcolor& backgroundColor = nsGraphics::KWhite);
     */
    MinGL(const std::string& name, const nsGraphics::Vec2D& windowSize = nsGraphics::Vec2D(640, 480),
          const nsGraphics::Vec2D& windowPosition = nsGraphics::Vec2D(128, 128),
          const nsGraphics::RGBAcolor& backgroundColor = nsGraphics::KWhite);

    /**
     * @brief Destructeur de la classe MinGL
     * @fn ~MinGL();
     */
    ~MinGL();

    /**
     * @brief Initialise la bibliothèque freeglut
     * @fn static void initGlut()
     */
    static void initGlut()
    {
        int tmp = 0;
        glutInit(&tmp, NULL);
    }

    /**
     * @brief Initialise minGL et ouvre la fenêtre
     * @fn void initGraphic();
     */
    void initGraphic();

    /**
     * @brief Ferme la fenêtre et minGL proprement
     * @fn void stopGraphic();
     */
    void stopGraphic();

    /**
     * @brief Renvoie l'état d'une touche du clavier (pressée ou non)
     * @param[in] key : Touche du clavier a vérifier
     * @fn bool isPressed(const KeyType_t& key);
     */
    bool isPressed(const KeyType_t& key);

    /**
     * @brief Force une touche a être relâchée
     * @param[in] key : Touche du clavier a relâcher
     * @fn void resetKey(const KeyType_t& key);
     */
    void resetKey(const KeyType_t& key);

    /**
     * @brief Préviens minGL que la frame est terminée
     * @fn void finishFrame();
     */
    void finishFrame();

    /**
     * @brief Efface l'écran avec la couleur de fond spécifiée
     * @fn void clearScreen();
     */
    void clearScreen();

    /**
     * @brief Récupère le gestionnaire d'évènements minGL
     * @fn nsEvent::EventManager& getEventManager();
     */
    nsEvent::EventManager& getEventManager();

    /**
     * @brief Récupère la couleur de fond de la fenêtre
     * @fn const nsGraphics::RGBAcolor& getBackgroundColor() const;
     */
    const nsGraphics::RGBAcolor& getBackgroundColor() const;

    /**
     * @brief Règle la couleur de fond de la fenêtre
     * @fn void setBackgroundColor(const nsGraphics::RGBAcolor& backgroundColor);
     */
    void setBackgroundColor(const nsGraphics::RGBAcolor& backgroundColor);

    /**
     * @brief Récupère la taille de la fenêtre
     * @fn nsGraphics::Vec2D getWindowSize() const;
     */
    nsGraphics::Vec2D getWindowSize() const;

    /**
     * @brief Règle la taille de la fenêtre
     * @param[in] windowSize : Nouvelle taille
     * @fn void setWindowSize(const nsGraphics::Vec2D& windowSize);
     */
    void setWindowSize(const nsGraphics::Vec2D& windowSize);

    /**
     * @brief Récupère la position de la fenêtre
     * @fn nsGraphics::Vec2D getWindowPosition() const;
     */
    nsGraphics::Vec2D getWindowPosition() const;

    /**
     * @brief Règle la position de la fenêtre
     * @param[in] windowPosition : Nouvelle position
     * @fn void setWindowPosition(const nsGraphics::Vec2D &windowPosition);
     */
    void setWindowPosition(const nsGraphics::Vec2D &windowPosition);

    /**
     * @brief Récupère le nom de la fenêtre
     * @fn const std::string& getWindowName() const;
     */
    const std::string& getWindowName() const;

    /**
     * @brief Règle le nom de la fenêtre
     * @param[in] windowName : Nouveau nom
     * @fn void setWindowName(const std::string &windowName);
     */
    void setWindowName(const std::string &windowName);

    /**
     * @brief Retourne si la fenêtre est ouverte
     * @fn bool isOpen() const;
     */
    bool isOpen() const;

private:
    // Les données membres en tant que tel

    /**
     * @brief m_windowName : Nom de la fenêtre
     */
    std::string m_windowName;

    /**
     * @brief m_bgColor : Couleur de fond de la fenêtre
     */
    nsGraphics::RGBAcolor m_bgColor;

    /**
     * @brief m_keyboardMap : Map de l'état des touches du clavier
     */
    KeyMap_t m_keyboardMap;

    /**
     * @brief m_glutWindowId : Identifiant de la fenêtre freeglut
     */
    short m_glutWindowId = 0;

    /**
     * @brief m_eventManager : Gestionnaire d'évènements
     */
    nsEvent::EventManager m_eventManager;

    /**
     * @brief m_windowIsOpen : Etat de la fenêtre
     */
    bool m_windowIsOpen;

    // Les handlers

    /**
     * @brief Handler lié a <a href="https://www.opengl.org/resources/libraries/glut/spec3/node48.html">glutReshapeFunc</a>
     * @param[in] h : Nouvelle hauteur de la fenêtre
     * @param[in] w : Nouvelle largeur de la fenêtre
     * @fn void callReshape(int h, int w);
     */
    void callReshape(int h, int w);

    /**
     * @brief Handler lié a <a href="https://www.opengl.org/resources/libraries/glut/spec3/node46.html">glutDisplayFunc</a>
     * @fn void callDisplay();
     */
    void callDisplay();

    /**
     * @brief Handler lié a <a href="https://www.opengl.org/resources/libraries/glut/spec3/node50.html">glutMouseFunc</a>
     * @param[in] button : Bouton de la souris qui a généré l'évènement
     * @param[in] state : Nouvel état du bouton
     * @param[in] x : Coordonnée X du curseur
     * @param[in] y : Coordonnée Y du curseur
     * @fn void callMouse(int button, int state, int x = 0, int y = 0);
     */
    void callMouse(int button, int state, int x = 0, int y = 0);

    /**
     * @brief Handler lié a <a href="https://www.opengl.org/resources/libraries/glut/spec3/node51.html">glutMotionFunc</a>
     * @param[in] x : Coordonnée X du curseur
     * @param[in] y : Coordonnée Y du curseur
     * @fn void callMotion(int x, int y);
     */
    void callMotion(int x, int y);

    /**
     * @brief Handler lié a <a href="https://www.opengl.org/resources/libraries/glut/spec3/node51.html">glutPassiveMotionFunc</a>
     * @param[in] x : Coordonnée X du curseur
     * @param[in] y : Coordonnée Y du curseur
     * @fn void callPassiveMotion(int x, int y);
     */
    void callPassiveMotion(int x, int y);

    /**
     * @brief Handler lié a <a href="https://www.opengl.org/resources/libraries/glut/spec3/node49.html">glutKeyboardFunc</a>
     * @param[in] key : Touche qui a été pressée
     * @param[in] x : Coordonnée X du curseur
     * @param[in] y : Coordonnée Y du curseur
     * @fn void callKeyboard(unsigned char key, int x = 0, int y = 0);
     */
    void callKeyboard(unsigned char key, int x = 0, int y = 0);

    /**
     * @brief Handler lié a <a href="http://freeglut.sourceforge.net/docs/api.php#WindowCallback">glutKeyboardUpFunc</a>
     * @param[in] key : Touche qui a été relâchée
     * @param[in] x : Coordonnée X du curseur
     * @param[in] y : Coordonnée Y du curseur
     * @fn void callKeyboardUp(unsigned char key, int x = 0, int y = 0);
     */
    void callKeyboardUp(unsigned char key, int x = 0, int y = 0);

    /**
     * @brief Handler lié a <a href="http://freeglut.sourceforge.net/docs/api.php#WindowCallback">glutSpecialFunc</a>
     * @param[in] key : Touche spéciale qui a été pressée
     * @param[in] x : Coordonnée X du curseur
     * @param[in] y : Coordonnée Y du curseur
     * @fn void callKeyboardSpecial(int key, int x = 0, int y = 0);
     */
    void callKeyboardSpecial(int key, int x = 0, int y = 0);

    /**
     * @brief Handler lié a <a href="http://freeglut.sourceforge.net/docs/api.php#WindowCallback">glutSpecialUpFunc</a>
     * @param[in] key : Touche spéciale qui a été relâchée
     * @param[in] x : Coordonnée X du curseur
     * @param[in] y : Coordonnée Y du curseur
     * @fn void callKeyboardUpSpecial(int key, int x = 0, int y = 0);
     */
    void callKeyboardUpSpecial(int key, int x = 0, int y = 0);

    /**
     * @brief Handler lié a <a href="http://freeglut.sourceforge.net/docs/api.php#WindowCallback">glutCloseFunc</a>
     * @fn void callClose();
     */
    void callClose();

}; // class MinGL

#endif // MINGL_H
