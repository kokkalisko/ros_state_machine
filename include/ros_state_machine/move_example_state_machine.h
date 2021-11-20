#ifndef STATE_MACHINE_MOVE_EXAMPLE
#define STATE_MACHINE_MOVE_EXAMPLE

#include <vector>
#include <map>
#include <functional>

enum class State
{
    MOVING = 0,
    STOPPED,
    STUCK
};

enum class Trigger
{
    MOVE = 0,
    STOP,
    RETREAT
};

enum class ProcessTransitionResult
{
    SUCCESS = 0,
    IMPOSSIBLE_TRANSITION,
    UNKNOWN
};

/// Function that translates the State to a string
std::string ResolveState(State state)
{
  switch (state)
  {
    case State::MOVING:
      return "Robot currently moving";
    case State::STOPPED:
      return "Robot currently stopped";
    case State::STUCK:
      return "Robot currently stuck";
    default:
      return "";
  }
}

/// Function that translates the State to a string
std::string ResolveTransitionResult(ProcessTransitionResult result)
{
  switch (result)
  {
    case ProcessTransitionResult::SUCCESS:
      return "Successful transition";
    case ProcessTransitionResult::IMPOSSIBLE_TRANSITION:
      return "Impossible transition";
    case ProcessTransitionResult::UNKNOWN:
      return "Unknown transition";
    default:
      return "";
  }
}

/// Function that translates the Trigger to a string
std::string ResolveTrigger(Trigger trigger)
{
  switch (trigger)
  {
    case Trigger::MOVE:
      return "Move the robot";
    case Trigger::STOP:
      return "Stop the robot";
    case Trigger::RETREAT:
      return "Robot retreat";
    default:
      return "";
  }
}

class MoveStateMachine
{
    typedef std::function<void()> TransitionAction; 

public:
    /// State machine constructor where the set of rules is defined
    MoveStateMachine() { mCurrentState = State::STOPPED; }

    /// Function where the transition rules are defined
    void DefineTransitions();

    /// Get the current state of the SM
    State GetCurrentState() const { return mCurrentState; }

    /// General method to process trigger 
    ProcessTransitionResult ProcessTrigger(const Trigger& triggerEvent);

private:

    // Member functions

    /// Action that simply transits to the given state
    void SimpleTransitionAction(State state) { mCurrentState = state; }

    /// Action that does not perform any function 
    void DoNothingAction() {}

    // Member variables

    // A vector of pairs was preferred than a set of pair due to the 
    // small size of Triggers
    /// Set of rules used to transition between states
    std::map<State, std::vector<std::pair<Trigger, TransitionAction>>> mRules;

    /// Current state of state machine
    State mCurrentState;

};

#endif