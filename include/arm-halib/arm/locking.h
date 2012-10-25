#pragma once

#include <stdint.h>

namespace arm_halib{
namespace driver
{
    struct GlobalInterruptLock
    {
        private:
            uint32_t faultmask;

        public:
            GlobalInterruptLock()
            {
                asm volatile("mrs %0, FAULTMASK\n\t"
                             "cpsid f"
                             : "=r"(faultmask)
                        );
            }

            ~GlobalInterruptLock()
            {
                asm volatile("msr FAULTMASK, %0"
                             :
                             : "r"(faultmask)
                        );
            }
    };
}
}
