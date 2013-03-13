#pragma once

#include <stdint.h>
#include "sysTickTimerDef.h"
#include <arm-halib/core/register.h>
#include <arm-halib/core/locking.h>

namespace arm_halib{
namespace driver
{
    void SysTickTimer::init()
    {
        static Register* const ctrlReg   = reinterpret_cast<Register*>(0xE000E010);
        static Register* const reloadReg = reinterpret_cast<Register*>(0xE000E014);
        static const uint32_t enable    = 0x1 << 0;
        static const uint32_t interrupt = 0x1 << 1;
        //static const uint32_t useSystemClock = 0x1 << 2;
        *reloadReg  = 0xFFFFFF;
        sysTickHigh = 0xFFFFFFFF;
        *ctrlReg    = enable | interrupt;// | useSystemClock;
    }

    void SysTickTimer::tick()
    {
        sysTickHigh--;
    }

    uint64_t SysTickTimer::time()
    {
        core::GlobalInterruptLock lock;
        static Register* const valueReg = reinterpret_cast<Register*>(0xE000E018);
        uint64_t now = sysTickHigh;
        now <<=24;
        now |= *valueReg;
        return now;
    }

    volatile uint32_t SysTickTimer::sysTickHigh;
}
}
