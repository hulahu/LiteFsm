#ifndef LITEFSMDEMO_LITE_FSM_DEMO_ACTION_H
#define LITEFSMDEMO_LITE_FSM_DEMO_ACTION_H

#include "LiteFsmDemoMeta.h"

#include <iostream>

namespace liteFsmDemo
{

struct Actions
{
  static inline struct ActionA
  {
    auto operator()(bool& r, uint32_t& data) const
    {
      return [=](Meta& meta) {
        std::cout << "actionA: r=" << r << " data=" << data << std::endl;
        meta.setHumidity(data);
      };
    }
  } const actionA;

  static inline struct ActionB
  {
    auto operator()() const
    {
      return [=](const Meta&) {
        std::cout << "actionB: none" << std::endl;
      };
    }
  } const actionB;

  static inline struct ActionC
  {
    auto operator()() const
    {
      return [=](Meta& meta) {
        std::cout << "actionC: meta.mTemperature=" << meta.getTemperature() << std::endl;
      };
    }
  } const actionC;
};
}
#endif
