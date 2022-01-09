/**
 *
 * @file    sprite.h
 * @author  Alexandre Sollier
 * @date    Janvier 2020
 * @version 1.0
 * @brief   Image pouvant être chargé depuis un fichier
 *
 **/

#ifndef DISPLAY_SPRITE_H
#define DISPLAY_SPRITE_H

#include <cstdint>
#include <vector>

#include "../graphics/idrawable.h"
#include "../graphics/rgbacolor.h"
#include "../graphics/vec2d.h"
#include "../transition/itransitionable.h"

namespace nsGui {

/**
 * @class Sprite
 * @brief Permet de charger une image depuis un format créé pour l'occasion, le .si2
 */
class Sprite : public nsGraphics::IDrawable, public nsTransition::ITransitionable
{
public:
    /**
     * @brief TransitionIds : Liste de toutes les transitions que cet élément peut exécuter
     */
    enum TransitionIds {
        TRANSITION_POSITION, /**< Transition pour la position */
    };

    /**
     * @brief Constructeur pour la classe Sprite, charge les données depuis un fichier
     * @param[in] filename : Chemin d'accès vers le fichier image
     * @param[in] position : Position du sprite
     * @fn Sprite(const std::string& filename, const nsGraphics::Vec2D& position = nsGraphics::Vec2D());
     */
    Sprite(const std::string& filename, const nsGraphics::Vec2D& position = nsGraphics::Vec2D());

    /**
     * @brief Constructeur pour la classe Sprite, copie les données depuis un vecteur de pixels
     * @param[in] pixelData : Vecteur contenant des données sur les pixels
     * @param[in] rowSize : Nombre de pixels par ligne
     * @param[in] position : Position du sprite
     * @fn Sprite(const std::vector<nsGraphics::RGBAcolor>& pixelData, const uint32_t& rowSize, const nsGraphics::Vec2D& position = nsGraphics::Vec2D());
     */
    Sprite(const std::vector<nsGraphics::RGBAcolor>& pixelData, const uint32_t& rowSize, const nsGraphics::Vec2D& position = nsGraphics::Vec2D());

    virtual void draw(MinGL& window) const override;

    virtual void getValues(const int &id, std::vector<float> &values) override;
    virtual void setValues(const int &id, const std::vector<float> &values) override;

    /**
     * @brief Récupère le nombre de pixels par ligne
     * @return Une référence constante vers m_rowSize
     * @fn const uint32_t& getRowSize() const;
     */
    const uint32_t& getRowSize() const;

    /**
     * @brief Récupère le vecteur contenant les pixels de l'image
     * @return Une référence constante vers m_pixelData
     * @fn const std::vector<nsGraphics::RGBAcolor>& getPixelData() const;
     */
    const std::vector<nsGraphics::RGBAcolor>& getPixelData() const;

    /**
     * @brief Récupère la position du sprite
     * @return Une référence const vers m_position
     * @fn const nsGraphics::Vec2D& getPosition() const;
     */
    const nsGraphics::Vec2D& getPosition() const;

    /**
     * @brief Définit la nouvelle position du sprite
     * @param[in] position : Nouvelle position
     * @fn void setPosition(const nsGraphics::Vec2D &position);
     */
    void setPosition(const nsGraphics::Vec2D& position);

    /**
     * @brief Calcule la taille du sprite
     * @return La taille calculée
     * @fn Vec2D computeSize() const;
     */
    nsGraphics::Vec2D computeSize() const;

private:
    /**
     * @struct FileBegin
     * @brief Décrit le début d'un fichier .si2
     */
    struct FileBegin {
        uint16_t magic; /**< Le magic number du fichier, doit toujours être "SI" */
        uint32_t headmagic; /**< Le magic number de la section en-tête, doit toujours être "HEAD" */
        uint16_t fileVersion; /**< La version du format stockée par le fichier */
        uint32_t pixelCount; /**< Le nombre de pixels contenus dans la section données */
        uint32_t rowSize; /**< Le nombre de pixels par ligne */
        uint32_t datamagic; /**< Le magic number de la section données, doit toujours être "DATA" */
    } __attribute__((packed));

    /**
     * @brief m_position : Position de ce Sprite
     */
    nsGraphics::Vec2D m_position;

    /**
     * @brief m_rowSize : Nombre de pixel par ligne
     */
    uint32_t m_rowSize;

    /**
     * @brief m_pixelData : Vecteur contenant tout les pixels composant l'image
     */
    std::vector<nsGraphics::RGBAcolor> m_pixelData;
}; // class Sprite

} // namespace nsGui

#endif // DISPLAY_SPRITE_H
