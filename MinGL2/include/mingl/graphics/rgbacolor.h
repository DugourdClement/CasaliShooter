/**
 *
 * @file    rgbacolor.h
 * @author  Alexandre Sollier
 * @date    Janvier 2020
 * @version 1.1
 * @brief   Représente une couleur RGBA
 *
 **/

#ifndef RGBACOLOR_H
#define RGBACOLOR_H

#include <GL/freeglut.h> // GLubyte

#include "../tools/ieditable.h"

namespace nsGraphics
{

/**
 * @class RGBAcolor
 * @brief Classe représentant un couleur RGBA8888
 */
class RGBAcolor : public nsUtil::IEditable
{

public:
    /**
     * @brief Constructeur pour la classe RGBAcolor
     * @param[in] red : Taux de rouge (0-255)
     * @param[in] green : Taux de vert (0-255)
     * @param[in] blue : Taux de bleu (0-255)
     * @param[in] alpha : Taux de transparence (0-255)
     * @fn RGBAcolor(const GLubyte& red = 0, const GLubyte& green = 0, const GLubyte& blue = 0, const GLubyte& alpha = 255);
     */
    RGBAcolor(const GLubyte& red = 0, const GLubyte& green = 0, const GLubyte& blue = 0, const GLubyte& alpha = 255);

    /**
     * @brief Destructeur virtuel pour la classe RGBAcolor
     * @fn virtual ~RGBAcolor() override = default;
     */
    virtual ~RGBAcolor() override = default;

    /**
     * @brief Opérateur d'égalité
     * @param[in] col : Couleur a vérifier
     * @fn bool operator==(const RGBAcolor& col) const;
     */
    bool operator==(const RGBAcolor& col) const;

    /**
     * @brief Opérateur d'inégalité
     * @param[in] col : Couleur a vérifier
     * @fn bool operator!=(const RGBAcolor& col) const;
     */
    bool operator!=(const RGBAcolor& col) const;

    /**
     * @brief Opérateur de décalage
     * @param[in] rhs : Couleur a additionner
     * @fn RGBAcolor operator+(const RGBAcolor& rhs) const;
     */
    RGBAcolor operator+(const RGBAcolor& rhs) const;

    /**
     * @brief Opérateur de réduction
     * @param[in] rhs : Couleur avec laquelle multiplier la couleur actuelle
     * @fn RGBAcolor operator*(const float& rhs) const;
     */
    RGBAcolor operator*(const float& rhs) const;

    /**
     * @brief Récupère le taux de rouge
     * @return Une référence constante vers m_red
     * @fn GLubyte getRed() const;
     */
    GLubyte getRed() const;

    /**
     * @brief Définit le nouveau taux de rouge
     * @param[in] red : Nouveau taux de rouge
     * @fn void setRed(const GLubyte& red);
     */
    void setRed(const GLubyte& red);

    /**
     * @brief Récupère le taux de vert
     * @return Une référence constante vers m_green
     * @fn GLubyte getGreen() const;
     */
    GLubyte getGreen() const;

    /**
     * @brief Définit le nouveau taux de vert
     * @param[in] red : Nouveau taux de vert
     * @fn void setGreen(const GLubyte& green);
     */
    void setGreen(const GLubyte& green);

    /**
     * @brief Récupère le taux de bleu
     * @return Une référence constante vers m_blue
     * @fn GLubyte getBlue() const;
     */
    GLubyte getBlue() const;

    /**
     * @brief Définit le nouveau taux de bleu
     * @param[in] red : Nouveau taux de bleu
     * @fn void setBlue(const GLubyte& blue);
     */
    void setBlue(const GLubyte& blue);

    /**
     * @brief Récupère le taux de transparence
     * @return Une référence constante vers m_alpha
     * @fn GLubyte getAlpha() const;
     */
    GLubyte getAlpha() const;

    /**
     * @brief Définit le nouveau taux de transparence
     * @param[in] red : Nouveau taux de transparence
     * @fn void setAlpha(const GLubyte& alpha);
     */
    void setAlpha(const GLubyte& alpha);

protected:
    virtual std::ostream& _Edit(std::ostream& os = std::cout) const override;

private:
    /**
     * @brief m_red : Taux de rouge
     */
    GLubyte m_red;

    /**
     * @brief m_green : Taux de vert
     */
    GLubyte m_green;

    /**
     * @brief m_blue : Taux de bleu
     */
    GLubyte m_blue;

    /**
     * @brief m_alpha : Taux de transparence
     */
    GLubyte m_alpha;

}; // class RGBAcolor

// Quelques couleurs trouvées sur:
// https://www.rapidtables.com/web/color/RGB_Color.html
const RGBAcolor KBlack       {  0,   0,   0};
const RGBAcolor KWhite       {255, 255, 255};
const RGBAcolor KRed         {255,   0,   0};
const RGBAcolor KLime        {  0, 255,   0};
const RGBAcolor KBlue        {  0,   0, 255};
const RGBAcolor KYellow      {255, 255,   0};
const RGBAcolor KCyan        {  0, 255, 255};
const RGBAcolor KMagenta     {255,   0, 255};
const RGBAcolor KSilver      {192, 192, 192};
const RGBAcolor KGray        {128, 128, 128};
const RGBAcolor KMaroon      {128,   0,   0};
const RGBAcolor KOlive       {128, 128,   0};
const RGBAcolor KGreen       {  0, 128,   0};
const RGBAcolor KPurple      {128,   0, 128};
const RGBAcolor KTeal        {  0, 128, 128};
const RGBAcolor KNavy        {  0,   0, 128};
const RGBAcolor KTransparent {  0,   0,   0,  0};

} // namespace nsGraphics

#endif // RGBACOLOR_H
