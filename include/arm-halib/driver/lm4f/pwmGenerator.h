#pragma once

#include <stdint.h>
#include <arm-halib/regmaps/local.h>
#include "gpio.h"

namespace arm_halib{
namespace driver{

        struct PwmChannels
        {
          enum PwmChannelType{a,b};
        };
        typedef PwmChannels::PwmChannelType PwmChannelType;

        namespace helper
        {
          using namespace regmaps::local;

          template<typename Config>
          class PwmGeneratorA : private GpioPin<typename Config::GpioConfig>
          {
            private:
              typedef typename Config::RegMap RegMap;
            public:
            PwmGeneratorA() : GpioPin<typename Config::GpioConfig>()
            {
              RegMap& rm = *reinterpret_cast<RegMap*>(0);
              rm.enable |= 0x1 << RegMap::index;
              rm.config = 0x4;
              rm.a.en = false;
              rm.a.ams= 0x1;
              rm.a.cmr = 0x0;
              rm.a.mr = 0x2;
              rm.a.pwml = Config::invert;
              asm("":::"memory");
            }

            void dutyCycle(uint16_t value)
            { 
              RegMap& rm = *reinterpret_cast<RegMap*>(0);      
              rm.a.interval = value;
              asm("":::"memory");
            }

            uint16_t dutyCycle() const
            {
              RegMap& rm = *reinterpret_cast<RegMap*>(0);
              asm("":::"memory");
              return rm.a.interval;
            }

            void value(uint16_t value)
            {
              RegMap& rm = *reinterpret_cast<RegMap*>(0);      
              rm.a.match = value;
              asm("":::"memory");
            }

            uint16_t value() const
            {
              RegMap& rm = *reinterpret_cast<RegMap*>(0);      
              asm("":::"memory");
              return rm.a.match;
            }

            void enable()
            {
              RegMap& rm = *reinterpret_cast<RegMap*>(0);      
              rm.a.en = true;
              asm("":::"memory");
            }

            void disable()
            {
              RegMap& rm = *reinterpret_cast<RegMap*>(0);      
              rm.a.en = false;
              asm("":::"memory");       
            }

            bool active() const
            {
              RegMap& rm = *reinterpret_cast<RegMap*>(0);      
              asm("":::"memory");
              return rm.a.en;       
            }
          };

          template<typename Config>
          class PwmGeneratorB : private GpioPin<typename Config::GpioConfig>
          {
            private:
              typedef typename Config::RegMap RegMap;
            public:
            PwmGeneratorB() : GpioPin<typename Config::GpioConfig>()
            {
              RegMap& rm = *reinterpret_cast<RegMap*>(0);
              rm.enable |= 0x1 << RegMap::index;
              rm.config = 0x4;
              rm.b.en = false;
              rm.b.ams= 0x1;
              rm.b.cmr = 0x0;
              rm.b.mr = 0x2;
              rm.b.pwml = Config::invert;
              asm("":::"memory");
            }

            void dutyCycle(uint16_t value)
            {
              RegMap& rm = *reinterpret_cast<RegMap*>(0);      
              rm.b.interval = value;
              asm("":::"memory");
            }

            uint16_t dutyCycle() const
            {
              RegMap& rm = *reinterpret_cast<RegMap*>(0);      
              asm("":::"memory");
              return rm.b.interval;
            }

            void value(uint16_t value)
            {
              RegMap& rm = *reinterpret_cast<RegMap*>(0);
              rm.b.match = value;
              asm("":::"memory");
            }

            uint16_t value() const
            {
              RegMap& rm = *reinterpret_cast<RegMap*>(0);      
              asm("":::"memory");
              return rm.b.match;
            }

            void enable()
            {
              RegMap& rm = *reinterpret_cast<RegMap*>(0);
              rm.b.en = true;
              asm("":::"memory");
            }

            void disable()
            {
              RegMap& rm = *reinterpret_cast<RegMap*>(0);      
              rm.b.en = false;
              asm("":::"memory");       
            }

            bool active() const
            {
              RegMap& rm = *reinterpret_cast<RegMap*>(0);
              asm("":::"memory");
              return rm.b.en;       
            }
          };

          template<typename Config>
          struct GpioConfigGenerator
          {
            struct type : public Config
            {
              struct GpioConfig
              {
                static const bool output = true;
                static const bool special = true;
                static const uint8_t specialSource = 0x7;
                static const uint8_t pin = Config::pin;
                typedef arm_halib::regmaps::local::GpioBank<Config::bank> RegMap;
              };
            };
          };

          template<PwmChannelType channel, typename Config>
          struct PwmConfigurator;

          template<typename Config>
          struct PwmConfigurator<PwmChannels::a, Config>
          {
            typedef typename GpioConfigGenerator<Config>::type ExtendedConfig;
            typedef PwmGeneratorA<ExtendedConfig> type;
          };

          template<typename Config>
          struct PwmConfigurator<PwmChannels::b, Config>
          {
            typedef typename GpioConfigGenerator<Config>::type ExtendedConfig;
            typedef PwmGeneratorB<ExtendedConfig> type;
          };
        }

        template<typename Config>
        class PwmGenerator : public helper::PwmConfigurator<Config::channel, Config>::type{};
}
}
