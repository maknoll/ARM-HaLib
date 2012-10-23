HALIB_DIR := $(abspath $(dir $(lastword ${MAKEFILE_LIST}))/..)

BIN     ?= ./bin
BUILD   ?= ./build
SRC     ?= ./src
INC     ?= ./include

DISTCLEAN += ./bin ./build

BIN     := ${BIN}/${PLATFORM}
BUILD   := ${BUILD}/${PLATFORM}

.PHONY: proxy

proxy: help

include ${HALIB_DIR}/make/defaults.mk
include ${HALIB_DIR}/platform/${PLATFORM}/config.mk

SOURCES := $(wildcard ${SRC}/*.c) $(wildcard ${SRC}/*.cpp) $(wildcard ${SRC}/*.S)

LIBS     := $(addprefix -l, ${LIBS})
LDPATHS  := $(addprefix -L, ${LDPATHS})

TARGET_SHORTCUTS := $(basename $(notdir ${SOURCES}))
TARGET_DUMPS     := $(addsuffix .dump, ${TARGET_SHORTCUTS})
TARGETS          := $(addprefix ${BIN}/, $(addsuffix .elf, ${TARGET_SHORTCUTS}))
GEN_DIRS         += ${BIN} ${BUILD}
CLEAN            += ${BIN} ${BUILD} $(wildcard *.dump)

.PHONY:    all help ${TARGET_SHORTCUTS}
.PRECIOUS: ${TARGETS}

help:
	@echo "Targets: all ${TARGET_SHORTCUTS}"

all: ${TARGETS}

${TARGET_SHORTCUTS}: %: ${BIN}/%.elf

include ${HALIB_DIR}/make/base.mk
include ${HALIB_DIR}/make/lib.mk

${BIN}/%.elf: ${BUILD}/%.o ${PLATFORM_LIB} ${MAKEFILE_LIST} | ${BIN}
	$(LD) ${LDFLAGS} -o $@  $< ${LDPATHS} ${LIBS}

${TARGET_DUMPS}: %.dump: ${BIN}/%.elf ${MAKEFILE_LIST}
	${OBJDMP} ${OBJDMP_FLAGS} $< > $@
