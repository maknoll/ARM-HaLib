/**
 *	\file	examples/application/uart.cpp
 *	\brief	Example illustrating usage of Uart
 *
 *	This file is part of avr-halib. See COPYING for copyright details.
 */

#define __ARM_SAM3S4B__

#include <stdint.h>

#define F_CPU F_XTAL * PLL_MUL / PLL_DIV / 2

//#include <arm-halib/arm/uart.h>

//typedef arm_halib::drivers::Uart::configure<>::type Uart;

// LEDs red, yellow, green: PIO A: 19, 18, 17
// PIO:
//     PIO_PER,PDR,PSR = enable pio control of pin: default 1 - offset: 0x0,0x4,0x8
//     PIO_OER,ODR,OSR = enable output(data direction)        - offset: 0x10,0x14,0x18
//     PIO_SODR,CODR,ODSR = set, clear output value           - offset: 0x30,0x34,0x38
//
//     PIOA base: 0x400E0E00

typedef volatile uint32_t Register;

struct SysTick
{
    uint8_t __base[0xE000E010];
    union
    {
        struct
        {
            uint8_t  enable    :  1;
            uint8_t  interrupt :  1;
            uint8_t  source    :  1;
            uint16_t           : 13;
            uint8_t  flag      :  1;
            uint16_t           : 15;
        };
        uint32_t control;
    };
    uint32_t reloadValue;
    uint32_t value;
    union
    {
        struct
        {
            uint32_t tenms : 24;
            uint8_t        : 6;
            uint8_t skew   : 1;
            uint8_t noref  : 1;
        };
        uint32_t calibration;
    };
}  __attribute__((packed));

struct PioA
{
    uint8_t __base[0x400E0E00];
    union
    {
        struct
        {
            uint8_t __pad_control[0x0];
            struct
            {
                uint32_t enable : 32;
                uint32_t disable: 32;
                uint32_t value  : 32;
            } control;
        };
        struct
        {
            uint8_t __pad_direction[0x10];
            struct
            {
                uint32_t output : 32;
                uint32_t input  : 32;
                uint32_t value  : 32;
            } direction;
        };
        struct
        {
            uint8_t __pad_out[0x30];
            struct
            {
                uint32_t high   : 32;
                uint32_t low    : 32;
                uint32_t value  : 32;
            } out;
        };
    };
}  __attribute__((packed));


inline void delay_us(uint16_t value)
{
    SysTick& tick = *reinterpret_cast<SysTick*>(0x0);

    tick.interrupt   = false;
    tick.source      = 1;
    tick.reloadValue = F_CPU/1000000*value;
    tick.enable = 1;
    while(!tick.flag)
        asm("":::"memory");
}

inline void delay_ms(uint16_t value)
{
    SysTick& tick = *reinterpret_cast<SysTick*>(0x0);

    tick.interrupt   = false;
    tick.source      = 1;
    tick.reloadValue = F_CPU/1000*value;
    tick.enable = 1;
    while(!tick.flag)
        asm("":::"memory");
}

static const uint32_t yellowMask = 1<<17;
static const uint32_t greenMask = 1<<18;
static const uint32_t rx    = 1<<9;
static const uint32_t tx    = 1<<10;
static const uint32_t uart0 = 1<<8;
static const uint32_t txEnable = 1<<6;
static const uint32_t noParity = 4<<9;
static const uint32_t txReady = 1<<1;
static const uint32_t txEmpty = 1<<9;

static Register* const pioAEnableReg    = reinterpret_cast<Register*>(0x400E0E00);
static Register* const pioADisableReg   = reinterpret_cast<Register*>(0x400E0E04);
static Register* const pioAOutputReg    = reinterpret_cast<Register*>(0x400E0E10);
static Register* const pioAOutDataReg   = reinterpret_cast<Register*>(0x400E0E38);
static Register* const pioAOutClearReg  = reinterpret_cast<Register*>(0x400E0E34);
static Register* const pioAOutSetReg    = reinterpret_cast<Register*>(0x400E0E30);

static Register* const pmcPeriEnableReg = reinterpret_cast<Register*>(0x400E0410);
static Register* const uart0ControlReg  = reinterpret_cast<Register*>(0x400E0600);

static Register* const uart0ModeReg     = reinterpret_cast<Register*>(0x400E0604);
static Register* const uart0BaudRateReg = reinterpret_cast<Register*>(0x400E0620);
static Register* const uart0StatusReg   = reinterpret_cast<Register*>(0x400E0614);
static Register* const uart0TxBufReg    = reinterpret_cast<Register*>(0x400E061C);

class Led
{
    uint32_t led;
    public:
    Led(uint32_t led) : led(led)
    {
        *pioAEnableReg = led;
        *pioAOutputReg = led;
        *pioAOutSetReg = led;
    }

    void toggle()
    {
        if(*pioAOutDataReg & led)
            *pioAOutClearReg = led;
        else
            *pioAOutSetReg = led;
    }
};

Led yellow(yellowMask);
Led green(greenMask);

static Register* const clkStatusReg = reinterpret_cast<Register*>(0x400E0468);
static const uint32_t xtalStable = 1<<0;

int main() 
{
    *pmcPeriEnableReg = uart0;
    *pioADisableReg   = rx | tx;
    *uart0ControlReg  = txEnable;
    *uart0ModeReg     = noParity;
    *uart0BaudRateReg = F_CPU / 16 / 19200;

    if(*clkStatusReg & xtalStable)
        yellow.toggle();

    while(true)
    {
        *uart0TxBufReg = 'A';
        while(!(*uart0StatusReg & txEmpty));
        green.toggle();
        delay_ms(1000);
    }

    return 0;
}

