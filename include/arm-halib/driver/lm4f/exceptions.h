typedef void(*VecFunc)(void);

extern "C"
{
    void NMI_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void HardFault_Handler(void)  __attribute__ ((weak, alias("badInterrupt")));
    void MemManage_Handler(void)  __attribute__ ((weak, alias("badInterrupt")));
    void BusFault_Handler(void)   __attribute__ ((weak, alias("badInterrupt")));
    void UsageFault_Handler(void) __attribute__ ((weak, alias("badInterrupt")));
    void SVC_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void DebugMon_Handler(void)   __attribute__ ((weak, alias("badInterrupt")));
    void PendSV_Handler(void)     __attribute__ ((weak, alias("badInterrupt")));
}
