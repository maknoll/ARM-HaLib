#include <platform.h>

#include <stdint.h>
#include <arm-halib/core/delay.h>

using arm_halib::delay_ms;

static const uint16_t redMin   = 10;
static const uint16_t blueMin  = 10;
static const uint16_t greenMin = 10;

static const uint16_t redMax   = 900;
static const uint16_t blueMax  = 900;
static const uint16_t greenMax = 900;

static const uint16_t redInit   = redMin;
static const uint16_t blueInit  = blueMin;
static const uint16_t greenInit = greenMin;

int main() 
{
    log::emit() << "PWM Test" <<  log::endl;

    platform::RedLed red;
    platform::BlueLed blue;
    platform::GreenLed green;

    red.dutyCycle(1000);
    blue.dutyCycle(1000);
    green.dutyCycle(1000);

    red.value(redInit);
    blue.value(blueInit);
    green.value(greenInit);

    red.enable();
    blue.enable();
    green.enable();

    int redMod = 1;
    int blueMod = 1;
    int greenMod = 1;

    while(true)
    {   
        red.value  ( red.value()   + redMod   );
        blue.value ( blue.value()  + blueMod  );
        green.value( green.value() + greenMod );

        log::emit() << "red  : "   << red.value()   << log::endl;
        log::emit() << "green: " << green.value() << log::endl;
        log::emit() << "blue : "  << blue.value()  << log::endl;

        if(red.value()>=redMax)
                redMod=-1;

        if(red.value()<=redMin)
                redMod=1;

        if(blue.value()>=blueMax)
                blueMod=-1;

        if(blue.value()<=blueMin)
                blueMod=1;

        if(green.value()>=greenMax)
                greenMod=-1;

        if(green.value()<=greenMin)
                greenMod=1;

        delay_ms(10);
    }
    return 0;
}

