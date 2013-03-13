#pragma once

#include <stdint.h>

namespace arm_halib{
namespace driver
{
    struct SysTickTimer
    {
        private:
            static volatile uint32_t sysTickHigh;

        public:
            static void init();
            static void tick();
            static inline uint64_t time();
    };
}
}
