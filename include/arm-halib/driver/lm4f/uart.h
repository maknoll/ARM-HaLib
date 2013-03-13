#pragma once

#include <stdint.h>
#include <arm-halib/core/register.h>
#include <arm-halib/core/fcpu.h>

namespace arm_halib{
namespace driver{
namespace lm4f
{
        struct Uart0
        {
            Uart0()
            {
            }
            
            bool ready() const
            {
                return true;
            }

            void put(uint8_t c)
            {
            }
        };
}
}
}
