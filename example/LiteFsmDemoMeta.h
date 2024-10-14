#ifndef LITEFSMDEMO_LITE_FSM_DEMO_META_H
#define LITEFSMDEMO_LITE_FSM_DEMO_META_H

#include <cstdint>

namespace liteFsmDemo
{

class Meta
{
public:
  Meta(uint32_t& temperature, uint32_t& humidity, uint32_t& windSpeed)
      : mTemperature(temperature)
      , mHumidity(humidity)
      , mWindSpeed(windSpeed)
  {}
  Meta(const Meta&) = delete;

  uint32_t getTemperature() const
  {
    return mTemperature;
  }

  void setHumidity(const uint32_t& humidity)
  {
    mHumidity = humidity;
  }

private:
  uint32_t& mTemperature;
  uint32_t& mHumidity;
  uint32_t& mWindSpeed;
};

}
#endif
