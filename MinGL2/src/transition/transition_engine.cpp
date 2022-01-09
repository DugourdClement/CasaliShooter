/**
 *
 * @file    transition_engine.h
 * @author  Alexandre Sollier
 * @date    Janvier 2020
 * @version 1.0
 * @brief   Gestionnaire de transition de minGL
 *
 **/

#include "mingl/transition/transition_engine.h"

#define TRANSITIONENGINE nsTransition::TransitionEngine

void TRANSITIONENGINE::update(const std::chrono::microseconds &delta)
{
    // Update every transitioned items
    TransitionVector_t::iterator iter = m_transitionList.begin();
    while (iter != m_transitionList.end())
    {
        // Check if the item is finished, and remove it from the list in that case
        if (iter->isFinished())
        {
            m_transitionList.erase(iter++);
        }
        else
        {
            iter->addToElapsed(delta);
            ++iter;
        }
    }
} // update()

void TRANSITIONENGINE::startContract(const TransitionContract &contract)
{
    m_transitionList.push_back(Transition(contract));
} // startContract()

void TRANSITIONENGINE::finishEveryTransition(const Transition::TransitionFinishModes &finishMode)
{
    // Mark every transition as finished
    for (Transition &transition : m_transitionList)
    {
        transition.finish(finishMode);
    }
} // finishEveryTransition()

void TRANSITIONENGINE::finishEveryTransitionOfTarget(const ITransitionable &transitionable, const Transition::TransitionFinishModes &finishMode)
{
    for (Transition &transition : m_transitionList)
    {
        // Check if the address of the target is the same one as the address of transitionable
        if (&(transition.getTarget()) == &transitionable)
        {
            transition.finish(finishMode);
        }
    }
}  // finishEveryTransitionOfTarget()

#undef TRANSITIONENGINE
