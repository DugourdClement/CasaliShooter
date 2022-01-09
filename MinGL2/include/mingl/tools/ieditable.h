/**
 *
 * @file    ieditable.h
 *
 * @authors D. Mathieu, M. Laporte
 *
 * @date    16/03/2009
 *
 * @version V2.0
 *
 * @brief   declaration de la classe CEditable dans nsUtil
 *
 * @version V2.1
 *
 * @author Alexandre Sollier
 *
 * @brief Ajout de la documentation
 *
 **/

#ifndef IEDITABLE_H
#define IEDITABLE_H

#include <iostream>

/**
 * @namespace nsUtil
 * @brief Espace de nom pour les utilitaires lambda
 */
namespace nsUtil
{

/**
 * @class IEditable
 * @brief Interface pour un objet injectable
 */
class IEditable
{

public:
    /**
     * @brief Destructeur pour la classe IEditable
     * @fn virtual ~IEditable() = default;
     */
    virtual ~IEditable() = default;

    /**
     * @brief Surcharge de l'opérateur d'injection
     * @param[in] os : Flux dans lequel injecter
     * @param[in] Obj : Objet a injecter
     * @fn friend std::ostream& operator<<(std::ostream& os, const IEditable& Obj);
     */
    friend std::ostream& operator<<(std::ostream& os, const IEditable& Obj);

protected:
    /**
     * @brief Fonction appelée pour injecter l'objet courant dans un flux
     * @param[in] os : Flux dans lequel injecter
     * @fn virtual std::ostream& _Edit(std::ostream& os) const = 0;
     */
    virtual std::ostream& _Edit(std::ostream& os) const = 0;

}; // class IEditable

std::ostream& operator<<(std::ostream & os, const IEditable & Obj);

} // namespace nsUtil

#include "ieditable.hpp"

#endif // IEDITABLE_H

