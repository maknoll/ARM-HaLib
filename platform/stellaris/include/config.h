#pragma once

#include <uart0.h>
#include <pwmGenerator.h>
#include <arm-halib/regmaps/local.h>
#include <logging/logging.h>

namespace platform{
namespace stellaris
{

  using namespace ::logging;
  using namespace arm_halib;
  using arm_halib::regmaps::local::Timer;
  using arm_halib::driver::PwmGenerator;
  using arm_halib::driver::PwmChannelType;
  using arm_halib::driver::PwmChannels;
  using arm_halib::regmaps::local::GpioBankType;
  using arm_halib::regmaps::local::GpioBanks;

  struct LogUart : public arm_halib::driver::Uart0
  {
      LogUart& operator<<(char c)
      {
          while(!ready());
          put(c);
          return *this;
      }
  };

  typedef OutputLevelSwitchDisabled <
              OutputStream<
                  LogUart
              > 
          > LogType;

  struct RedConfig
  {
    typedef Timer<0> RegMap;
    static const PwmChannelType channel = PwmChannels::b;
    static const GpioBankType bank = GpioBanks::f;
    static const uint8_t pin = 1;
    static const bool invert = true;
  };

  struct BlueConfig
  {
    typedef Timer<1> RegMap;
    static const PwmChannelType channel = PwmChannels::a;
    static const GpioBankType bank = GpioBanks::f;
    static const uint8_t pin = 2;
    static const bool invert = true;
  };

  struct GreenConfig
  {
    typedef Timer<1> RegMap;
    static const PwmChannelType channel = PwmChannels::b;
    static const GpioBankType bank = GpioBanks::f;
    static const uint8_t pin = 3;
    static const bool invert = true;
  };

  typedef PwmGenerator<RedConfig> RedLed;
  typedef PwmGenerator<BlueConfig> BlueLed;
  typedef PwmGenerator<GreenConfig> GreenLed;

}
}
