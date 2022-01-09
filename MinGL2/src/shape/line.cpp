/**
 *
 * @file    line.cpp
 * @author  Alexandre Sollier
 * @date    Janvier 2020
 * @version 1.0
 * @brief   Représente une ligne
 *
 **/

#include <cmath>

#include "mingl/shape/line.h"
#include "mingl/macros.h"

nsShape::Line::Line(const nsGraphics::Vec2D & pos1_, const nsGraphics::Vec2D & pos2_, const nsGraphics::RGBAcolor &fillCol_, const float &lineWidth_)
    : Shape(fillCol_, fillCol_)
    , m_firstPosition(pos1_)
    , m_secondPosition(pos2_)
    , m_lineWidth(lineWidth_)
{} // Line()

void nsShape::Line::draw(MinGL& window) const
{
    UNUSED(window);

    // On met la couleur de la ligne
    const nsGraphics::RGBAcolor inColor = getFillColor();
    glColor4ub(inColor.getRed(), inColor.getGreen(), inColor.getBlue(), inColor.getAlpha());

    // On règle l'épaisseur de la ligne
    glLineWidth(m_lineWidth);

    // On dessine la ligne
    glBegin(GL_LINES);
    glVertex2i(m_firstPosition.getX(), m_firstPosition.getY());
    glVertex2i(m_secondPosition.getX(), m_secondPosition.getY());
    glEnd();
} // draw()

void nsShape::Line::getValues(const int &id, std::vector<float> &values)
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

        case TRANSITION_LINE_WIDTH:
            values[0] = m_lineWidth;

            break;
    }
} // getValues()

void nsShape::Line::setValues(const int &id, const std::vector<float> &values)
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

        case TRANSITION_LINE_WIDTH:
            m_lineWidth = values[0];

            break;
    }
} // setValues()

nsShape::Line nsShape::Line::operator+(const nsGraphics::Vec2D& position) const
{
    return Line(m_firstPosition + position, m_secondPosition + position, getFillColor());
} // operator+()

nsShape::Line nsShape::Line::operator*(const float& f) const
{
    return Line(m_firstPosition * f, m_secondPosition * f, getFillColor());
} // operator*()

float nsShape::Line::getLineWidth() const
{
    return m_lineWidth;
} // getLineWidth()

void nsShape::Line::setLineWidth(float lineWidth)
{
    m_lineWidth = lineWidth;
} // setLineWidth()

const nsGraphics::Vec2D& nsShape::Line::getFirstPosition() const
{
    return m_firstPosition;
} // getFirstPosition()

void nsShape::Line::setFirstPosition(const nsGraphics::Vec2D &firstPosition)
{
    m_firstPosition = firstPosition;
} // setFirstPosition()

const nsGraphics::Vec2D& nsShape::Line::getSecondPosition() const
{
    return m_secondPosition;
} // getSecondPosition()

void nsShape::Line::setSecondPosition(const nsGraphics::Vec2D &secondPosition)
{
    m_secondPosition = secondPosition;
} // setSecondPosition()
