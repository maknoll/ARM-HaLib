#include <arm-halib/driver/sysTickTimerDef.h>

using arm_halib::driver::SysTickTimer;

typedef void(*VecFunc)(void);

extern "C"
{
    void badInterrupt()
    {
	    while(true);
    }

    extern void init(void);

    void NMI_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void HardFault_Handler(void)  __attribute__ ((weak, alias("badInterrupt")));
    void MemManage_Handler(void)  __attribute__ ((weak, alias("badInterrupt")));
    void BusFault_Handler(void)   __attribute__ ((weak, alias("badInterrupt")));
    void UsageFault_Handler(void) __attribute__ ((weak, alias("badInterrupt")));
    void SVC_Handler(void)        __attribute__ ((weak, alias("badInterrupt")));
    void DebugMon_Handler(void)   __attribute__ ((weak, alias("badInterrupt")));
    void PendSV_Handler(void)     __attribute__ ((weak, alias("badInterrupt")));

    void GPIOA_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void GPIOB_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void GPIOC_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void GPIOD_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void GPIOE_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void GPIOF_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void UART0_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void UART1_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void UART2_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void UART3_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void UART4_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void UART5_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void UART6_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void UART7_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void SSI0_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void SSI1_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void SSI2_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void SSI3_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void I2C0_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void I2C1_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void I2C2_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void I2C3_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void ADC0Seq0_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void ADC0Seq1_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void ADC0Seq2_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void ADC0Seq3_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void ADC1Seq0_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void ADC1Seq1_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void ADC1Seq2_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void ADC1Seq3_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Timer32A0_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Timer32B0_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Timer32A1_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Timer32B1_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Timer32A2_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Timer32B2_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Timer32A3_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Timer32B3_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Timer32A4_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Timer32B4_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Timer32A5_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Timer32B5_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Timer64A0_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Timer64B0_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Timer64A1_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Timer64B1_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Timer64A2_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Timer64B2_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Timer64A3_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Timer64B3_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Timer64A4_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Timer64B4_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Timer64A5_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Timer64B5_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void AComp0_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Acomp1_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void CAN0_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void USB_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void UDMASoft_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void UDMAHard_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void SysControl_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void SysExcept_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void WatchDogs_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void FlashEEPROM_Handler(void) __attribute__((weak,alias("badInterrupt")));
    void Hibernate_Handler(void) __attribute__((weak,alias("badInterrupt")));


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
	SysTickTimer::tick,
    GPIOA_Handler,
    GPIOB_Handler,
    GPIOC_Handler,
    GPIOD_Handler,
    GPIOE_Handler,
    UART0_Handler,
    UART1_Handler,
    SSI0_Handler,
    I2C0_Handler,
    0,0,0,0,0,
    ADC0Seq0_Handler,
    ADC0Seq1_Handler,
    ADC0Seq2_Handler,
    ADC0Seq3_Handler,
    WatchDogs_Handler,
    Timer32A0_Handler,
    Timer32B0_Handler,
    Timer32A1_Handler,
    Timer32B1_Handler,
    Timer32A2_Handler,
    Timer32B2_Handler,
    AComp0_Handler,
    Acomp1_Handler,
    0,
    SysControl_Handler,
    FlashEEPROM_Handler,
    GPIOF_Handler,
    0,0,
    UART2_Handler,
    SSI1_Handler,
    Timer32A3_Handler,
    Timer32B3_Handler,
    I2C1_Handler,
    0,
    CAN0_Handler,
    0,0,0,
    Hibernate_Handler,
    USB_Handler,
    0,
    UDMASoft_Handler,
    UDMAHard_Handler,
    ADC1Seq0_Handler,
    ADC1Seq1_Handler,
    ADC1Seq2_Handler,
    ADC1Seq3_Handler,
    0,0,0,0,0,
    SSI2_Handler,
    SSI3_Handler,
    UART3_Handler,
    UART4_Handler,
    UART5_Handler,
    UART6_Handler,
    UART7_Handler,
    0,0,0,0,
    I2C2_Handler,
    I2C3_Handler,
    Timer32A4_Handler,
    Timer32B4_Handler,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    Timer32A5_Handler,
    Timer32B5_Handler,
    Timer64A0_Handler,
    Timer64B0_Handler,
    Timer64A1_Handler,
    Timer64B1_Handler,
    Timer64A2_Handler,
    Timer64B2_Handler,
    Timer64A3_Handler,
    Timer64B3_Handler,
    Timer64A4_Handler,
    Timer64B4_Handler,
    Timer64A5_Handler,
    Timer64B5_Handler,
    SysExcept_Handler,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    };
}
