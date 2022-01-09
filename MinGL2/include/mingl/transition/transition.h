/**
 *
 * @file    transition.h
 * @author  Alexandre Sollier
 * @date    Janvier 2020
 * @version 1.0
 * @brief   Definition d'une transition
 *
 **/

#ifndef TRANSITION_H
#define TRANSITION_H

#include "transition_contract.h"

/**
 * @namespace nsTransition
 * @brief Espace de nom pour le moteur de transition et ses composants
 */
namespace nsTransition
{

/**
 * @class Transition
 * @brief Une classe représentant un TransitionContract en cours de lecture
 */
class Transition : public TransitionContract
{
public:
    /**
     * @brief TransitionMode : Liste de tout les modes de fin de la Transition
     */
    enum TransitionFinishModes {
        FINISH_START, /**< Ce mode de fin met les valeurs de la cible a celles de départ */
        FINISH_CURRENT, /**< Ce mode de fin ne touche pas aux valeurs actuelles de la cible */
        FINISH_DESTINATION, /**< Ce mode de fin met les valeurs de la cible a celles d'arrivé */
    };

    /**
     * @brief Constructeur pour la classe Transition
     * @param[in] contract : Contrat utilisé pour initialiser cette Transition
     * @fn Transition(const TransitionContract& contract);
     */
    Transition(const TransitionContract& contract);

    /**
     * @brief Retourne le temps écoulé pour cette Transition
     * @return Une référence const vers m_elapsed
     * @fn const SystemDuration_t& getElapsed() const;
     */
    const SystemDuration_t& getElapsed() const;

    /**
     * @brief Définit un nouveau temps écoulé pour cette Transition,
     * puis met a jour les valeurs de la cible
     * @param[in] elapsed : Nouveau temps écoulé
     * @fn void setElapsed(const SystemDuration_t& elapsed);
     */
    void setElapsed(const SystemDuration_t& elapsed);

    /**
     * @brief Rajoute une durée au temps écoulé actuel
     * @param[in] addedTime : Durée a rajouter
     * @fn void addToElapsed(const SystemDuration_t& addedTime);
     */
    void addToElapsed(const SystemDuration_t& addedTime);

    /**
     * @brief Indique si cette Transition est en train de se jouer a l'envers
     * @return Une référence const vers m_reverse
     * @fn const bool& isReversed() const;
     */
    const bool& isReversed() const;

    /**
     * @brief Marque cette Transition comme terminée, en utilisant le mode spécifié
     * @param[in] finishMode : Mode utilisé pour finir cette Transition (Valeurs d'arrivé par défaut)
     * @fn void finish();
     */
    void finish(const TransitionFinishModes& finishMode = TransitionFinishModes::FINISH_DESTINATION);

    /**
     * @brief Indique si cette Transition est marquée comme terminée
     * @return Une référence const vers m_finished
     * @fn const bool& isFinished() const;
     */
    const bool& isFinished() const;

private:
    /**
     * @brief m_startTime : Stocke le temps du début de cette Transition
     */
    SystemTimePoint_t m_startTime;

    /**
     * @brief m_elapsed : Stocke le temps écoulé
     */
    SystemDuration_t m_elapsed;

    /**
     * @brief m_reverse : Flag set si cette Transition se joue a l'envers
     * i.e. se jouant des valeurs d'arrivé vers celles de départ
     */
    bool m_reverse;

    /**
     * @brief m_finished : Flag set si cette Transition doit être considérée terminée
     * Le moteur de transition utilisé doit enlever une telle Transition de sa liste
     */
    bool m_finished;

    /**
     * @brief Calcule et définit les nouvelles valeurs a la cible,
     * basé sur le temps écoulé, la durée de la transition et le temps de départ
     * @fn void updateValues();
     */
    void updateValues();

    /**
     * @brief Appelé quand cette Transition s'est terminée
     * @fn void handleEndlife();
     */
    void handleEndlife();
}; // class Transition

} // namespace nsTransition

#endif // TRANSITION_H
