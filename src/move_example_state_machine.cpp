#include "ros_state_machine/move_example_state_machine.h"
#include <algorithm>

void MoveStateMachine::DefineTransitions()
{
    mCurrentState = State::STOPPED;

    // Set of rules and actions created for each state and trigger 
    mRules[State::STOPPED] = {
        {Trigger::MOVE, [&](){SimpleTransitionAction(State::MOVING);}}
    };

    mRules[State::MOVING] = {
        {Trigger::STOP, [&](){SimpleTransitionAction(State::STOPPED);}}
    };

    mRules[State::STUCK] = {
        {Trigger::RETREAT, [&](){SimpleTransitionAction(State::MOVING);}},
        {Trigger::STOP, [&](){DoNothingAction();}}
    };
}

ProcessTransitionResult MoveStateMachine::ProcessTrigger(const Trigger& triggerEvent)
{
    if (triggerEvent < Trigger::MOVE && triggerEvent > Trigger::RETREAT)
        return ProcessTransitionResult::UNKNOWN;
    
    // Check whether the trigger event exists
    auto triggerIterator = std::find_if(mRules[mCurrentState].begin(), mRules[mCurrentState].end(),
        [&](const std::pair<Trigger, TransitionAction>& element){ return element.first == triggerEvent;} );

    // If it does not exist return error
    if (triggerIterator == mRules[mCurrentState].end())
        return ProcessTransitionResult::IMPOSSIBLE_TRANSITION;
    
    // Make the transition happen
    triggerIterator->second();

    return ProcessTransitionResult::SUCCESS;
}