#pragma once

#include <stdint.h>
#include <arm-halib/driver/sysTickTimer.h>
#include "fcpu.h"

namespace arm_halib
{
    inline void delay_us(uint16_t value) 
    { 
        uint64_t then = driver::SysTickTimer::time() -F_CPU/1000000/4*value;
        while(driver::SysTickTimer::time() > then);
    }

    inline void delay_ms(uint16_t value)
    {
        uint64_t then = driver::SysTickTimer::time() -F_CPU/1000/4*value;
        while(driver::SysTickTimer::time() > then);
    }
}
