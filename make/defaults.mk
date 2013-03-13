PREFIX := arm-none-eabi-

CC     ?= gcc
AS     ?= ${CC}
CXX    ?= g++
LD     ?= ld
OBJCPY ?= objcopy
OBJDMP ?= objdump
DBG    ?= gdb
AR     ?= ar

AS     := ${PREFIX}${AS}
CC     := ${PREFIX}${CC}
CXX    := ${PREFIX}${CXX}
LD     := ${PREFIX}${LD}
OBJCPY := ${PREFIX}${OBJCPY}
OBJDMP := ${PREFIX}${OBJDMP}
DBG    := ${PREFIX}${DBG}
AR     := ${PREFIX}${AR}

DEFAULT_ARFLAGS  := 

DEFAULT_ASFLAGS  := 

DEFAULT_CFLAGS   := ${ASFLAGS}              \
                    -ffreestanding          \
                    -nostdlib               \
                    -fno-strict-aliasing    \
                    -fno-exceptions         \
                    -fno-threadsafe-statics \
                    -ffunction-sections

DEFAULT_CXXFLAGS := ${DEFAULT_CFLAGS} \
                    -fno-rtti

DEFAULT_OBJCPY_FLAGS := -O binary \
                        -j .text  \
                        -j .data

DEFAULT_OBJDMP_FLAGS  := -Cdx

DEFAULT_LDFLAGS := --gc-sections -u init -u exceptions

HALIB_LIB_DIR   := ${HALIB_DIR}/lib
HALIB_BUILD_DIR := ${HALIB_DIR}/build
HALIB_INC       := ${HALIB_DIR}/include
EXT_INC         := ${HALIB_DIR}/external
