/**
 *
 * @file    transition_contract.cpp
 * @author  Alexandre Sollier
 * @date    Janvier 2020
 * @version 1.0
 * @brief   Création de la transition
 *
 **/

#include "mingl/transition/transition_contract.h"

#define TRANSITIONCONTRACT nsTransition::TransitionContract

TRANSITIONCONTRACT::TransitionContract(ITransitionable& target, const int &id,
                                       const SystemDuration_t &duration, const std::vector<float> &destination,
                                       const SystemDuration_t &delay,
                                       const TransitionMode &transitionMode)
    : m_id(id)
    , m_target(target)
    , m_transitionMode(transitionMode)
    , m_destination(destination)
    , m_duration(duration)
    , m_delay(delay)
{
    m_beginning.resize(destination.size());
    target.getValues(id, m_beginning);
} // TransitionContract()

const int& TRANSITIONCONTRACT::getId() const
{
    return m_id;
} // getId()

const TRANSITIONCONTRACT::TransitionMode& TRANSITIONCONTRACT::getTransitionMode() const
{
    return m_transitionMode;
} // getTransitionMode()

const std::vector<float>& TRANSITIONCONTRACT::getBeginning() const
{
    return m_beginning;
} // getBeginning()

const std::vector<float>& TRANSITIONCONTRACT::getDestination() const
{
    return m_destination;
} // getDestination()

const nsTransition::SystemDuration_t &TRANSITIONCONTRACT::getDuration() const
{
    return m_duration;
} // getDuration()

void TRANSITIONCONTRACT::setDestinationCallback(const std::function<void ()> &callback)
{
    m_destinationCallback = callback;
} // setFinishCallback()

const nsTransition::ITransitionable& TRANSITIONCONTRACT::getTarget() const
{
    return m_target;
} // getTarget()

#undef TRANSITIONCONTRACT
