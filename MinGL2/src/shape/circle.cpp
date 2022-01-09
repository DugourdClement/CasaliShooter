/**
 *
 * @file    circle.cpp
 * @author  Alexandre Sollier
 * @date    Janvier 2020
 * @version 1.0
 * @brief   Représente un cercle
 *
 **/

#include <cmath>

#include "mingl/shape/circle.h"
#include "mingl/macros.h"

nsShape::Circle::Circle(const nsGraphics::Vec2D &position, const unsigned &radius, const nsGraphics::RGBAcolor &fillColor, const nsGraphics::RGBAcolor &borderColor)
    : Shape(fillColor, borderColor)
    , m_position(position)
    , m_radius(radius)
{} // Circle()

void nsShape::Circle::draw(MinGL& window) const
{
    UNUSED(window);

    // Source: https://gist.github.com/linusthe3rd/803118

    int i;
    int triangleAmount = 20; // Nombre de triangles a dessiner

    // On règle la couleur du cercle
    const nsGraphics::RGBAcolor inColor = getFillColor();
    glColor4ub(inColor.getRed(), inColor.getGreen(), inColor.getBlue(), inColor.getAlpha()); // Couleur du cercle

    GLfloat twicePi = 2.0f * M_PI;

    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(m_position.getX(), m_position.getY()); // Centre du cercle

    for(i = 0; i <= triangleAmount;i++) {
        glVertex2f(m_position.getX() + (m_radius * cos(i * twicePi / triangleAmount)),
                   m_position.getY() + (m_radius * sin(i * twicePi / triangleAmount)));
    }

    glEnd();

    if (getBorderColor() != nsGraphics::KTransparent) {
        // On a une bordure, on l'affiche
        const nsGraphics::RGBAcolor borderColor = getBorderColor();
        glColor4ub(borderColor.getRed(), borderColor.getGreen(), borderColor.getBlue(), borderColor.getAlpha());
        glLineWidth(1.f);

        glBegin(GL_LINE_LOOP);

        for(i = 0; i <= triangleAmount;i++) {
            glVertex2f(m_position.getX() + (m_radius * cos(i * twicePi / triangleAmount)),
                       m_position.getY() + (m_radius * sin(i * twicePi / triangleAmount)));
        }

        glEnd();
    }
} // draw()

void nsShape::Circle::getValues(const int &id, std::vector<float> &values)
{
    switch (id) {
        case TRANSITION_FILL_COLOR_RGB:
            values[0] = m_fillColor.getRed();
            values[1] = m_fillColor.getGreen();
            values[2] = m_fillColor.getBlue();

            break;

        case TRANSITION_FILL_COLOR_ALPHA:
            values[0] = m_fillColor.getAlpha();

            break;

        case TRANSITION_BORDER_COLOR_RGB:
            values[0] = m_borderColor.getRed();
            values[1] = m_borderColor.getGreen();
            values[2] = m_borderColor.getBlue();

            break;

        case TRANSITION_BORDER_COLOR_ALPHA:
            values[0] = m_borderColor.getAlpha();

            break;

        case TRANSITION_POSITION:
            values[0] = m_position.getX();
            values[1] = m_position.getY();

            break;

        case TRANSITION_RADIUS:
            values[0] = m_radius;

            break;
    }
} // getValues()

void nsShape::Circle::setValues(const int &id, const std::vector<float> &values)
{
    switch (id) {
        case TRANSITION_FILL_COLOR_RGB:
            m_fillColor.setRed(values[0]);
            m_fillColor.setGreen(values[1]);
            m_fillColor.setBlue(values[2]);

            break;

        case TRANSITION_FILL_COLOR_ALPHA:
            m_fillColor.setAlpha(values[0]);

            break;

        case TRANSITION_BORDER_COLOR_RGB:
            m_borderColor.setRed(values[0]);
            m_borderColor.setGreen(values[1]);
            m_borderColor.setBlue(values[2]);

            break;

        case TRANSITION_BORDER_COLOR_ALPHA:
            m_borderColor.setAlpha(values[0]);

            break;

        case TRANSITION_POSITION:
            m_position.setX(values[0]);
            m_position.setY(values[1]);

            break;

        case TRANSITION_RADIUS:
            m_radius = values[0];

            break;
    }
} // setValues()

nsShape::Circle nsShape::Circle::operator+(const nsGraphics::Vec2D& position) const
{
    return Circle(m_position + position, m_radius, getFillColor(), getBorderColor());
} // operator+()

nsShape::Circle nsShape::Circle::operator*(const float& f) const
{
    return Circle(m_position * f, m_radius, getFillColor(), getBorderColor());
} // operator*()

unsigned nsShape::Circle::getRadius() const
{
    return m_radius;
} // getRadius()

void nsShape::Circle::setRadius(const unsigned &radius)
{
    m_radius = radius;
} // setRadius()

const nsGraphics::Vec2D& nsShape::Circle::getPosition() const
{
    return m_position;
} // getPosition()

void nsShape::Circle::setPosition(const nsGraphics::Vec2D &position)
{
    m_position = position;
} // setPosition()
