/**
 *
 * @file    event_manager.h
 * @author  Alexandre Sollier
 * @date    Décembre 2019
 * @version 1.0
 * @brief   Gestionnaire d'événements de minGL
 *
 **/

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <queue>

#include "event.hpp"

namespace nsEvent {

/**
 * @class EventManager
 * @brief Gère une queue d'événement entrants
 */
class EventManager
{

public:
    /**
     * @brief Vérifie si un événement doit être traité
     * @return Si la queue possède au moins un élément
     * @fn bool hasEvent();
     */
    bool hasEvent();

    /**
     * @brief Pousse un nouvel événement dans la queue
     * @param[in] event : Evénement a pousser
     * @fn void pushEvent(const Event_t& event);
     */
    void pushEvent(const Event_t& event);

    /**
     * @brief Tire l'événement le plus ancien, et l'enlève de la queue
     * @return Une copie du plus ancien événement
     * @fn const Event_t pullEvent();
     */
    const Event_t pullEvent();

    /**
     * @brief Vide la queue
     * @fn void clearEvents();
     */
    void clearEvents();

private:
    /**
     * @brief m_eventQueue : Queue possèdant des événement entrants
     */
    std::queue<Event_t> m_eventQueue;

}; // class EventManager

} // namespace nsEvent

#endif // EVENTMANAGER_H
