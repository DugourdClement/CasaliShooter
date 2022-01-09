/**
 *
 * @file    transition.h
 * @author  Alexandre Sollier
 * @date    Janvier 2020
 * @version 1.0
 * @brief   Definition d'une transition
 *
 **/

#include "mingl/transition/transition.h"

#include <algorithm>

#define TRANSITION nsTransition::Transition

TRANSITION::Transition(const TransitionContract &contract)
    : TransitionContract(contract)
    , m_startTime(std::chrono::steady_clock::now() + m_delay)
    , m_elapsed(0)
    , m_reverse(false)
    , m_finished(false)
{} // Transition()

const nsTransition::SystemDuration_t& TRANSITION::getElapsed() const
{
    return m_elapsed;
} // getElapsed()

void TRANSITION::setElapsed(const nsTransition::SystemDuration_t &elapsed)
{
    // Don't allow to set the elapsed time if the start time is ahead of clock
    if (std::chrono::steady_clock::now() < m_startTime) return;

    // Set the new elapsed time
    m_elapsed = elapsed;

    // Update the target values
    updateValues();
} // setElapsed()

void TRANSITION::addToElapsed(const nsTransition::SystemDuration_t &addedTime)
{
    setElapsed(getElapsed() + addedTime);
} // addToElapsed()

const bool &TRANSITION::isReversed() const
{
    return m_reverse;
} // isReversed()

void TRANSITION::finish(const TransitionFinishModes &finishMode)
{
    m_finished = true;

    switch (finishMode)
    {
        case TRANSITION::TransitionFinishModes::FINISH_START:
            m_target.setValues(m_id, m_beginning);

            break;
        case TRANSITION::TransitionFinishModes::FINISH_DESTINATION:
            m_target.setValues(m_id, m_destination);

            break;
        default:
            break;
    }
} // finish()

const bool& TRANSITION::isFinished() const
{
    return m_finished;
} // isFinished()

void TRANSITION::updateValues()
{
    // Prevent further progress if this transition is marked finished
    if (m_finished)
        return;

    // Get the elapsed progress and clamp it between 0 and 1
    float elapsedProgress = m_elapsed / m_duration;
    elapsedProgress = std::max(0.f, std::min(elapsedProgress, 1.f));

    // If we are in reverse mode, reverse the progress
    float effectiveElapsedProgress = (!m_reverse) ? elapsedProgress : 1 - elapsedProgress;

    // Compute the new values
    std::vector<float> updatedValues(m_beginning.size());
    for (size_t i = 0; i < m_beginning.size(); ++i)
    {
        updatedValues[i] = ((m_destination[i] - m_beginning[i]) * effectiveElapsedProgress) + m_beginning[i];
    }

    // Set the new values to the target
    m_target.setValues(m_id, updatedValues);

    // Transition has finished, call the endlife handler
    if (elapsedProgress == 1.f)
    {
        handleEndlife();
    }
} // updateValues()

void TRANSITION::handleEndlife()
{
    switch (m_transitionMode)
    {
        case TransitionContract::TransitionMode::MODE_FINITE:
            // In finite mode, the transition is terminated when it's done
            finish(FINISH_DESTINATION);

            break;
        case TransitionContract::TransitionMode::MODE_FINITE_REVERSE:
            // In finite reverse mode, the transition is reversed when done, and finished when reversed
            if (!m_reverse)
            {
                m_reverse = true;

                m_startTime = std::chrono::steady_clock::now();
                m_elapsed = SystemDuration_t::zero();
            }
            else
            {
                finish(FINISH_START);
            }

            break;
        case TransitionContract::TransitionMode::MODE_LOOP:
            // In loop mode, the target is set to its beginning values before going again
            m_target.setValues(m_id, m_beginning);

            m_startTime = std::chrono::steady_clock::now();
            m_elapsed = SystemDuration_t::zero();

            break;
        case TransitionContract::TransitionMode::MODE_LOOP_SMOOTH:
            // In loop smooth mode, we invert the reverse boolean before going again
            m_reverse = !m_reverse;

            m_startTime = std::chrono::steady_clock::now();
            m_elapsed = SystemDuration_t::zero();

            break;
    }

    // Call the finish callback if set
    if (m_destinationCallback)
    {
        m_destinationCallback();
    }
} // handleEndlife()

#undef TRANSITION
