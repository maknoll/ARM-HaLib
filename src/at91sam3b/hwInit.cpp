#include <stdint.h>
#include <arm-halib/core/register.h>

using arm_halib::Register;

void watchdogDisable(void)
{
    static const uint32_t wdtDis = 1<<15;
    static Register* const wdtMr = reinterpret_cast<Register*>(0x400E1454);
    *wdtMr = wdtDis;
}

void clockSetup(void)
{
    static Register* const eefcModeReg  = reinterpret_cast<Register*>(0x400E0A00);
    static Register* const pmcMorReg    = reinterpret_cast<Register*>(0x400E0420);
    static Register* const pmcMckrReg   = reinterpret_cast<Register*>(0x400E0430);
    static Register* const pmcPllAReg   = reinterpret_cast<Register*>(0x400E0428);
    static Register* const pmcSrReg     = reinterpret_cast<Register*>(0x400E0468);
    static const uint32_t cssMask       = 0x3 << 0;
    static const uint32_t cssMain       = 0x1 << 0;
    static const uint32_t cssPllA       = 0x2 << 0;
    static const uint32_t pres2         = PRES_EXP << 4;
    static const uint32_t masterReady   = 0x1 << 3;
    static const uint32_t lockA         = 0x1 << 1;
    static const uint32_t pllOne        = 0x1 << 29;
    static const uint8_t  pllMulShift   = 16;
    static const uint32_t pllMulMask    = 0x7ff << pllMulShift;
    static const uint8_t  pllCountShift = 8;
    static const uint32_t pllCountMask  = 0x3f << pllCountShift;
    static const uint8_t  pllDivShift   = 0;
    static const uint32_t pllDivMask    = 0xff << pllDivShift;
    static const uint8_t  xtalWaitShift = 8;
    static const uint32_t selectXtal    = 1<<24;
    static const uint32_t xtalStable    = 1<<0;
    static const uint32_t rcStable      = 1<<1;
    static const uint32_t enableXtal    = 1<<0;
    static const uint32_t enableRC      = 1<<3;
    static const uint32_t key           = 0x37<<16;
    static const uint32_t selInProgress = 1<<16;
    static const uint32_t rc12MHz       = 0x2<<4;

    *eefcModeReg = 1<<8;

    uint32_t timeout;

    static const uint32_t pllConfig    = pllOne | ((PLL_MUL-1) << pllMulShift) | (1 << pllCountShift) | (PLL_DIV << pllDivShift);
    static const uint32_t masterConfig = pres2 | cssPllA;
    static const uint32_t xtalWaitCount = 8 << xtalWaitShift;

    *pmcMorReg = key | enableRC | enableXtal | xtalWaitCount;
    timeout=0;
    while (!(*pmcSrReg & xtalStable) & timeout++<=0xFFFFFFFF);

    *pmcMorReg = key | xtalWaitCount | enableRC | enableXtal | selectXtal;
    timeout=0;
    while (!(*pmcSrReg & selInProgress) & timeout++<=0xFFFFFFFF);

    *pmcPllAReg = pllConfig;
    timeout=0;
    while(!(*pmcSrReg & lockA) & timeout++<=0xFFFFFFFF);

    *pmcMckrReg = (masterConfig & ~cssMask) | cssMain;
    timeout=0;
    while(!(*pmcSrReg & masterReady) & timeout++<=0xFFFFFFFF);
    
    *pmcMckrReg = masterConfig;
    timeout=0;
    while(!(*pmcSrReg & masterReady) & timeout++<=0xFFFFFFFF);
    
}
