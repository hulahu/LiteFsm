#ifndef LITEFSM_LITE_FSM_H
#define LITEFSM_LITE_FSM_H

#include "LiteFsmState.h"

#include <cassert>

namespace liteFsm
{

/// @class Fsm
/// @brief Represents a finite state machine.
/// @tparam M The type of meta data.
template <typename M>
class Fsm
{
public:
  explicit Fsm(M& meta)
      : mMeta(meta)
  {}

  /// @brief Adds a state to the finite state machines.
  /// @param state Reference to the state to be added.
  /// @tparam S The type of the state.
  template <typename S>
  void addState(S& state)
  {
    assert(mStates.find(state.getName()) == mStates.end());
    mStates[state.getName()] = &state;
  }

  /// @brief Adds states to the finite state machine.
  /// @param state Reference to the state to be added.
  /// @tparam S The type of the state.
  /// @tparam Args The types of additional states to be added.
  template <typename S, typename... Args>
  void addState(S& state, Args&... states)
  {
    addState(state);
    addState(states...);
  }

  /// @brief Starts the finite state machine with an initial state.
  /// @param initialState The name of the initial state to start the FSM.
  void start(const std::string_view& initialState)
  {
    mCurrentState = mStates.at(initialState);
    mCurrentState->onEnter(mMeta);
    mCurrentStateName = initialState;
  }

  /// @brief Handles an event and potentially triggers a state transition.
  /// @param event The event to handle.
  /// @tparam E The type of the event data.
  template <typename E>
  void handleEvent(const Event<E>& event)
  {
    const auto& transitions = mCurrentState->getTransitions();
    if (auto it = transitions.find(event.hash()); it != transitions.end())
    {
      const auto& [nextStateName, guard, action] = it->second;
      if ((nextStateName != mCurrentStateName) && guard(mMeta))
      {
        transitionTo(nextStateName, action);
      }
    }
  }

private:
  /// @brief Transitions to a new state.
  /// @param nextStateName The name of the next state to transition to.
  /// @param action The action to perform during the transition.
  /// @tparam M The type of meta data.
  void transitionTo(const std::string_view& nextStateName, const Action<M>& action)
  {
    mCurrentState->onExit(mMeta);

    std::cout << "Transitioning from " << mCurrentStateName << " to " << nextStateName << std::endl;
    if (action != nullptr)
    {
      action(mMeta);
    }

    mCurrentState = mStates.at(nextStateName);
    mCurrentState->onEnter(mMeta);
    mCurrentStateName = nextStateName;
  }

  std::unordered_map<std::string_view, State<M>*> mStates;
  State<M>* mCurrentState = nullptr;
  std::string_view mCurrentStateName;

  M& mMeta;
};

}
#endif
