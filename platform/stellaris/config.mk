PLATFORM_DIR       := $(dir $(lastword ${MAKEFILE_LIST}))

PLL_MULTIPLICATOR  := 1
PLL_DIVISOR        := 1
PRESCALER_EXPONENT := 0
CRYSTAL_FREQUENCY  := 16000000ULL

PLATFORM_LIB       := ${HALIB_LIB_DIR}/lib${PLATFORM}.a

LDPATHS            += ${HALIB_LIB_DIR}
LIBS               += ${PLATFORM}

INCLUDE            := ${PLATFORM_DIR}/include

PLATFORM_ASFLAGS   := -mcpu=cortex-m4                   \
		              -mthumb                           \
			          -D PLL_MUL=${PLL_MULTIPLICATOR}   \
		              -D PLL_DIV=${PLL_DIVISOR}         \
			          -D PRES_EXP=${PRESCALER_EXPONENT} \
		              -D F_XTAL=${CRYSTAL_FREQUENCY}

PLATFORM_CFLAGS    := ${PLATFORM_ASFLAGS}

PLATFORM_CXXFLAGS  := ${PLATFORM_ASFLAGS}

PLATFORM_LDFLAGS   := -T ${PLATFORM_DIR}/link.ld

include ${HALIB_DIR}/make/submodules.mk
include ${PLATFORM_DIR}/flash.mk
include ${PLATFORM_DIR}/debug.mk
