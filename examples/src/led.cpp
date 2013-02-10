#include <platform.h>

#include <stdint.h>
#include <arm-halib/core/delay.h>

using arm_halib::delay_ms;

typedef uint16_t ColorType;
static const ColorType max=1000; 

int main() 
{
    log::emit() << "PWM Test" <<  log::endl;

    platform::RedLed red;
    platform::BlueLed blue;
    platform::GreenLed green;

    red.dutyCycle(max);
    blue.dutyCycle(max);
    green.dutyCycle(max);

    red.value(0);
    blue.value(0);
    green.value(0);

    red.enable();
    blue.enable();
    green.enable();

    while(true)
    {   
        for(ColorType i=0;i<max;i++)
        {
            red.value(i);
            log::emit() << "red  : "   << red.value()   << log::endl;
            delay_ms(10);
        }
        red.value(0);

        for(ColorType i=0;i<max;i++)
        {
            blue.value(i);
            log::emit() << "blue : "  << blue.value()  << log::endl;
            delay_ms(10);
        }
        blue.value(0);

        for(ColorType i=0;i<max;i++)
        {
            green.value(i);
            log::emit() << "green: " << green.value() << log::endl;
            delay_ms(10);
        }
        green.value(0);    
    }
    return 0;
}

