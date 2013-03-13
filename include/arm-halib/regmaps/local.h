#pragma once

#include "regmaps.h"

#if defined(__ARM_AT91SAM3S4B__)
	#include "local/at91sam3s4b.h"
#elif defined(__ARM_LM4F__)
  #include "local/lm4f.h"
#else
	#error "MCU not supported yet"
#endif
