/**
 *
 * @file    mingl.cpp
 * @author  Alexandre Sollier, Clément Mathieu--Drif, Alain Casali
 * @date    Janvier 2020
 * @version 2.0
 * @brief   La bête
 *
 **/

#include <map>

#include "mingl/mingl.h"

// Astuce pour faire passer les handlers en fonction static dans initGraphic()
namespace {

std::map<int, MinGL *> anyWindow;

template<typename T, T oHandler>
struct callBackBuilder;

template<typename Obj, typename... Arg, void(Obj::* oHandler)(Arg...)>
struct callBackBuilder<void(Obj::*)(Arg...), oHandler>
{
    static void callback(Arg... arg)
    {
        int current_id = glutGetWindow();
        //cout << "window [" << current_id << "] handler call" << endl;
        auto it = anyWindow.find(current_id);
        if (it != anyWindow.end())
        {
            (it->second->*oHandler)(arg...);
        }
    }
};

} // namespace

#define BIND_CALLBACK(HANDLER) callBackBuilder<decltype(HANDLER), HANDLER>::callback

MinGL::MinGL(const std::string& name, const nsGraphics::Vec2D& windowSize, const nsGraphics::Vec2D& windowPosition,
             const nsGraphics::RGBAcolor& backgroundColor)
    : m_windowName(name)
    , m_bgColor(backgroundColor)
    , m_eventManager()
    , m_windowIsOpen(false)
{
    glutInitWindowSize(windowSize.getX(), windowSize.getY());
    glutInitWindowPosition(windowPosition.getX(), windowPosition.getY());
} // MinGL()

MinGL::~MinGL()
{
    auto it = anyWindow.find(m_glutWindowId);
    if (it != anyWindow.end())
        anyWindow.erase(it);

    stopGraphic();
} //~MinGL()

void MinGL::finishFrame()
{
    glutPostRedisplay();
    glutMainLoopEvent();
} // finishFrame()

void MinGL::clearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);
} // clearScreen()

nsEvent::EventManager& MinGL::getEventManager()
{
    return m_eventManager;
} // getEventManager()

const nsGraphics::RGBAcolor& MinGL::getBackgroundColor() const
{
    return m_bgColor;
} // getBackgroundColor()

void MinGL::setBackgroundColor(const nsGraphics::RGBAcolor& backgroundColor)
{
    m_bgColor = backgroundColor;
    glClearColor(m_bgColor.getRed() / 256.f, m_bgColor.getGreen() / 256.f, m_bgColor.getBlue() / 256.f, m_bgColor.getAlpha() / 256.f);
} // setBackgroundColor()

void MinGL::initGraphic()
{
    // Initialisation GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    m_glutWindowId = glutCreateWindow(m_windowName.c_str());
    anyWindow[m_glutWindowId] = this;

    // On active la transparence
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

    // Initialisation handlers
    glutReshapeFunc(BIND_CALLBACK(&MinGL::callReshape));
    glutDisplayFunc(BIND_CALLBACK(&MinGL::callDisplay));
    glutMouseFunc(BIND_CALLBACK(&MinGL::callMouse));
    glutMotionFunc(BIND_CALLBACK(&MinGL::callMotion));
    glutPassiveMotionFunc(BIND_CALLBACK(&MinGL::callPassiveMotion));
    glutKeyboardFunc(BIND_CALLBACK(&MinGL::callKeyboard));
    glutKeyboardUpFunc(BIND_CALLBACK(&MinGL::callKeyboardUp));
    glutSpecialFunc(BIND_CALLBACK(&MinGL::callKeyboardSpecial));
    glutSpecialUpFunc(BIND_CALLBACK(&MinGL::callKeyboardUpSpecial));
    glutCloseFunc(BIND_CALLBACK(&MinGL::callClose));

    // On set la couleur d'effacement (prend des float, donc obligé de diviser par la taille d'un GLuint)
    glClearColor(m_bgColor.getRed() / 256.f, m_bgColor.getGreen() / 256.f, m_bgColor.getBlue() / 256.f, m_bgColor.getAlpha() / 256.f);

    // Efface écran
    clearScreen();

    // Un tour de boucle pour lancer l'affichage
    glutMainLoopEvent();
    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF); // on désactive la répétition des touches
    m_windowIsOpen = true;
} // initGraphic()

void MinGL::stopGraphic()
{
    glutDestroyWindow(m_glutWindowId);
    glutMainLoopEvent();
} // stopGraphic()

bool MinGL::isPressed(const KeyType_t &key)
{
    return m_keyboardMap[key];
} // isPressed()

void MinGL::resetKey(const KeyType_t &key)
{
    m_keyboardMap[key] = false;
} // resetKey()

void MinGL::callReshape(int h, int w)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    nsGraphics::Vec2D windowSize = getWindowSize();
    gluOrtho2D(0.0, GLfloat (windowSize.getX()), GLfloat (windowSize.getY()), 0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, h, w);
} // callReshape()

void MinGL::callDisplay()
{
    glFlush();
    glutSwapBuffers();
} // callDisplay()

void MinGL::callMouse(int button, int state, int x, int y)
{
    nsEvent::Event_t event;
    event.eventType = nsEvent::EventType_t::MouseClick;
    event.eventData.clickData.button = button;
    event.eventData.clickData.state = state;
    event.eventData.clickData.x = x;
    event.eventData.clickData.y = y;

    m_eventManager.pushEvent(event);
} // calMouse()

void MinGL::callMotion(int x, int y)
{
    nsEvent::Event_t event;
    event.eventType = nsEvent::EventType_t::MouseDrag;
    event.eventData.moveData.x = x;
    event.eventData.moveData.y = y;

    m_eventManager.pushEvent(event);
} // callMotion()

void MinGL::callPassiveMotion(int x, int y)
{
    nsEvent::Event_t event;
    event.eventType = nsEvent::EventType_t::MouseMove;
    event.eventData.moveData.x = x;
    event.eventData.moveData.y = y;

    m_eventManager.pushEvent(event);
} // callPassiveMotion()

void MinGL::callKeyboard(unsigned char k, int x, int y)
{
    (void)(x); (void)(y);
    KeyType_t key(k, false);
    m_keyboardMap[key] = true;
} // callKeyboard()

void MinGL::callKeyboardUp(unsigned char k, int x, int y)
{
    (void)(x); (void)(y);
    KeyType_t key(k, false);
    m_keyboardMap[key] = false;
} // callKeyboardUp()

void MinGL::callKeyboardSpecial(int k, int x, int y)
{
    (void)(x); (void)(y);
    KeyType_t key(k, true);
    m_keyboardMap[key] = true;
} // callKeyboardSpecial()

void MinGL::callKeyboardUpSpecial(int k, int x, int y)
{
    (void)(x); (void)(y);
    KeyType_t key(k, true);
    m_keyboardMap[key] = false;
} // callKeyboardUpSpecial()

void MinGL::callClose()
{
    m_windowIsOpen = false;
} // callClose()

nsGraphics::Vec2D MinGL::getWindowSize() const
{
    return nsGraphics::Vec2D(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
} // getWindowSize()

void MinGL::setWindowSize(const nsGraphics::Vec2D &windowSize)
{
    glutReshapeWindow(windowSize.getX(), windowSize.getY());
} // setWindowSize()

nsGraphics::Vec2D MinGL::getWindowPosition() const
{
    return nsGraphics::Vec2D(glutGet(GLUT_WINDOW_X), glutGet(GLUT_WINDOW_Y));
} // getWindowPosition()

void MinGL::setWindowPosition(const nsGraphics::Vec2D &windowPosition)
{
    glutPositionWindow(windowPosition.getX(), windowPosition.getY());
} // setWindowPosition()

const std::string& MinGL::getWindowName() const
{
    return m_windowName;
} // getWindowName()

void MinGL::setWindowName(const std::string &windowName)
{
    m_windowName = windowName;
    glutSetWindowTitle(windowName.c_str());
} // setWindowName()

bool MinGL::isOpen() const
{
    return m_windowIsOpen;
} // isOpen()
