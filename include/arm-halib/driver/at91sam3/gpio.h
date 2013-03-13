#pragma once

#include <stdint.h>
#include <arm-halib/core/register.h>

namespace arm_halib{
namespace driver
{
    template<uint8_t bit>
    class GpioF
    {
        public:
        GpioF()
        {
            static Register* const pioAEnableReg  = reinterpret_cast<Register*>(0x400E0E00);
            static Register* const pioAOutputReg  = reinterpret_cast<Register*>(0x400E0E10);
            static Register* const pioAOutSetReg  = reinterpret_cast<Register*>(0x400E0E30);
            *pioAEnableReg = 1<<bit;
            *pioAOutputReg = 1<<bit;
            *pioAOutSetReg = 1<<bit;
        }

        void toggle()
        {
            static Register* const pioAOutDataReg  = reinterpret_cast<Register*>(0x400E0E38);
            static Register* const pioAOutClearReg = reinterpret_cast<Register*>(0x400E0E34);
            static Register* const pioAOutSetReg   = reinterpret_cast<Register*>(0x400E0E30);
            uint32_t temp= *pioAOutDataReg & (1<<bit);
            *pioAOutClearReg = temp;
            *pioAOutSetReg   = (~temp) & (1<<bit);
        }
    };
}
}
