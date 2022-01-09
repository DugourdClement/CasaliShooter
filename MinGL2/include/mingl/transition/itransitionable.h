/**
 *
 * @file    itransitionable.h
 * @author  Alexandre Sollier
 * @date    Janvier 2020
 * @version 1.0
 * @brief   Interface pour objet "transitionable"
 *
 **/

#ifndef ITRANSITIONABLE_H
#define ITRANSITIONABLE_H

#include <vector>

namespace nsTransition
{

/**
 * @class ITransitionable
 * @brief Une classe abstraite pour n'importe quelle élément pouvant effectuer une transition entre deux états
 */
class ITransitionable
{
public:
    /**
     * @brief Destructeur pour la classe ITransitionable
     * @fn virtual ~ITransitionable() {}
     */
    virtual ~ITransitionable() {}

    /**
     * @brief Récupère des valeurs dans un vecteur de float pour l'ID spécifié
     * @param[in] id: ID des valeurs a récupérer
     * @param[in, out] values: Vecteur de valeurs a peupler
     * @fn virtual void getValues(const int& id, std::vector<float>& values);
     */
    virtual void getValues(const int& id, std::vector<float>& values) = 0;

    /**
     * @brief Définit les nouvelles valeurs pour l'ID spécifié
     * @param[in] id: ID des valeurs a définir
     * @param[in] values: Vecteur des nouvelles valeurs a appliquer
     * @fn virtual void setValues(const int& id, const std::vector<float>& values);
     */
    virtual void setValues(const int& id, const std::vector<float>& values) = 0;
}; // class ITransitionable

} // namespace nsTransition

#endif // ITRANSITIONABLE_H
