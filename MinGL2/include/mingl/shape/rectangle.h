/**
 *
 * @file    rectangle.h
 * @author  Alexandre Sollier
 * @date    Janvier 2020
 * @version 1.0
 * @brief   Représente un rectangle
 *
 **/

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

#include "../transition/itransitionable.h"

namespace nsShape
{

/**
 * @class Rectangle
 * @brief Classe représentant un rectangle
 */
class Rectangle : public Shape, public nsTransition::ITransitionable
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
        TRANSITION_FIRST_POSITION, /**< Transition pour la position du coin haut-gauche */
        TRANSITION_SECOND_POSITION, /**< Transition pour la position du coin bas-droit */
    };

    /**
     * @brief Constructeur pour la classe Rectangle
     * @param[in] firstPosition : Position du coin haut-gauche
     * @param[in] secondPosition : Position du coin bas-droit
     * @param[in] fillColor : Couleur de remplissage
     * @param[in] borderColor : Couleur de bord
     * @fn Rectangle(const nsGraphics::Vec2D& firstPosition, const nsGraphics::Vec2D& secondPosition, const nsGraphics::RGBAcolor& fillColor,
              const nsGraphics::RGBAcolor& borderColor = nsGraphics::KTransparent);
     */
    Rectangle(const nsGraphics::Vec2D& firstPosition, const nsGraphics::Vec2D& secondPosition, const nsGraphics::RGBAcolor& fillColor,
              const nsGraphics::RGBAcolor& borderColor = nsGraphics::KTransparent);

    /**
     * @brief Constructeur pour la classe Rectangle
     * @param[in] position : Position du coin haut-gauche
     * @param[in] width : Largeur du rectangle
     * @param[in] height : Hauteur du rectangle
     * @param[in] fillColor : Couleur de remplissage
     * @param[in] borderColor : Couleur de bord
     * @fn Rectangle(const nsGraphics::Vec2D& position, const unsigned& width, const unsigned& height, const nsGraphics::RGBAcolor& fillColor,
              const nsGraphics::RGBAcolor& borderColor = nsGraphics::KTransparent);
     */
    Rectangle(const nsGraphics::Vec2D& position, const unsigned& width, const unsigned& height, const nsGraphics::RGBAcolor& fillColor,
              const nsGraphics::RGBAcolor& borderColor = nsGraphics::KTransparent);

    /**
     * @brief Destructeur virtuel pour la classe Line
     * @fn virtual ~Line() override = default;
     */
    virtual ~Rectangle() override = default;

    virtual void draw(MinGL& window) const override;

    virtual void getValues(const int &id, std::vector<float> &values) override;
    virtual void setValues(const int &id, const std::vector<float> &values) override;

    /**
     * @brief Opérateur de décalage
     * @param[in] position : Position a additionner
     * @fn Rectangle operator+(const nsGraphics::Vec2D& position) const
     */
    Rectangle operator+(const nsGraphics::Vec2D& position) const;

    /**
     * @brief Opérateur de réduction
     * @param[in] f : Nombre avec lequel multiplier la position actuelle
     * @fn Rectangle operator*(const float& f) const
     */
    Rectangle operator*(const float& f) const;

    /**
     * @brief Récupère la position du coin haut-gauche du rectangle
     * @fn const nsGraphics::Vec2D& getFirstPosition() const;
     */
    const nsGraphics::Vec2D& getFirstPosition() const;

    /**
     * @brief Définit la nouvelle position du coin haut-gauche du rectangle
     * @param[in] firstPosition : Nouvelle position du coin haut-gauche
     * @fn void setFirstPosition(const nsGraphics::Vec2D &firstPosition);
     */
    void setFirstPosition(const nsGraphics::Vec2D &firstPosition);

    /**
     * @brief Récupère la position du coin bas-droit du rectangle
     * @fn const nsGraphics::Vec2D& getSecondPosition() const;
     */
    const nsGraphics::Vec2D& getSecondPosition() const;

    /**
     * @brief Définit la nouvelle position du coin bas-droit du rectangle
     * @param[in] secondPosition : Nouvelle position du coin bas-droit
     * @fn void setSecondPosition(const nsGraphics::Vec2D &secondPosition);
     */
    void setSecondPosition(const nsGraphics::Vec2D &secondPosition);

private:
    /**
     * @brief m_firstPosition : Position du premier sommet
     */
    nsGraphics::Vec2D m_firstPosition;

    /**
     * @brief m_secondPosition : Position du second sommet
     */
    nsGraphics::Vec2D m_secondPosition;

}; // class Rectangle

} // namespace nsShape

#endif // RECTANGLE_H
