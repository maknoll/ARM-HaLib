#include <stdint.h>
#include <arm-halib/arm/register.h>
#include <arm-halib/common/delay.h>
#include <arm-halib/external/led.h>

using arm_halib::Register;
using arm_halib::common::delay_ms;
using arm_halib::common::delay_us;
using arm_halib::external::Led;

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
//    delay_us(1);
    asm volatile ("nop");
    asm volatile ("nop");
    asm volatile ("nop");
    asm volatile ("nop");
    asm volatile ("nop");
    Register* gpioFData = (Register*)(0x4005D000);
    Register* gpioFDir  = (Register*)0x4005D400;
    Register* gpioFDigEn= (Register*)0x4005D51C;
    
    *gpioFDir = 0xff;
    *gpioFDigEn= 0xff;
    gpioFData[0xFF] = 0xff;
    
//    unsigned int i=0;
    while(true)
    {
        
//        log::emit() << "Toggle Led: " << i++ << log::endl;
//        green.toggle();*/
        delay_ms(1000);
        gpioFData[0xFF] = 0x0;
        delay_ms(1000);
        gpioFData[0xFF] = 0xffffffff;
    }

    return 0;
}

