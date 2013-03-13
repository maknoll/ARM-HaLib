PLATFORM_DIR       := $(dir $(lastword ${MAKEFILE_LIST}))

PLL_MULTIPLICATOR  := 124
PLL_DIVISOR        := 24
PRESCALER_EXPONENT := 1
CRYSTAL_FREQUENCY  := 18432000ULL

PLATFORM_LIB       := ${HALIB_LIB_DIR}/lib${PLATFORM}.a
PLATFORM_INCLUDES  := ${HALIB_DIR}/include/arm-halib/driver/at91sam3 ${PLATFORM_DIR}/include

LDPATHS            += ${HALIB_LIB_DIR}
LIBS               += ${PLATFORM}

INCLUDE            := ${PLATFORM_DIR}/include

PLATFORM_ASFLAGS   := -mcpu=cortex-m3                   \
		              -mthumb                           \
			          -D PLL_MUL=${PLL_MULTIPLICATOR}   \
		              -D PLL_DIV=${PLL_DIVISOR}         \
			          -D PRES_EXP=${PRESCALER_EXPONENT} \
		              -D F_XTAL=${CRYSTAL_FREQUENCY}

PLATFORM_CFLAGS    := ${PLATFORM_ASFLAGS}

PLATFORM_CXXFLAGS  := ${PLATFORM_ASFLAGS}

PLATFORM_LDFLAGS   := -T ${PLATFORM_DIR}/link.ld

include ${PLATFORM_DIR}/flash.mk
include ${PLATFORM_DIR}/debug.mk
