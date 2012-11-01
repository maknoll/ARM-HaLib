#pragma once

#include "regmaps.h"

#if defined(__ARM_AT91SAM3S4B__)
	#include "local/at91sam3s4b.h"
#else
	#error "MCU not supported yet"
#endif
