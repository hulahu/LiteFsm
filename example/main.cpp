#include "LiteFsmDemoAction.h"
#include "LiteFsmDemoEvent.h"
#include "LiteFsmDemoGuard.h"
#include "LiteFsmDemoState.h"

#include <stdint.h>


int main()
{
  using namespace liteFsmDemo;
  using namespace liteFsm;

  uint32_t temperature = 100;
  uint32_t humidity = 101;
  uint32_t windSpeed = 102;
  Meta meta(temperature, humidity, windSpeed);
  Fsm<Meta> fsm(meta);

  StateA stateA;
  StateB stateB;
  StateC stateC;

  uint32_t data = 10;
  bool ret = false;

  // clang-format off
  stateA.addTransition(event<Events::toB>,  Guards::guardA(ret, data),      Actions::actionA(ret, data),        stateB);
  stateA.addTransition(event<Events::toC>,  Guards::guardC(),              Actions::actionC(),                  stateC);

  stateB.addTransition(event<Events::toA>,  Guards::guardB(ret, data),      Actions::actionB(),                 stateA);
  stateB.addTransition(event<Events::toC>,  Guards::guardB(ret, data),      nullptr,                            stateB);

  stateC.addTransition(event<Events::toA>,  Guards::guardA(ret, data),      nullptr,                            stateB);
  stateC.addTransition(event<Events::toB>,  Guards::guardC(),               nullptr,                            stateB);
  stateC.addTransition(event<Events::toC>,  Guards::guardC(),               [](Meta&) { /* do nothing*/ },      stateC);
  // clang-format on

  fsm.addState(stateA, stateB, stateC);
  fsm.start(stateA.getName());

  fsm.handleEvent(event<Events::toB>);
  fsm.handleEvent(event<Events::toA>);
  fsm.handleEvent(event<Events::toC>);
  fsm.handleEvent(event<Events::toA>);

  return 0;
}
