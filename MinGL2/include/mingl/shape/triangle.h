/**
 *
 * @file    triangle.h
 * @author  Alexandre Sollier
 * @date    Janvier 2020
 * @version 1.0
 * @brief   Représente un triangle
 *
 **/

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"

#include "../transition/itransitionable.h"

namespace nsShape
{

/**
 * @class Triangle
 * @brief Classe représentant un triangle
 */
class Triangle : public Shape, public nsTransition::ITransitionable
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
        TRANSITION_THIRD_POSITION, /**< Transition pour la position du troisième sommet */
    };

    /**
     * @brief Constructeur pour la classe Triangle
     * @param[in] firstPosition : Position du premier sommet
     * @param[in] secondPosition : Position du second sommet
     * @param[in] thirdPosition : Position du troisième sommet
     * @param[in] fillColor : Couleur de remplissage
     * @param[in] borderColor : Couleur de bord
     * @fn Triangle(const nsGraphics::Vec2D& firstPosition, const nsGraphics::Vec2D& secondPosition, const nsGraphics::Vec2D& thirdPosition,
             const nsGraphics::RGBAcolor& fillColor, const nsGraphics::RGBAcolor& borderColor = nsGraphics::KTransparent);
     */
    Triangle(const nsGraphics::Vec2D& firstPosition, const nsGraphics::Vec2D& secondPosition, const nsGraphics::Vec2D& thirdPosition,
             const nsGraphics::RGBAcolor& fillColor, const nsGraphics::RGBAcolor& borderColor = nsGraphics::KTransparent);

    /**
     * @brief Destructeur virtuel pour la classe Triangle
     * @fn virtual ~Triangle() override = default;
     */
    virtual ~Triangle() override = default;

    virtual void draw(MinGL& window) const override;

    virtual void getValues(const int &id, std::vector<float> &values) override;
    virtual void setValues(const int &id, const std::vector<float> &values) override;

    /**
     * @brief Opérateur de décalage
     * @param[in] position : Position a additionner
     * @fn Triangle operator+(const nsGraphics::Vec2D& position) const
     */
    Triangle operator+(const nsGraphics::Vec2D& position) const;

    /**
     * @brief Opérateur de réduction
     * @param[in] f : Nombre avec lequel multiplier la position actuelle
     * @fn Triangle operator*(const float& f) const
     */
    Triangle operator*(const float& f) const;

    /**
     * @brief Récupère la position du premier sommet du triangle
     * @fn const nsGraphics::Vec2D& getFirstPosition() const;
     */
    const nsGraphics::Vec2D& getFirstPosition() const;

    /**
     * @brief Définit la nouvelle position du premier sommet du triangle
     * @param[in] firstPosition : Nouvelle position du premier sommet
     * @fn void setFirstPosition(const nsGraphics::Vec2D &firstPosition);
     */
    void setFirstPosition(const nsGraphics::Vec2D &firstPosition);

    /**
     * @brief Récupère la position du second sommet du triangle
     * @fn const nsGraphics::Vec2D& getSecondPosition() const;
     */
    const nsGraphics::Vec2D& getSecondPosition() const;

    /**
     * @brief Définit la nouvelle position du second sommet du triangle
     * @param[in] secondPosition : Nouvelle position du second sommet
     * @fn void setSecondPosition(const nsGraphics::Vec2D &secondPosition);
     */
    void setSecondPosition(const nsGraphics::Vec2D &secondPosition);

    /**
     * @brief Récupère la position du troisième sommet du triangle
     * @fn const nsGraphics::Vec2D& getThirdPosition() const;
     */
    const nsGraphics::Vec2D& getThirdPosition() const;

    /**
     * @brief Définit la nouvelle position du troisième sommet du triangle
     * @param[in] thirdPosition : Nouvelle position du troisième sommet
     * @fn void setThirdPosition(const nsGraphics::Vec2D &thirdPosition);
     */
    void setThirdPosition(const nsGraphics::Vec2D &thirdPosition);

private:
    /**
     * @brief m_firstPosition : Position du premier sommet
     */
    nsGraphics::Vec2D m_firstPosition;

    /**
     * @brief m_secondPosition : Position du second sommet
     */
    nsGraphics::Vec2D m_secondPosition;

    /**
     * @brief m_thirdPosition : Position du troisième sommet
     */
    nsGraphics::Vec2D m_thirdPosition;

}; // class Triangle

} // namespace nsShape

#endif // TRIANGLE_H
