/**
 *
 * @file    transition_contract.h
 * @author  Alexandre Sollier
 * @date    Janvier 2020
 * @version 1.0
 * @brief   Création de la transition
 *
 **/

#ifndef TRANSITION_CONTRACT_H
#define TRANSITION_CONTRACT_H

#include <functional>
#include <vector>

#include "itransitionable.h"
#include "transition_types.h"

namespace nsTransition
{

/**
 * @class TransitionContract
 * @brief Une classe contenant des paramètres pour créer une transition
 */
class TransitionContract
{
public:    
    /**
     * @brief TransitionMode : Liste de tout les modes de transition
     */
    enum TransitionMode {
        MODE_FINITE, /**< Ce mode marque la Transition comme terminée une fois achevée */
        MODE_FINITE_REVERSE, /**< Ce mode va jouer la Transition a l'envers une fois achevée, puis marquer la Transition comme étant terminée */
        MODE_LOOP, /**< Ce mode va définir les valeurs de départ a la cible une fois la Transition achevée, puis se rejouer en boucle */
        MODE_LOOP_SMOOTH, /**< Ce mode va jouer la Transition a l'envers une fois achevée, puis se rejouer en boucle */
    };

    /**
     * @brief Constructeur pour la classe TransitionContract
     * @param[in, out] target : Une référence vers une classe dérivée d'ITransitionable qui sera la cible
     * @param[in] id : L'ID de la transition a appliquer
     * @param[in] duration : La durée de la transition
     * @param[in] destination : Les valeurs d'arrivée
     * @param[in] delay : Délai avant que la transition commence (Zéro par défaut)
     * @param[in] transitionMode : Mode de transition (Transition finie par défaut)
     * @fn TransitionContract(ITransitionable& target, const int& id,
                       const SystemDuration_t& duration, const std::vector<float>& destination,
                       const SystemDuration_t& delay = std::chrono::seconds::zero(),
                       const TransitionMode& transitionMode = TransitionMode::MODE_FINITE);
     */
    TransitionContract(ITransitionable& target, const int& id,
                       const SystemDuration_t& duration, const std::vector<float>& destination,
                       const SystemDuration_t& delay = std::chrono::seconds::zero(),
                       const TransitionMode& transitionMode = TransitionMode::MODE_FINITE);

    /**
     * @brief Retourne l'ID de transition, utilisé par la cible pour connaitre les valeurs a utiliser
     * @return Une référence const vers m_id
     * @fn const int& getId() const;
     */
    const int& getId() const;

    /**
     * @brief Retourne la cible de transition
     * @return Une référence const vers m_target
     * @fn const ITransitionable& getTarget() const;
     */
    const ITransitionable& getTarget() const;

    /**
     * @brief Retourne le mode de transition
     * @return Une référence const vers m_transitionMode
     * @fn const TransitionMode& getTransitionMode() const;
     */
    const TransitionMode& getTransitionMode() const;

    /**
     * @brief Retourne les valeurs de départ
     * @return Une référence const vers m_beginning
     * @fn const std::vector<float>& getBeginning() const;
     */
    const std::vector<float>& getBeginning() const;

    /**
     * @brief Retourne les valeurs d'arrivée
     * @return Une référence const vers m_destination
     * @fn const std::vector<float>& getDestination() const;
     */
    const std::vector<float>& getDestination() const;

    /**
     * @brief Retourne la durée de la transition
     * @return Une référence const vers m_duration
     * @fn const SystemDuration_t& getDuration() const;
     */
    const SystemDuration_t& getDuration() const;

    /**
     * @brief Définit la fonction de callback a appeler quand la transition est achevée
     * @param[in] callback : La fonction a appeler
     * @fn void setDestinationCallback(const std::function<void()>& callback);
     */
    void setDestinationCallback(const std::function<void()>& callback);

protected:
    /**
     * @brief m_id : L'ID de la transition
     *
     * Ceci est seulement utile pour la cible, car lui seul sait a quel ID correspond quelles valeurs.
     * Ainsi, l'ID n'est jamais utilisée directement par la transition et est seulement passée a la cible.
     */
    const int m_id;

    /**
     * @brief m_target : Une référence vers une instance d'une classe dérivée d'ITransitionable
     *
     * C'est la cible de la transition, sur laquelle vont s'appliquer les modifications de valeurs.
     */
    ITransitionable& m_target;

    /**
     * @brief m_transitionMode : Le mode de transition
     *
     * Pour plus d'informations, voyez les valeurs de l'énumération TransitionMode.
     */
    const TransitionMode m_transitionMode;

    /**
     * @brief m_beginning : Contient les valeurs de départ
     */
    std::vector<float> m_beginning;

    /**
     * @brief m_destination : Contient les valeurs d'arrivées
     */
    const std::vector<float> m_destination;

    /**
     * @brief m_duration : La durée de la transition
     */
    SystemDuration_t m_duration;

    /**
     * @brief m_delay : Délai a attendre avant que la transition ne démarre
     */
    SystemDuration_t m_delay;

    /**
     * @brief m_duration : Un pointeur vers la fonction a appeler une fois la transition achevée
     */
    std::function<void()> m_destinationCallback;
}; // class TransitionContract

} // namespace nsTransition

#endif // TRANSITION_CONTRACT_H
