#pragma once

#include "regmaps.h"

#if defined(__ARM_SAM3S4B__)
	#include "local/sam3s4b.h"
#else
	#error "MCU not supported yet"
#endif
