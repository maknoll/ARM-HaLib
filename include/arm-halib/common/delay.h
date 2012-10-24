#pragma once

#include <stdint.h>
#include <arm-halib/arm/register.h>
#include <arm-halib/arm/fcpu.h>
#include <arm-halib/arm/locking.h>

extern "C" volatile uint32_t sysTickHigh;

namespace arm_halib{
namespace driver
{
    struct SysTickTimer
    {
        static uint64_t time()
        {
            GlobalInterruptLock lock;
            static Register* const valueReg = reinterpret_cast<Register*>(0xE000E018);
            uint64_t now = sysTickHigh;
            now <<=24;
            now |= *valueReg;
            return now;
        }
    };
}

namespace common
{
    inline void delay_us(uint16_t value) 
    { 
        uint64_t then = driver::SysTickTimer::time() -F_CPU/1000000/8*value;
        while(driver::SysTickTimer::time() > then);
    }

    inline void delay_ms(uint16_t value)
    {
        uint64_t then = driver::SysTickTimer::time() -F_CPU/1000/8*value;
        while(driver::SysTickTimer::time() > then);
    }
}
}
