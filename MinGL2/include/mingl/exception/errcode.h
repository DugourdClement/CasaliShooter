/**
 *
 * @file    errcode.h
 *
 * @authors D. Mathieu
 *
 * @date    28/08/2010
 *
 * @version V2.0
 *
 * @brief   Codes d'erreurs
 *
 * @version V2.1
 *
 * @author Alexandre Sollier
 *
 * @brief Ajout de la documentation, renommage du fichier
 *
 **/

#ifndef CSTCODERR_H
#define CSTCODERR_H

#include <map>
#include <string>

namespace nsException
{

enum {
    KNoExc          = 0, /**< Pas d'exception */
    KNoError        = 0, /**< Pas d'exception */

    kColorOutOfBounds = 100, /**< Couleur hors des bornes */

    KFileError      = 252, /**< Erreur lors de l'ouverture du fichier */
    KErrArg         = 253, /**< Erreur d'argument (Nombre ou types) */
    KExcStd         = 254, /**< Erreur standard */
    kExcInconnue    = -1, /**< Erreur inconnue */

    kErrTooHight    = 300, /**< Position trop haute */
    kErrTooRight    = 301, /**< Position trop a droite */
    kErrFontSize    = 302, /**< Erreur sur la taille de la police */
    kNoTriangle     = 303, /**< Pas de triangle */
    kNoLine         = 304, /**< Pas de ligne */
    kNoRectangle    = 305, /**< Pas de rectangle */
    kNoCircle       = 306, /**< Pas de cercle */
    kTypeNotFound   = 307, /**< Type non trouvé */
};

const std::map <unsigned, std::string> kError
{
    {kErrTooHight, "Trop haut"},
    {kErrTooRight, "Trop à droite"},
    {kErrFontSize, "Taille de police incorrecte"},
    {kNoTriangle, "Nombre incorrect de points pour la construction du triangle"},
    {kNoLine, "Nombre incorrect de points pour la construction d'une ligne"},
    {kNoRectangle, "Nombre incorrect de points pour la construction d'un rectangle"},
    {kNoCircle, "Nombre incorrect de points pour la construction d'un cercle"},
    {kTypeNotFound, "Instanciation impossible: Pas le bon type"},
};

} // namespace nsException

#endif // CSTCODERR_H
