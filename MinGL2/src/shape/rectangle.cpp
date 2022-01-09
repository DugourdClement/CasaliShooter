/**
 *
 * @file    rectangle.cpp
 * @author  Alexandre Sollier
 * @date    Janvier 2020
 * @version 1.0
 * @brief   Représente un rectangle
 *
 **/

#include "mingl/shape/rectangle.h"
#include "mingl/macros.h"

nsShape::Rectangle::Rectangle(const nsGraphics::Vec2D& firstPosition, const nsGraphics::Vec2D& secondPosition, const nsGraphics::RGBAcolor& fillColor, const nsGraphics::RGBAcolor& borderColor)
    : Shape(fillColor, borderColor)
    , m_firstPosition(firstPosition)
    , m_secondPosition(secondPosition)
{} // Rectangle()

nsShape::Rectangle::Rectangle(const nsGraphics::Vec2D& position, const unsigned& width, const unsigned& height, const nsGraphics::RGBAcolor& fillColor, const nsGraphics::RGBAcolor& borderColor)
    : Shape(fillColor, borderColor)
    , m_firstPosition(position)
    , m_secondPosition(nsGraphics::Vec2D(position.getX() + width, position.getY() + height))
{} // Rectangle()

void nsShape::Rectangle::draw(MinGL& window) const
{
    UNUSED(window);

    // On règle la couleur du rectangle
    const nsGraphics::RGBAcolor inColor = getFillColor();
    glColor4ub(inColor.getRed(), inColor.getGreen(), inColor.getBlue(), inColor.getAlpha());

    // Affiche un rectangle via la routine OpenGL
    glRecti(m_firstPosition.getX(), m_firstPosition.getY(), m_secondPosition.getX(), m_secondPosition.getY());

    if (getBorderColor() != nsGraphics::KTransparent) {
        // On a une bordure, on l'affiche
        const nsGraphics::RGBAcolor borderColor = getBorderColor();
        glColor4ub(borderColor.getRed(), borderColor.getGreen(), borderColor.getBlue(), borderColor.getAlpha());
        glLineWidth(1.f);

        glBegin(GL_LINE_LOOP);
        glVertex2i(m_firstPosition.getX(), m_firstPosition.getY());
        glVertex2i(m_firstPosition.getX(), m_secondPosition.getY());
        glVertex2i(m_secondPosition.getX(), m_secondPosition.getY());
        glVertex2i(m_secondPosition.getX(), m_firstPosition.getY());
        glEnd();
    }
} // draw()

void nsShape::Rectangle::getValues(const int &id, std::vector<float> &values)
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

        case TRANSITION_FIRST_POSITION:
            values[0] = m_firstPosition.getX();
            values[1] = m_firstPosition.getY();

            break;

        case TRANSITION_SECOND_POSITION:
            values[0] = m_secondPosition.getX();
            values[1] = m_secondPosition.getY();

            break;
    }
} // getValues()

void nsShape::Rectangle::setValues(const int &id, const std::vector<float> &values)
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

        case TRANSITION_FIRST_POSITION:
            m_firstPosition.setX(values[0]);
            m_firstPosition.setY(values[1]);

            break;

        case TRANSITION_SECOND_POSITION:
            m_secondPosition.setX(values[0]);
            m_secondPosition.setY(values[1]);

            break;
    }
} // setValues()

nsShape::Rectangle nsShape::Rectangle::operator+(const nsGraphics::Vec2D& position) const
{
    return Rectangle(m_firstPosition + position, m_secondPosition + position, getFillColor(), getBorderColor());
} // operator+()

nsShape::Rectangle nsShape::Rectangle::operator*(const float& f) const
{
    return Rectangle(m_firstPosition * f, m_secondPosition * f, getFillColor(), getBorderColor());
} // operator*()

const nsGraphics::Vec2D& nsShape::Rectangle::getFirstPosition() const
{
    return m_firstPosition;
} // getFirstPosition()

void nsShape::Rectangle::setFirstPosition(const nsGraphics::Vec2D &firstPosition)
{
    m_firstPosition = firstPosition;
} // setFirstPosition()

const nsGraphics::Vec2D& nsShape::Rectangle::getSecondPosition() const
{
    return m_secondPosition;
} // getSecondPosition()

void nsShape::Rectangle::setSecondPosition(const nsGraphics::Vec2D &secondPosition)
{
    m_secondPosition = secondPosition;
} // setSecondPosition()
