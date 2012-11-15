#include <stdint.h>
#include <arm-halib/core/register.h>
#include <arm-halib/core/delay.h>
//#include <gpio.h>

using arm_halib::Register;
using arm_halib::delay_ms;
using arm_halib::delay_us;
//using arm_halib::driver::GpioF;

/*#include <arm-halib/arm/uart.h>



#include <logging/logging.h>

using namespace ::logging;
using namespace ::arm_halib;
using external::Led;
using driver::Uart0;


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


Led<17> yellow;
Led<18> green;
*/
int main() 
{
/*    static const uint32_t xtalStable = 1<<0;
    static Register* const clkStatusReg = reinterpret_cast<Register*>(0x400E0468);
    if(*clkStatusReg & xtalStable)
        yellow.toggle();
*/
    Register* gpioClock = (Register*)0x400FE608;
    Register* gpioHP = (Register*)0x400FE06C;
    *gpioHP    = 0xff;
    *gpioClock = 0xff;
    delay_us(1);
    Register* gpioFData = (Register*)(0x4005D000);
    Register* gpioFDir  = (Register*)0x4005D400;
    Register* gpioFDigEn= (Register*)0x4005D51C;
    
    *gpioFDir = 0xe;
    *gpioFDigEn= 0xe;
    
    uint8_t pwm = 1;

    while(true)
    {
        for(uint8_t i=0;i<8;i++)
        {
            for(uint8_t j=0;j<100;j++)
            {
                gpioFData[0xe] = i<<1;
                delay_us(pwm*100);
                gpioFData[0xe] = 0;
                delay_us((100-pwm)*100);
            }
        }
    }

    return 0;
}

