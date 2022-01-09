/**
 *
 * @file    idrawable.h
 * @author  Alexandre Sollier
 * @date    Janvier 2020
 * @version 1.0
 * @brief   Interface pour un objet affichable
 *
 **/

#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <memory>

class MinGL;

/**
 * @namespace nsGraphics
 * @brief Espace de nom pour les utilitaires graphiques
 */
namespace nsGraphics
{

/**
 * @class IDrawable
 * @brief Interface pour un objet affichable
 */
class IDrawable
{

public:
    /**
     * @brief Destructeur pour la classe IDrawable
     * @fn virtual ~IDrawable() = default;
     */
    virtual ~IDrawable() = default;

    /**
     * @brief Fonction pour afficher l'objet.
     * @fn virtual void draw(MinGL& window) const = 0;
     */
    virtual void draw(MinGL& window) const = 0;

    /**
     * @brief Surcharge de l'opérateur d'injection
     * @param[in] window : Fenêtre dans laquelle injecter l'élément
     * @param[in] drawable : Elément a injecter
     * @fn friend MinGL& operator<<(MinGL& window, const IminGLInjectable& drawable)
     */
    friend MinGL& operator<<(MinGL& window, const IDrawable& drawable)
    {
        drawable.draw(window);

        return window;
    }

}; // class IDrawable

} // namespace nsGraphics

#endif // DRAWABLE_H
