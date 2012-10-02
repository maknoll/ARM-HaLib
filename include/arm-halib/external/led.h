#pragma once

#include <stdint.h>
#include <arm-halib/arm/register.h>

namespace arm_halib{
namespace external
{
    template<uint8_t led>
    class Led
    {
        public:
        Led()
        {
            static Register* const pioAEnableReg  = reinterpret_cast<Register*>(0x400E0E00);
            static Register* const pioAOutputReg  = reinterpret_cast<Register*>(0x400E0E10);
            static Register* const pioAOutSetReg  = reinterpret_cast<Register*>(0x400E0E30);
            *pioAEnableReg = 1<<led;
            *pioAOutputReg = 1<<led;
            *pioAOutSetReg = 1<<led;
        }

        void toggle()
        {
            static Register* const pioAOutDataReg  = reinterpret_cast<Register*>(0x400E0E38);
            static Register* const pioAOutClearReg = reinterpret_cast<Register*>(0x400E0E34);
            static Register* const pioAOutSetReg   = reinterpret_cast<Register*>(0x400E0E30);
            uint32_t temp= *pioAOutDataReg & (1<<led);
            *pioAOutClearReg = temp;
            *pioAOutSetReg   = (~temp) & (1<<led);
        }
    };
}
}
