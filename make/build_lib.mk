HALIB_DIR := $(abspath $(dir $(lastword ${MAKEFILE_LIST}))/..)

include ${HALIB_DIR}/make/defaults.mk
include ${HALIB_DIR}/platform/${PLATFORM}/config.mk

ARFLAGS  += ${PLATFORM_ARFLAGS} ${DEFAULT_ARFLAGS}

BUILD := ${HALIB_DIR}/build/${PLATFORM}
SRC   := ${HALIB_DIR}/src

PLATFORM_OBJECTS := common start

PLATFORM_OBJECTS := $(addprefix ${BUILD}/, $(addsuffix .o, ${PLATFORM_OBJECTS}))

GEN_DIRS += ${HALIB_LIB_DIR}

ASFLAGS  += -Os -g
CFLAGS   += -Os -g
CXXFLAGS += -Os -g

include ${HALIB_DIR}/make/base.mk

.PHONY: lib

lib: ${PLATFORM_LIB}

${PLATFORM_LIB}: ${PLATFORM_OBJECTS} | ${HALIB_LIB_DIR}
	${AR} ${ARFLAGS} $@ $^
