#ifndef LITEFSMDEMO_LITE_FSM_DEMO_STATE_H
#define LITEFSMDEMO_LITE_FSM_DEMO_STATE_H

#include "LiteFsm.h"
#include "LiteFsmDemoMeta.h"

#include <iostream>


namespace liteFsmDemo
{

using DemoState = liteFsm::State<Meta>;

class StateA : public DemoState
{
public:
  StateA()
      : State("StateA")
  {}
};

class StateB : public DemoState
{
public:
  StateB()
      : State("StateB")
  {}
};

class StateC : public DemoState
{
public:
  StateC()
      : State("StateC")
  {}

  void onEnter(Meta& meta) final
  {
    std::cout << "Entering State C"
              << " meta.mTemperature=" << meta.getTemperature() << std::endl;
  }

  void onExit(Meta&) final
  {
    std::cout << "Exiting State C" << std::endl;
  }
};

}
#endif
