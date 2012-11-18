#pragma once

#include <stdint.h>
#include <arm-halib/core/register.h>
#include <arm-halib/core/fcpu.h>
#include "gpio.h"

namespace arm_halib{
namespace driver
{
        struct Uart0
        {
            Gpio<0> gpioA;
            static const uint32_t enable           = 0x1;
            static const uint32_t txEnable         = 0x100;
            static const uint32_t rxEnable         = 0x200;
            static const uint32_t baudRateMask     = 0xffff;
            static const uint32_t baudRateFraqMask = 0x3f;
            static const uint32_t fifoEnable       = 0x10;
            static const uint8_t  byteCountShift   = 0x5;
            static const uint32_t byteCountMask    = 0x3;
            static const uint32_t busyFlag         = 0x8;


            union UartRegMap
            {
                struct
                {
                    uint8_t  __base0[0x4000C000];
                    Register data;
                };

                struct
                {
                    uint8_t  __base1[0x4000C018];
                    Register flags;
                };

                struct
                {
                    uint8_t  __base2[0x4000C024];
                    Register baudRateDivisor;
                    Register baudRateDivisorFraction;
                    Register lineControl;
                    Register control;
                };

                struct
                {
                    uint8_t  __base3[0x4000CFC8];
                    Register clockSelect;
                };

                struct
                {
                    uint8_t  __base4[0x400FE618];
                    Register clockEnable;
                };
            };

            Uart0() : gpioA(0x3, 0x2, 0x3)
            {
                UartRegMap& rm = *static_cast<UartRegMap*>(0);
                rm.clockEnable             = 0x01;
                while(rm.flags & busyFlag);
                rm.lineControl             &= ~fifoEnable;
                rm.control                 &= ~(enable | txEnable | rxEnable);
                
                rm.baudRateDivisor         = (F_CPU/16/115200) & baudRateMask;
                rm.baudRateDivisorFraction = (F_CPU*64/16/115200) & baudRateFraqMask;
                rm.lineControl             = (3 & byteCountMask) << byteCountShift;
                rm.clockSelect             = 0x0;
                rm.control                 |= (enable | txEnable);
            }
            
            bool ready() const
            {
                UartRegMap& rm = *static_cast<UartRegMap*>(0);
                return !(rm.flags & busyFlag);
            }

            void put(uint8_t c)
            {
                UartRegMap& rm = *static_cast<UartRegMap*>(0);
                rm.data = c;
            }
        };
}
}

