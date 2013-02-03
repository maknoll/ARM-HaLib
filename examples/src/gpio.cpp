#include <platform.h>

#include <arm-halib/regmaps/local.h>

#include <gpio.h>
#include <arm-halib/core/delay.h>

using arm_halib::delay_ms;

struct RedConfig
{
  typedef arm_halib::regmaps::local::GpioBank<arm_halib::regmaps::local::GpioBanks::f> RegMap;
  static const uint8_t pin = 1;
  static const bool output = true;
  static const bool special = false;
  static const uint8_t specialSource = 0x0;
};

typedef arm_halib::driver::GpioPin<RedConfig> RedLed;

int main()
{
  log::emit() << "GPIO test" << log::endl;
  RedLed red;
  
  while(true)
  {
    delay_ms(1000);
    red.toggle();
  }

  return 0;
}
