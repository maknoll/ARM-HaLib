TARGET     := build/$(shell basename `pwd`).elf
TARGET_DIR := $(dir ${TARGET})
TARGET_BIN := $(basename ${TARGET}).bin
PREFIX     := arm-none-eabi-
AS         := ${PREFIX}gcc
CC         := ${PREFIX}gcc
CXX        := ${PREFIX}g++
LD         := ${PREFIX}ld
OCPY       := ${PREFIX}objcopy
OBJDUMP    := ${PREFIX}objdump
ASFLAGS    := -Os -g\
	          -mcpu=cortex-m3 \
		      -mthumb \
		      -I include \
			  -I external \
		      -D PLL_MUL=124 \
		      -D PLL_DIV=24 \
			  -D PRES_EXP=1 \
		      -D F_XTAL=18432000ULL
CFLAGS     := ${ASFLAGS} \
		      -ffreestanding \
		      -nostdlib \
		      -fno-strict-aliasing \
		      -fno-exceptions \
		      -fno-threadsafe-statics \
			  -ffunction-sections
CXXFLAGS   := ${CFLAGS} \
 		      -fno-rtti
LDFLAGS    := -T ldscripts/link.ld --gc
LDPATHS    := 
LIBS       := 
DEBUGGER   := ${PREFIX}gdb

SOURCES    := $(wildcard ./src/*.c) $(wildcard ./src/*.cpp) $(wildcard ./src/*.S)
OBJECTS    := $(foreach file, ${SOURCES}, ./build/$(notdir $(basename ${file})).o)

.PHONY: openocd

vpath %.c   ./src
vpath %.S   ./src
vpath %.cpp ./src

all: ${TARGET}

./build:
	mkdir -p $@

clean:
	rm -r build

debug: ${TARGET}
	${DEBUGGER} ${TARGET}

openocd: 
	openocd -f openocd/debug.cfg &

sim: build
	qemu-system-arm \
	  -cpu cortex-m3 \
	  -nographic \
	  -monitor null \
	  -serial null \
	  -s -S \
	  -kernel ${TARGET} \
	  -daemonize

telnet:
	telnet localhost 4444

flash: ${TARGET_BIN}
	openocd -f openocd/init.cfg -c "at91sam3 gpnvm set 1" -c "flash write_bank 0 ${TARGET_BIN} 0" -f openocd/shutdown.cfg


$(TARGET): 	${OBJECTS} | ./build
	$(LD) ${LDFLAGS} -o $@  $^ ${LDPATHS} ${LIBS}

${TARGET_BIN}: ${TARGET} | ./build
	${OCPY} -O binary -j .text -j .data $< $@

dump: ${TARGET}
	${OBJDUMP} -Cdx $< > ${TARGET}.dump

build/%.o: %.c | ./build
	$(CC) ${CFLAGS} -c -o $@ $<

build/%.o: %.cpp | ./build
	$(CXX) ${CXXFLAGS} -c -o $@ $<

build/%.o: %.S | ./build
	$(AS) ${ASFLAGS} -c -o $@ $<
