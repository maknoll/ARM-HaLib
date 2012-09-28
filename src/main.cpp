#include <stdint.h>

#define F_CPU F_XTAL * PLL_MUL / PLL_DIV / 2

typedef volatile uint32_t Register;

struct SysTickTimer
{
    void wait(uint32_t value)
    {
        static const uint32_t enable     = 1<<0;
        static const uint32_t intEnable  = 1<<1;
        static const uint32_t notClkDiv8 = 1<<2;
        static const uint32_t zeroFlag   = 1<<16;
        static Register* const ctrlReg   = reinterpret_cast<Register*>(0xE000E010);
        static Register* const reloadReg = reinterpret_cast<Register*>(0xE000E014);
        
        *reloadReg = value;
        *ctrlReg   = enable | notClkDiv8;
        while(!(*ctrlReg & zeroFlag));
        *ctrlReg   = !enable;
    }
};

template<uint8_t led>
class Led
{
    public:
    Led()
    {
        static Register* const pioAEnableReg  = reinterpret_cast<Register*>(0x400E0E00);
        static Register* const pioAOutputReg  = reinterpret_cast<Register*>(0x400E0E10);
        static Register* const pioAOutSetReg  = reinterpret_cast<Register*>(0x400E0E30);
        *pioAEnableReg = 1<<led;
        *pioAOutputReg = 1<<led;
        *pioAOutSetReg = 1<<led;
    }

    void toggle()
    {
        static Register* const pioAOutDataReg  = reinterpret_cast<Register*>(0x400E0E38);
        static Register* const pioAOutClearReg = reinterpret_cast<Register*>(0x400E0E34);
        static Register* const pioAOutSetReg   = reinterpret_cast<Register*>(0x400E0E30);
        uint32_t temp= *pioAOutDataReg & (1<<led);
        *pioAOutClearReg = temp;
        *pioAOutSetReg   = (~temp) & (1<<led);
    }
};

struct Uart0
{
    Uart0()
    {
        static const uint32_t rx0      = 1<<9;
        static const uint32_t tx0      = 1<<10;
        static const uint32_t uart0    = 1<<8;
        static const uint32_t txEnable = 1<<6;
        static const uint32_t noParity = 4<<9;
        static Register* const pioADisableReg = reinterpret_cast<Register*>(0x400E0E04);
        static Register* const pmcPeriEnableReg = reinterpret_cast<Register*>(0x400E0410);
        static Register* const uart0ControlReg  = reinterpret_cast<Register*>(0x400E0600);
        static Register* const uart0ModeReg     = reinterpret_cast<Register*>(0x400E0604);
        static Register* const uart0BaudRateReg  = reinterpret_cast<Register*>(0x400E0620);

        *pmcPeriEnableReg = uart0;
        *pioADisableReg   = rx0 | tx0;
        *uart0ControlReg  = txEnable;
        *uart0ModeReg     = noParity;
        *uart0BaudRateReg = F_CPU / 16 / 19200;
    }
    
    bool ready() const
    {
        static const uint32_t txEmpty  = 1<<9;
        static Register* const uart0StatusReg = reinterpret_cast<Register*>(0x400E0614);
        return (*uart0StatusReg & txEmpty);
    }

    void put(uint8_t c)
    {
        static Register* const uart0TxBufReg = reinterpret_cast<Register*>(0x400E061C);
        *uart0TxBufReg = c;
    }
};

inline void delay_us(uint16_t value)
{
    SysTickTimer().wait(F_CPU/1000000*value);
}

inline void delay_ms(uint16_t value)
{
    SysTickTimer().wait(F_CPU/1000*value);
}

Led<17> yellow;
Led<18> green;
Uart0   uart;

int main() 
{
    static const uint32_t xtalStable = 1<<0;
    static Register* const clkStatusReg = reinterpret_cast<Register*>(0x400E0468);
    if(*clkStatusReg & xtalStable)
        yellow.toggle();

    while(true)
    {
        uart.put('A');
        while(!uart.ready());
        green.toggle();
        delay_ms(1000);
    }

    return 0;
}

