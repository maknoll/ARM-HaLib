#pragma once

#include <stdint.h>
#include <arm-halib/core/register.h>

namespace arm_halib{
namespace driver
{
    template<uint8_t i>
    class Gpio
    {
        struct RegMap
        {
            union
            {
                struct
                {
                    uint8_t __base[0x40058000+i*0x1000];
                    union
                    {
                        struct
                        {
                            uint8_t  __offset0[0];
                            Register data[0xFF];
                        };

                        struct
                        {
                            uint8_t  __offset1[0x400];
                            Register dir;
                        };

                        struct
                        {
                            uint8_t  __offset2[0x420];
                            Register nonGpio;
                        };

                        struct
                        {
                            uint8_t  __offset3[0x51C];
                            Register padEnable;
                        };
                    };
                };

                struct
                {
                    uint8_t  __base4[0x400FE608];
                    Register clockEnable;
                };

                struct
                {
                    uint8_t  __base5[0x400FE06C];
                    Register highSpeedEnable;
                };


            };
        };

        public:
        Gpio(uint8_t enabledPads, uint8_t padDirection, uint8_t nonGpio)
        {
            RegMap& rm         = *static_cast<RegMap*>(0);
            rm.clockEnable     |= 1<<i;
            rm.highSpeedEnable |= 1<<i;
            delay_us(1);
            
            rm.dir       |= enabledPads;
            rm.padEnable |= padDirection;
            rm.nonGpio   |= nonGpio;
        }

        void toggle(uint8_t mask)
        {
            RegMap& rm = *static_cast<RegMap*>(0);
            rm.data[mask] = ~rm.data[0xFF];
        }

        void set(uint8_t mask, uint8_t value)
        {
            RegMap& rm = *static_cast<RegMap*>(0);
            rm.data[mask] = value;
        }

        uint8_t value(uint8_t mask)
        {
            RegMap& rm = *static_cast<RegMap*>(0);
            return rm.data[mask];
        }
    };
}
}
