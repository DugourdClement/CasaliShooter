/**
 *
 * @file    event_manager.cpp
 * @author  Alexandre Sollier
 * @date    Décembre 2019
 * @version 1.0
 * @brief   Gestionnaire d'événements de minGL
 *
 **/

#include "mingl/event/event_manager.h"

bool nsEvent::EventManager::hasEvent()
{
    return m_eventQueue.size() > 0;
} // hasEvent()

void nsEvent::EventManager::pushEvent(const Event_t& event)
{
    m_eventQueue.push(event);
} // pushEvent()

const nsEvent::Event_t nsEvent::EventManager::pullEvent()
{
    // Copy the first element and then remove it from the queue
    const Event_t event = m_eventQueue.front();
    m_eventQueue.pop();
    return event;
} // pullEvent()

void nsEvent::EventManager::clearEvents()
{
    while (!m_eventQueue.empty())
        m_eventQueue.pop();
} // clearEvents()
