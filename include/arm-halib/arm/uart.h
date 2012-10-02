#pragma once

#include <stdint.h>
#include <arm-halib/arm/register.h>
#include <arm-halib/arm/fcpu.h>

namespace arm_halib{
namespace driver
{
        struct Uart0
        {
            Uart0()
            {
                static const uint32_t rx0      = 1<<9;
                static const uint32_t tx0      = 1<<10;
                static const uint32_t uart0    = 1<<8;
                static const uint32_t txEnable = 1<<6;
                static const uint32_t noParity = 4<<9;
                static Register* const pioADisableReg = reinterpret_cast<Register*>(0x400E0E04);
                static Register* const pmcPeriEnableReg = reinterpret_cast<Register*>(0x400E0410);
                static Register* const uart0ControlReg  = reinterpret_cast<Register*>(0x400E0600);
                static Register* const uart0ModeReg     = reinterpret_cast<Register*>(0x400E0604);
                static Register* const uart0BaudRateReg  = reinterpret_cast<Register*>(0x400E0620);

                *pmcPeriEnableReg = uart0;
                *pioADisableReg   = rx0 | tx0;
                *uart0ControlReg  = txEnable;
                *uart0ModeReg     = noParity;
                *uart0BaudRateReg = F_CPU / 16 / 115200;
            }
            
            bool ready() const
            {
                static const uint32_t txEmpty  = 1<<9;
                static Register* const uart0StatusReg = reinterpret_cast<Register*>(0x400E0614);
                return (*uart0StatusReg & txEmpty);
            }

            void put(uint8_t c)
            {
                static Register* const uart0TxBufReg = reinterpret_cast<Register*>(0x400E061C);
                *uart0TxBufReg = c;
            }
        };
}
}
