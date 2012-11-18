#include <stdint.h>
#include <arm-halib/core/delay.h>
#include <gpio.h>
#include <arm-halib/core/interrupt.h>
#include <uart0.h>

using arm_halib::delay_ms;
using arm_halib::delay_us;
using arm_halib::driver::Gpio;
using arm_halib::driver::Uart0;

#include <logging/logging.h>

using namespace ::logging;

struct LogUart : public Uart0
{
    LogUart& operator<<(char c)
    {
        while(!ready());
        put(c);
        return *this;
    }
};

typedef OutputLevelSwitchDisabled <
            OutputStream<
                LogUart
            > 
        > LogType;

LOGGING_DEFINE_OUTPUT(LogType);

Gpio<5> gpioF(0xe, 0xe, 0x0);
Uart0 uart;

int main() 
{
    enableInterrupts();
    
    uint8_t pwm = 1;

    while(true)
    {
        for(uint8_t i=0;i<8;i++)
        {
            log::emit() << "Hello World" << log::endl;
            for(uint8_t j=0;j<100;j++)
            {
                gpioF.set(i<<1, 0xff);                
                delay_us(pwm*100);
                gpioF.set(i<<1, 0x0);
                delay_us((100-pwm)*100);
            }
        }
    }

    return 0;
}

