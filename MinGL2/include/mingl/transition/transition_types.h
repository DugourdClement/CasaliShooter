/**
 *
 * @file    transition_types.h
 * @author  Alexandre Sollier
 * @date    Janvier 2020
 * @version 1.0
 * @brief   Définit quelques types pour les transitions
 *
 **/

#ifndef TRANSITION_TYPES_H
#define TRANSITION_TYPES_H

#include <chrono>

namespace nsTransition
{

/**
 * @brief SystemDuration_t : Définition de type stockant une durée exprimée en nanosecondes, sous forme de float
 */
typedef std::chrono::duration<float, std::nano> SystemDuration_t;

/**
 * @brief SystemTimePoint_t : Définition de type représentant un point dans le temps basée sur l'horloge système
 */
typedef std::chrono::time_point<std::chrono::steady_clock, SystemDuration_t> SystemTimePoint_t;

} // namespace nsTransition

#endif // TRANSITION_TYPES_H
