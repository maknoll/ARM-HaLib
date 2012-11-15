#include <arm-halib/driver/sysTickTimerDef.h>

using arm_halib::driver::SysTickTimer;

typedef void(*VecFunc)(void);

extern "C"
{
    void badInterrupt()
    {
	    while(true);
    }

    extern void init();

    void NMI_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void HardFault_Handler(void)  __attribute__ ((weak, alias("badInterrupt")));
    void MemManage_Handler(void)  __attribute__ ((weak, alias("badInterrupt")));
    void BusFault_Handler(void)   __attribute__ ((weak, alias("badInterrupt")));
    void UsageFault_Handler(void) __attribute__ ((weak, alias("badInterrupt")));
    void SVC_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void DebugMon_Handler(void)   __attribute__ ((weak, alias("badInterrupt")));
    void PendSV_Handler(void)     __attribute__ ((weak, alias("badInterrupt")));

    VecFunc exceptions[] __attribute__((section(".vectors")))=
    {
	init,
	NMI_Handler,
	HardFault_Handler,
	MemManage_Handler,
	BusFault_Handler,
	UsageFault_Handler,
	0,0,0,0,
	SVC_Handler,
	DebugMon_Handler,
	0,
	PendSV_Handler,
	SysTickTimer::tick

    };
}
