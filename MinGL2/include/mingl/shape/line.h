/**
 *
 * @file    line.h
 * @author  Alexandre Sollier
 * @date    Janvier 2020
 * @version 1.0
 * @brief   Représente une ligne
 *
 **/

#ifndef LINE_H
#define LINE_H

#include "shape.h"

#include "../transition/itransitionable.h"

namespace nsShape
{

/**
 * @class Line
 * @brief Classe représentant une ligne
 */
class Line : public Shape, public nsTransition::ITransitionable
{

public:
    /**
     * @brief TransitionIds : Liste de toutes les transitions que cet élément peut exécuter
     */
    enum TransitionIds {
        TRANSITION_FILL_COLOR_RGB, /**< Transition pour la couleur de remplissage */
        TRANSITION_FILL_COLOR_ALPHA, /**< Transition pour la transparence de remplissage */
        TRANSITION_BORDER_COLOR_RGB, /**< Transition pour la couleur de bord */
        TRANSITION_BORDER_COLOR_ALPHA, /**< Transition pour la transparence de bord */
        TRANSITION_FIRST_POSITION, /**< Transition pour la position du premier sommet */
        TRANSITION_SECOND_POSITION, /**< Transition pour la position du second sommet */
        TRANSITION_LINE_WIDTH, /**< Transition pour l'épaisseur de la ligne */
    };

    /**
     * @brief Constructeur pour la classe Line
     * @param[in] firstPosition : Position du premier sommet
     * @param[in] secondPosition : Position du second sommet
     * @param[in] fillColor : Couleur de remplissage
     * @param[in] lineWidth : Epaisseur de la ligne
     * @fn Line(const nsGraphics::Vec2D& firstPosition, const nsGraphics::Vec2D& secondPosition, const nsGraphics::RGBAcolor& fillColor, const float& lineWidth = 1.f);
     */
    Line(const nsGraphics::Vec2D& firstPosition, const nsGraphics::Vec2D& secondPosition, const nsGraphics::RGBAcolor& fillColor, const float& lineWidth = 1.f);

    /**
     * @brief Destructeur virtuel pour la classe Line
     * @fn virtual ~Line() override = default;
     */
    virtual ~Line() override = default;

    virtual void draw(MinGL& window) const override;

    virtual void getValues(const int &id, std::vector<float> &values) override;
    virtual void setValues(const int &id, const std::vector<float> &values) override;

    /**
     * @brief Opérateur de décalage
     * @param[in] position : Position a additionner
     * @fn Line operator+(const nsGraphics::Vec2D& position) const
     */
    Line operator+(const nsGraphics::Vec2D& position) const;

    /**
     * @brief Opérateur de réduction
     * @param[in] f : Nombre avec lequel multiplier la position actuelle
     * @fn Line operator*(const float& f) const
     */
    Line operator*(const float& f) const;

    /**
     * @brief Récupère la position du premier sommet de la ligne
     * @fn const nsGraphics::Vec2D& getFirstPosition() const;
     */
    const nsGraphics::Vec2D& getFirstPosition() const;

    /**
     * @brief Définit la nouvelle position du premier sommet de la ligne
     * @param[in] firstPosition : Nouvelle position du premier sommet
     * @fn void setFirstPosition(const nsGraphics::Vec2D &firstPosition);
     */
    void setFirstPosition(const nsGraphics::Vec2D &firstPosition);

    /**
     * @brief Récupère la position du second sommet de la ligne
     * @fn const nsGraphics::Vec2D& getSecondPosition() const;
     */
    const nsGraphics::Vec2D& getSecondPosition() const;

    /**
     * @brief Définit la nouvelle position du second sommet de la ligne
     * @param[in] secondPosition : Nouvelle position du second sommet
     * @fn void setSecondPosition(const nsGraphics::Vec2D &secondPosition);
     */
    void setSecondPosition(const nsGraphics::Vec2D &secondPosition);

    /**
     * @brief Récupère l'épaisseur de la ligne
     * @fn float getLineWidth() const;
     */
    float getLineWidth() const;

    /**
     * @brief Définit la nouvelle épaisseur de la ligne
     * @param[in] lineWidth : Nouvelle épaisseur
     * @fn void setLineWidth(float lineWidth);
     */
    void setLineWidth(float lineWidth);

private:
    /**
     * @brief m_firstPosition : Position du premier sommet
     */
    nsGraphics::Vec2D m_firstPosition;

    /**
     * @brief m_position : Position du second sommet
     */
    nsGraphics::Vec2D m_secondPosition;

    /**
     * @brief m_position : Epaisseur de la ligne
     */
    float m_lineWidth;

}; // class Line

} // namespace nsShape

#endif // LINE_H
