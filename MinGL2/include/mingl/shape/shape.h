/**
 *
 * @file    shape.h
 * @author  Alexandre Sollier
 * @date    Janvier 2020
 * @version 1.0
 * @brief   Représente une forme
 *
 **/

#ifndef FIG2_H
#define FIG2_H

#include "../graphics/idrawable.h"
#include "../graphics/rgbacolor.h"
#include "../graphics/vec2d.h"

/**
 * @namespace nsShape
 * @brief Espace de nom pour différentes formes
 */
namespace nsShape
{

/**
 * @class Shape
 * @brief Classe de base pour une forme
 */
class Shape: public nsGraphics::IDrawable
{

public:
    /**
     * @brief Constructeur pour la classe Shape
     * @param[in] fillColor : Couleur de remplissage de la forme
     * @param[in] borderColor : Couleur de bord de la forme
     * @fn Shape(const nsGraphics::RGBAcolor& fillColor, const nsGraphics::RGBAcolor& borderColor);
     */
    Shape(const nsGraphics::RGBAcolor& fillColor, const nsGraphics::RGBAcolor& borderColor);

    /**
     * @brief Destructeur virtuel pour la classe Shape
     * @fn virtual ~Shape() = default;
     */
    virtual ~Shape() = default;

    /**
     * @brief Retourne la couleur de remplissage
     * @fn const nsGraphics::RGBAcolor& getFillColor() const;
     */
    const nsGraphics::RGBAcolor& getFillColor() const;

    /**
     * @brief Règle la couleur de remplissage
     * @fn cvoid setFillColor(const nsGraphics::RGBAcolor& fillColor);
     */
    void setFillColor(const nsGraphics::RGBAcolor& fillColor);

    /**
     * @brief Retourne la couleur de bord
     * @fn const nsGraphics::RGBAcolor& getBorderColor() const;
     */
    const nsGraphics::RGBAcolor& getBorderColor() const;

    /**
     * @brief Règle la couleur de bord
     * @fn void setBorderColor(const RGBAcolor& borderColor);
     */
    void setBorderColor(const nsGraphics::RGBAcolor& borderColor);

protected:
    /**
     * @brief m_fillColor : Couleur de remplissage
     */
    nsGraphics::RGBAcolor m_fillColor;

    /**
     * @brief m_borderColor : Couleur de bord
     */
    nsGraphics::RGBAcolor m_borderColor;

}; // class Shape

} // namespace nsShape

#endif // FIG2_H
