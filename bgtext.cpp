#include "bgtext.h"

BgText::BgText(const nsGraphics::Vec2D& position, const std::string& content, const nsGraphics::RGBAcolor& textColor, const nsGraphics::RGBAcolor& backgroundColor)
    : m_text(position, content, textColor)
    , m_background(m_text.computeVisiblePosition(), m_text.computeVisibleEndPosition(), backgroundColor)
{} // BgText()

void BgText::draw(MinGL& window) const
{
    // Affiche le fond puis le texte
    window << m_background << m_text;
} // draw()

void BgText::getValues(const int& id, std::vector<float>& values)
{
    // On charge les valeurs dans le vecteur selon l'identifiant donné
    switch (id) {
        case TRANSITION_TEXT_COLOR:
            values[0] = m_text.getTextColor().getRed();
            values[1] = m_text.getTextColor().getGreen();
            values[2] = m_text.getTextColor().getBlue();

            break;

        case TRANSITION_BACKGROUND_COLOR:
            values[0] = m_background.getFillColor().getRed();
            values[1] = m_background.getFillColor().getGreen();
            values[2] = m_background.getFillColor().getBlue();

            break;
    }
} // getValues()

void BgText::setValues(const int& id, const std::vector<float>& values)
{
    // On règle les valeurs depuis le vecteur selon l'identifiant donné
    switch (id) {
        case TRANSITION_TEXT_COLOR:
            m_text.setTextColor(nsGraphics::RGBAcolor(values[0], values[1], values[2]));

            break;

        case TRANSITION_BACKGROUND_COLOR:
            m_background.setFillColor(nsGraphics::RGBAcolor(values[0], values[1], values[2]));

            break;
    }
} // setValues()
