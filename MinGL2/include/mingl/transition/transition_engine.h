/**
 *
 * @file    transition_engine.h
 * @author  Alexandre Sollier
 * @date    Janvier 2020
 * @version 1.0
 * @brief   Gestionnaire de transition de minGL
 *
 **/

#ifndef TRANSITION_ENGINE_H
#define TRANSITION_ENGINE_H

#include <chrono>
#include <memory>
#include <list>

#include "transition.h"

namespace nsTransition
{

/**
 * @class TransitionEngine
 * @brief Une classe implémentant un moteur de transition supportant plusieurs transitions a la fois
 */
class TransitionEngine
{
public:
    /**
     * @brief Met a jour toutes les transitions dans la liste
     * @param[in] delta : Temps que la dernière image a mis pour faire son rendu
     * @fn void update(const std::chrono::microseconds &delta);
     *
     * Cette fonction rajoute la valeur de delta aux temps écoulés des différentes transitions,
     * et supprime les transitions terminées de la liste.
     */
    void update(const std::chrono::microseconds& delta);

    /**
     * @brief Démarre un contrat
     * @param[in] contract : Contrat de transition a démarrer
     * @fn void startContract(const TransitionContract &contract);
     */
    void startContract(const TransitionContract& contract);

    /**
     * @brief Termine toutes les transitions de la liste
     * @param[in] finishMode : finishMode : Mode utilisé pour finir cette Transition (Valeurs d'arrivé par défaut)
     * @fn void finishEveryTransition();
     */
    void finishEveryTransition(const Transition::TransitionFinishModes& finishMode = Transition::FINISH_DESTINATION);

    /**
     * @brief Termine toutes les transitions d'une certaine cible de la liste
     * @param[in] transitionable : La cible où arrêter les transitions
     * @param[in] finishMode : finishMode : Mode utilisé pour finir cette Transition (Valeurs d'arrivé par défaut)
     * @fn void finishEveryTransitionOfTarget(const ITransitionable &transitionable);
     */
    void finishEveryTransitionOfTarget(const ITransitionable& transitionable, const Transition::TransitionFinishModes& finishMode = Transition::FINISH_DESTINATION);

private:
    /**
     * @brief TransitionVector_t : Définition de type représentant une liste de transition
     */
    typedef std::list<Transition> TransitionVector_t;

    /**
     * @brief m_transitionList : Liste des transitions que ce moteur gère
     */
    TransitionVector_t m_transitionList;
}; // class TransitionEngine

} // namespace nsTransition

#endif // TRANSITION_ENGINE_H
