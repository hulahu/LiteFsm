#ifndef LITEFSMDEMO_LITE_FSM_DEMO_GUARD_H
#define LITEFSMDEMO_LITE_FSM_DEMO_GUARD_H

#include "LiteFsmDemoMeta.h"

#include <iostream>


namespace liteFsmDemo
{

struct Guards
{
  static inline struct GuardA
  {
    auto operator()(bool& r, uint32_t& data) const
    {
      return [&](Meta& meta) {
        std::cout << "guardA: r=" << r << " data=" << data << " meta.mTemperature=" << meta.getTemperature()
                  << std::endl;
        --data;
        return !r;
      };
    }
  } const guardA;

  static inline struct GuardB
  {
    auto operator()(bool& r, uint32_t& data) const
    {
      return [=](const Meta&) {
        std::cout << "guardB: r=" << r << " data=" << data << std::endl;
        return !r;
      };
    }
  } const guardB;

  static inline struct GuardC
  {
    auto operator()() const
    {
      return [](const Meta&) {
        return true;
      };
    };
  } const guardC;
};

}
#endif
