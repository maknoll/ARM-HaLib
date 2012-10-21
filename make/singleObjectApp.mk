HALIB_DIR := $(abspath $(dir $(lastword ${MAKEFILE_LIST}))/..)

include ${HALIB_DIR}/make/defaults.mk
include ${HALIB_DIR}/platform/${PLATFORM}/config.mk

BIN     ?= ./bin
BUILD   ?= ./build
SRC     ?= ./src
INC     ?= ./include

BIN     := ${BIN}/${PLATFORM}
BUILD   := ${BUILD}/${PLATFORM}

SOURCES := $(wildcard ${SRC}/*.c) $(wildcard ${SRC}/*.cpp) $(wildcard ${SRC}/*.S)

LIBS     := $(addprefix -l, ${LIBS})
LDPATHS  := $(addprefix -L, ${LDPATHS})

TARGET_SHORTCUTS := $(basename $(notdir ${SOURCES}))
TARGET_DUMPS     := $(addsuffix .dump, ${TARGET_SHORTCUTS})
TARGETS          := $(addprefix ${BIN}/, $(addsuffix .elf, ${TARGET_SHORTCUTS}))
GEN_DIRS         += ${BIN}

.PHONY:    all help ${TARGET_SHORTCUTS}
.PRECIOUS: ${TARGETS}

help:
	@echo "Targets: all ${TARGET_SHORTCUTS}"

all: ${TARGETS}

${TARGET_SHORTCUTS}: %: ${BIN}/%

include ${HALIB_DIR}/make/base.mk

${BIN}/%.elf: ${BUILD}/%.o ${PLATFORM_LIB} | ${BIN}
	$(LD) ${LDFLAGS} -o $@  $< ${LDPATHS} ${LIBS}

%.dump: ${BIN}/%.elf
	${OBJDMP} ${OBJDMP_FLAGS} $< > $@

include ${HALIB_DIR}/make/openocd.mk
