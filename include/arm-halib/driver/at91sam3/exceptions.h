#pragma once

#include <arm-halib/driver/sysTickTimerDef.h>

namespace arm_halib{
namespace driver
{

    typedef void(*InterruptFunc)(void);

    extern "C" void badInterrupt()
    {
        while(1);
    }

    extern "C" void init();
    extern "C" void sysTick();

    void NMI_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void HardFault_Handler(void)  __attribute__ ((weak, alias("badInterrupt")));
    void MemManage_Handler(void)  __attribute__ ((weak, alias("badInterrupt")));
    void BusFault_Handler(void)   __attribute__ ((weak, alias("badInterrupt")));
    void UsageFault_Handler(void) __attribute__ ((weak, alias("badInterrupt")));
    void SVC_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void DebugMon_Handler(void)   __attribute__ ((weak, alias("badInterrupt")));
    void PendSV_Handler(void)     __attribute__ ((weak, alias("badInterrupt")));
    void ACC_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void ADC_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void CRCCU_Handler(void)      __attribute__ ((weak, alias("badInterrupt")));
    void DACC_Handler(void)       __attribute__ ((weak, alias("badInterrupt")));
    void EFC_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void HSMCI_Handler(void)      __attribute__ ((weak, alias("badInterrupt")));
    void PIOA_Handler(void)       __attribute__ ((weak, alias("badInterrupt")));
    void PIOB_Handler(void)       __attribute__ ((weak, alias("badInterrupt")));
    void PIOC_Handler(void)       __attribute__ ((weak, alias("badInterrupt")));
    void PMC_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void PWM_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void RSTC_Handler(void)       __attribute__ ((weak, alias("badInterrupt")));
    void RTC_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void RTT_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void SMC_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void SPI_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void SSC_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void SUPC_Handler(void)       __attribute__ ((weak, alias("badInterrupt")));
    void TC0_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void TC1_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void TC2_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void TC3_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void TC4_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void TC5_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void TWI0_Handler(void)       __attribute__ ((weak, alias("badInterrupt")));
    void TWI1_Handler(void)       __attribute__ ((weak, alias("badInterrupt")));
    void UART0_Handler(void)      __attribute__ ((weak, alias("badInterrupt")));
    void UART1_Handler(void)      __attribute__ ((weak, alias("badInterrupt")));
    void USART0_Handler(void)     __attribute__ ((weak, alias("badInterrupt")));
    void USART1_Handler(void)     __attribute__ ((weak, alias("badInterrupt")));
    void UDP_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void WDT_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));

    InterruptFunc exceptionHandlers[] __attribute__ ((section(".vectors"))) = {
        init,
        NMI_Handler,
        HardFault_Handler,
        MemManage_Handler,
        BusFault_Handler,
        UsageFault_Handler,
        SVC_Handler,
        DebugMon_Handler,
        PendSV_Handler,
        SysTickTimer::tick,
        ACC_Handler,
        ADC_Handler,
        CRCCU_Handler,
        DACC_Handler,
        EFC_Handler,
        HSMCI_Handler,
        PIOA_Handler,
        PIOB_Handler,
        PIOC_Handler,
        PMC_Handler,
        PWM_Handler,
        RSTC_Handler,
        RTC_Handler,
        RTT_Handler,
        SMC_Handler,
        SPI_Handler,
        SSC_Handler,
        SUPC_Handler,
        TC0_Handler,
        TC1_Handler,
        TC2_Handler,
        TC3_Handler,
        TC4_Handler,
        TC5_Handler,
        TWI0_Handler,
        TWI1_Handler,
        UART0_Handler,
        UART1_Handler,
        USART0_Handler,
        USART1_Handler,
        UDP_Handler,
        WDT_Handler,
    };

}
}
