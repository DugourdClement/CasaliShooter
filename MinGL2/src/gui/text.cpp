/**
 *
 * @file    text.h
 * @author  Alexandre Sollier
 * @date    Janvier 2020
 * @version 1.0
 * @brief   Du texte
 *
 **/

#include "mingl/gui/text.h"

#include "mingl/macros.h"

nsGui::Text::Text(const nsGraphics::Vec2D &position, const std::string &content,
           const nsGraphics::RGBAcolor &textColor, const GlutFont::GlutFonts &textFont,
           const HorizontalAlignment &horizontalAlignment,
           const VerticalAlignment &verticalAlignment)
    : m_position(position)
    , m_content(content)
    , m_textColor(textColor)
    , m_textFont(textFont)
    , m_horizontalAlignment(horizontalAlignment)
    , m_verticalAlignment(verticalAlignment)
{} // Text()

void nsGui::Text::getValues(const int &id, std::vector<float> &values)
{
    switch (id) {
        case TRANSITION_COLOR_RGB:
            values[0] = m_textColor.getRed();
            values[1] = m_textColor.getGreen();
            values[2] = m_textColor.getBlue();

            break;

        case TRANSITION_COLOR_ALPHA:
            values[0] = m_textColor.getAlpha();

            break;

        case TRANSITION_POSITION:
            values[0] = m_position.getX();
            values[1] = m_position.getY();

            break;
    }
} // getValues()

void nsGui::Text::setValues(const int &id, const std::vector<float> &values)
{
    switch (id) {
        case TRANSITION_COLOR_RGB:
            m_textColor.setRed(values[0]);
            m_textColor.setGreen(values[1]);
            m_textColor.setBlue(values[2]);

            break;

        case TRANSITION_COLOR_ALPHA:
            m_textColor.setAlpha(values[0]);

            break;

        case TRANSITION_POSITION:
            m_position.setX(values[0]);
            m_position.setY(values[1]);

            break;
    }
} // setValues()

int nsGui::Text::computeWidth() const
{
    return glutBitmapLength(m_textFont.convertForGlut(), reinterpret_cast<const unsigned char *>(m_content.c_str()));
} // computeWidth()

int nsGui::Text::computeHeight() const
{
    return glutBitmapHeight(m_textFont.convertForGlut());
} // computeHeight()

nsGraphics::Vec2D nsGui::Text::computeVisiblePosition() const
{
    int posX = m_position.getX();
    switch (m_horizontalAlignment)
    {
        case nsGui::Text::ALIGNH_RIGHT:
            posX -= computeWidth();

            break;
        case nsGui::Text::ALIGNH_CENTER:
            posX -= computeWidth() / 2;

            break;
        default:
            break;
    }

    int posY = m_position.getY();
    switch (m_verticalAlignment)
    {
        case nsGui::Text::ALIGNV_TOP:
            posY += computeHeight();

            break;
        case nsGui::Text::ALIGNV_CENTER:
            posY += computeHeight() / 2;

            break;
        default:
            break;
    }

    return nsGraphics::Vec2D(posX, posY);
} // computeVisiblePosition()

nsGraphics::Vec2D nsGui::Text::computeVisibleEndPosition() const
{
    return computeVisiblePosition() + nsGraphics::Vec2D(computeWidth(), -computeHeight());
} // computeVisibleEndPosition()

const std::string& nsGui::Text::getContent() const
{
    return m_content;
} // getContent()

void nsGui::Text::setContent(const std::string &content)
{
    m_content = content;
} // setContent()

nsGui::Text::VerticalAlignment nsGui::Text::getVerticalAlignment() const
{
    return m_verticalAlignment;
} // getVerticalAlignment()

void nsGui::Text::setVerticalAlignment(const VerticalAlignment &verticalAlignment)
{
    m_verticalAlignment = verticalAlignment;
} // setVerticalAlignment()

nsGui::Text::HorizontalAlignment nsGui::Text::getHorizontalAlignment() const
{
    return m_horizontalAlignment;
} // getHorizontalAlignment()

void nsGui::Text::setHorizontalAlignment(const HorizontalAlignment &horizontalAlignment)
{
    m_horizontalAlignment = horizontalAlignment;
} // setHorizontalAlignment()

const nsGui::GlutFont& nsGui::Text::getTextFont() const
{
    return m_textFont;
} // getTextFont()

void nsGui::Text::setTextFont(const GlutFont &textFont)
{
    m_textFont = textFont;
} // setTextFont()

const nsGraphics::Vec2D& nsGui::Text::getPosition() const
{
    return m_position;
} // getPosition()

void nsGui::Text::setPosition(const nsGraphics::Vec2D &position)
{
    m_position = position;
} // setPosition()

const nsGraphics::RGBAcolor& nsGui::Text::getTextColor() const
{
    return m_textColor;
} // getTextColor()

void nsGui::Text::setTextColor(const nsGraphics::RGBAcolor &textColor)
{
    m_textColor = textColor;
} // setTextColor()

void nsGui::Text::draw(MinGL& window) const
{
    UNUSED(window);
    
    // Draw the text with the right color using Glut
    glColor4ub(m_textColor.getRed(), m_textColor.getGreen(), m_textColor.getBlue(), m_textColor.getAlpha());

    // Set the text position according to its alignment
    const nsGraphics::Vec2D visiblePos = computeVisiblePosition();
    glRasterPos2i(visiblePos.getX(), visiblePos.getY());

    glutBitmapString(m_textFont.convertForGlut(), reinterpret_cast<const unsigned char *>(m_content.c_str()));
} // draw()
