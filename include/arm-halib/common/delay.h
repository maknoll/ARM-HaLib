#pragma once

#include <stdint.h>
#include <arm-halib/arm/register.h>
#include <arm-halib/arm/fcpu.h>

namespace arm_halib{
namespace driver
{
    struct SysTickTimer
    {
        static void wait(uint32_t value)
        {
            static const uint32_t enable     = 1<<0;
            static const uint32_t intEnable  = 1<<1;
            static const uint32_t notClkDiv8 = 1<<2;
            static const uint32_t zeroFlag   = 1<<16;
            static Register* const ctrlReg   = reinterpret_cast<Register*>(0xE000E010);
            static Register* const reloadReg = reinterpret_cast<Register*>(0xE000E014);
            
            *reloadReg = value;
            *ctrlReg   = enable | notClkDiv8;
            while(!(*ctrlReg & zeroFlag));
            *ctrlReg   = !enable;
        }
    };
}

namespace common
{
    inline void delay_us(uint16_t value)
    {
        driver::SysTickTimer::wait(F_CPU/1000000*value);
    }

    inline void delay_ms(uint16_t value)
    {
        driver::SysTickTimer::wait(F_CPU/1000*value);
    }
}
}
