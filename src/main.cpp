/**
 *	\file	examples/application/uart.cpp
 *	\brief	Example illustrating usage of Uart
 *
 *	This file is part of avr-halib. See COPYING for copyright details.
 */

#define __ARM_SAM3S4B__

#include "arm-halib/arm/uart.h"

struct Config : public arm_halib::drivers::Uart::DefaultConfig
{
    typedef arm_halib::regmaps::local::Uart0 RegMap;
};

typedef arm_halib::drivers::Uart::configure<Config>::type Uart;

Uart uart;

int main() {
    uint8_t c;
	while(true){
        if(uart.get(c)){
            uart.put('\n');
            uart.put(c);
        }
	}
    return 0;
}

