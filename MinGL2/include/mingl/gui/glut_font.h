/**
 * @file glut_font.h
 * @brief Classe utilitaire pour utiliser facilement les polices de Glut
 * @author Alexandre Sollier
 * @version 1.1
 * @date 28 décembre 2019
 */

#ifndef GLUT_FONTS_H
#define GLUT_FONTS_H

namespace nsGui
{

/**
 * @class GlutFont
 * @brief Classe listant toute les polices rendues disponibles par Glut, a utiliser avec Text
 */
class GlutFont
{

public:
    /**
     * @brief GlutFonts : Liste de toutes les polices Glut
     */
    enum GlutFonts
    {
        BITMAP_8_BY_13, /**< Police 8x13 Bitmap */
        BITMAP_9_BY_15, /**< Police 9x15 Bitmap */
        BITMAP_TIMES_ROMAN_10, /**< Police 10px Times New Roman */
        BITMAP_TIMES_ROMAN_24, /**< Police 24px Times New Roman */
        BITMAP_HELVETICA_10, /**< Police 10px Helvetica */
        BITMAP_HELVETICA_12, /**< Police 12px Helvetica */
        BITMAP_HELVETICA_18, /**< Police 18px Helvetica */
    };

    /**
     * @brief Constructeur pour la classe GlutFont
     * @param[in] font_ : Police représentée par cette instance
     * @fn GlutFont(const GlutFonts& font);
     */
    GlutFont(const GlutFonts& font);

    /**
     * @brief Récupère l'identificateur de police utilisable par Glut
     * @return Un identificateur de police Glut
     * @fn void* convertForGlut() const;
     */
    void* convertForGlut() const;

private:
    /**
     * @brief m_font : Police représentée par cette instance
     */
    GlutFonts m_font;

}; // class GlutFont

} // namespace nsGui

#endif // GLUT_FONTS_H
