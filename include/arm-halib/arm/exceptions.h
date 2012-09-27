typedef void(*VecFunc)(void);

extern "C"
{
    void badInterrupt(void)
    {
        *(volatile uint32_t*)0x400E0E00 = 0x1<< 19;
        *(volatile uint32_t*)0x400E0E10 = 0x1<< 19;
        *(volatile uint32_t*)0x400E0E30 = 0x1<< 19;
        while(1);
    }

    void NMI_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void HardFault_Handler(void)  __attribute__ ((weak, alias("badInterrupt")));
    void MemManage_Handler(void)  __attribute__ ((weak, alias("badInterrupt")));
    void BusFault_Handler(void)   __attribute__ ((weak, alias("badInterrupt")));
    void UsageFault_Handler(void) __attribute__ ((weak, alias("badInterrupt")));
    void SVC_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void DebugMon_Handler(void)   __attribute__ ((weak, alias("badInterrupt")));
    void PendSV_Handler(void)     __attribute__ ((weak, alias("badInterrupt")));
    void SysTick_Handler(void)    __attribute__ ((weak, alias("badInterrupt")));
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
}
