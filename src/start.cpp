#include <stdint.h>
#include <arm-halib/core/register.h>
#include <arm-halib/driver/sysTickTimerDef.h>

using arm_halib::Register;
using arm_halib::driver::SysTickTimer;

typedef void* StackPtr;

typedef void(*InitFunc)(void);
typedef void(*FiniFunc)(void);

extern "C"
{
    extern uint8_t __end;
    extern uint8_t __text_end;
    extern uint32_t __data_start;
    extern uint32_t __data_end;
    extern uint32_t __data_load_start;
    extern uint32_t __data_load_end;
    extern uint32_t __bss_start;
    extern uint32_t __bss_end;
    extern uint8_t __start;
    extern void* __init_array_start;
    extern void* __init_array_end;
    extern void* __fini_array_start;
    extern void* __fini_array_end;
    extern int main(void);
}

inline void frameSetup(void)        __attribute__((always_inline));
void hwInit(void);
inline void sysTickSetup(void)      __attribute__((always_inline));
inline void copyData(void)          __attribute__((always_inline));
inline void clearBSS(void)          __attribute__((always_inline));
inline void initArray(void)         __attribute__((always_inline));
inline void enterMain(void)         __attribute__((always_inline));
inline void finiArray(void)         __attribute__((always_inline));
inline void disableInterrupts(void) __attribute__((always_inline));
inline void enableInterrupts(void) __attribute__((always_inline));
inline void loop(void)              __attribute__((always_inline));

void frameSetup(void)
{
    asm volatile("mov r7,sp");
}

void copyData(void)
{
    uint32_t* srcPtr=&__data_start;
    uint32_t* dstPtr=&__data_load_start;
    while(srcPtr<&__data_end)
        *srcPtr++ = *dstPtr++;
}

void clearBSS(void)
{
    uint32_t *ptr=&__bss_start;
    while(ptr<&__bss_end)
        *ptr++ = 0;  
}
void initArray(void)
{
    for(void **ptr = &__init_array_start;
               ptr < &__init_array_end;
               ptr++
       )
        ((InitFunc)*ptr)();

}
void enterMain(void)
{
    main();
}

void finiArray(void)
{
    for(void **ptr = &__fini_array_start;
               ptr < &__fini_array_end;
               ptr++
        )
        ((FiniFunc)*ptr)();

}
void disableInterrupts(void)
{
    asm volatile ("cpsid f");
}
void enableInterrupts(void)
{
    asm volatile ("cpsie f");
}
void loop(void)
{
    while(1);
}

extern "C" void init(void) __attribute__((section(".init"),naked));
void init()
{
    disableInterrupts();
    frameSetup();
    copyData();
    clearBSS();
    initArray();
    hwInit();
    SysTickTimer::init();
    enableInterrupts();
    enterMain();
    finiArray();
    disableInterrupts();
    loop();
}

StackPtr tos __attribute__((section(".tos"))) = (StackPtr)&__end;
