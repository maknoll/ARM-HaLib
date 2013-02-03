#pragma once

#include <stdint.h>
#include <arm-halib/core/register.h>
#include <arm-halib/core/delay.h>

namespace arm_halib{
namespace driver
{
    namespace helper
    {
      template<typename Config>
      class BasicGpioPin
      {
        private:
          typedef typename Config::RegMap RegMap;
        public:
          BasicGpioPin()
          {
            RegMap& rm         = *reinterpret_cast<RegMap*>(0);
            rm.enableBank     |= 0x1 << RegMap::bank;
            rm.highSpeedBank  |= 0x1 << RegMap::bank;
            delay_us(1);
         
            rm.active     |= 0x1 << Config::pin;
          }

          void triState(bool value)
          {
              RegMap& rm = *static_cast<RegMap*>(0);
              if(value)
                rm.active&=~(0x1 << Config::pin);
              else
                rm.active|=0x1 << Config::pin;
          }

          bool triState() const
          {
              RegMap& rm = *static_cast<RegMap*>(0);
              return !rm.active&(0x1 << Config::pin);
          }
      };
      
      template<typename Config>
      class SpecialGpioPin : public BasicGpioPin<Config>
      {
        private:
          typedef typename Config::RegMap RegMap;
        public:
          SpecialGpioPin() : BasicGpioPin<Config>()
          {
            RegMap& rm        = *reinterpret_cast<RegMap*>(0);
            rm.special       |= 0x1 << Config::pin;
            rm.specialSelect |= Config::specialSource << (Config::pin*4);

            if(Config::output)
              rm.dir |= 0x1 << Config::pin;
            else
              rm.dir &= ~(0x1 << Config::pin);
          }
      };

      template<typename Config>
      class OutputGpioPin : public BasicGpioPin<Config>
      {
        private:
          typedef typename Config::RegMap RegMap;
        public:
          OutputGpioPin() : BasicGpioPin<Config>()
          {
            RegMap& rm  = *reinterpret_cast<RegMap*>(0);
            rm.special &= ~(0x1 << Config::pin);
            rm.dir |= 0x1 << Config::pin;
          }

          void toggle()
          {
              RegMap& rm = *static_cast<RegMap*>(0);
              rm.data[0x1<<Config::pin] = ~rm.data[0x1<<Config::pin];
          }

          void value(bool value)
          {
              RegMap& rm = *static_cast<RegMap*>(0);
              rm.data[0x1 << Config::pin] = value;
          }

          bool value() const
          {
              RegMap& rm = *static_cast<RegMap*>(0);
              return rm.data[0x1 << Config::pin];
          }
      };

      template<typename Config>
      class InputGpioPin : public BasicGpioPin<Config>
      {
        private:
          typedef typename Config::RegMap RegMap;
        public:
          InputGpioPin() : BasicGpioPin<Config>()
          {
            RegMap& rm  = *reinterpret_cast<RegMap*>(0);
            rm.special &= ~(0x1 << Config::pin);
            rm.dir &= ~(0x1 << Config::pin);
          }

          bool value()
          {
              RegMap& rm = *static_cast<RegMap*>(0);
              return rm.data[0x1 << Config::pin];
          }
      };

      template<bool special, bool output, typename Config>
      struct GpioSelector;

      template<bool output, typename Config>
      struct GpioSelector<true, output, Config> : public SpecialGpioPin<Config>{};

      template<typename Config>
      struct GpioSelector<false, true, Config> : public OutputGpioPin<Config>{};

      template<typename Config>
      struct GpioSelector<false, false, Config> : public InputGpioPin<Config>{};
    };

    template<typename Config>
    class GpioPin : public helper::GpioSelector<Config::special, Config::output, Config>{};
}
}
