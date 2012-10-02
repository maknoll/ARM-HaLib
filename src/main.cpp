#include <stdint.h>
#include <arm-halib/arm/uart.h>
#include <arm-halib/external/led.h>
#include <arm-halib/common/delay.h>

using namespace ::arm_halib;
using external::Led;
using driver::Uart0;
using common::delay_ms;

Led<17> yellow;
Led<18> green;
Uart0 uart;

int main() 
{
    static const uint32_t xtalStable = 1<<0;
    static Register* const clkStatusReg = reinterpret_cast<Register*>(0x400E0468);
    if(*clkStatusReg & xtalStable)
        yellow.toggle();

    while(true)
    {
        uart.put('A');
        while(!uart.ready());
        green.toggle();
        delay_ms(1000);
    }

    return 0;
}

