#pragma once

void disableInterrupts(void)
{
    asm volatile ("cpsid f");
}

void enableInterrupts(void)
{
    asm volatile ("cpsie f");
}
