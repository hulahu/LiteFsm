#ifndef LITEFSM_LITE_FSM_STATE_H
#define LITEFSM_LITE_FSM_STATE_H

#include <functional>
#include <iostream>
#include <string_view>
#include <typeinfo>
#include <unordered_map>

namespace liteFsm
{

// Guard and Action types
template <typename M>
using Guard = std::function<bool(M&)>;

template <typename M>
using Action = std::function<void(M&)>;

// Event type
template <typename E>
struct Event
{
  bool operator==(const Event& other) const
  {
    return dynamic_cast<const E*>(&other) != nullptr;
  }

  std::size_t hash() const
  {
    return typeid(E).hash_code();
  }

  static constexpr std::string_view to_string()
  {
    return typeid(E).name();
  }
};

/// @brief Base State class, represents a state in a finite state machine.
/// This class provides the base for creating states within a finite state machine.
/// It supports entering and exiting actions, as well as transitions to other states.
/// @tparam M The type of the meta data.
template <typename M>
class State
{
public:
  struct Transition
  {
    std::string_view nextStateName;
    Guard<M> guard;
    Action<M> action;
  };
  using TransitionMap = std::unordered_map<std::size_t, Transition>;

  explicit State(const std::string_view& name)
      : mStateName(name)
  {}
  virtual ~State() = default;

  /// @brief Action to be performed when the state is entered.
  /// This method can be overridden to perform custom actions upon entering the state.
  /// @para The meta object to be passed to the state.
  virtual void onEnter(M& meta)
  {
    std::cout << "Entering state " << mStateName << std::endl;
  }

  /// @brief Action to be performed when the state is exited.
  /// This method can be overridden to perform custom actions upon exiting the state.
  /// @param meta The meta object to be passed to the state.
  virtual void onExit(M& meta)
  {
    std::cout << "Exiting state " << mStateName << std::endl;
  }

  /// @brief Adds a transition from this state to another state.
  /// @param event The event that triggers the transition.
  /// @param guard A guard function that must return true for the transition to occur.
  /// @param action An action to be performed during the transition.
  /// @param nextState The state to transition to.
  /// @tparam E The type of the event.
  /// @tparam M The type of meta data.
  template <typename E>
  inline void
    addTransition(const Event<E>& event, const Guard<M>& guard, const Action<M>& action, const State& nextState)
  {
    const auto& to = nextState.getName();
    mTransitions[event.hash()] = {to, guard, action};
  }

  /// @brief Gets the transitions map for this state.
  /// @return A constant reference to the transitions map.
  const TransitionMap& getTransitions() const
  {
    return mTransitions;
  }

  /// @brief Gets the name of the state.
  /// @return A constant string view reference to the state's name.
  const std::string_view& getName() const
  {
    return mStateName;
  }

private:
  const std::string_view mStateName; ///< The name of the state.
  TransitionMap mTransitions;        ///< Map of transitions from this state.
};

/// @var template <typename E> Event<E> event
/// @brief The event instance for the event E
template <typename E>
inline const Event<E> event;

}
#endif
