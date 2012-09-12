TARGET = build/$(shell basename `pwd`).elf
AS = arm-none-eabi-gcc
CC = arm-none-eabi-gcc
CXX = arm-none-eabi-g++
LD = arm-none-eabi-gcc
CCFLAGS = -mcpu=cortex-m3 -mthumb -I include -g -D "F_CPU = 1000000" -ffreestanding \
				-fno-strict-aliasing \
			    -fno-exceptions \
			    -fno-rtti \
				-fno-threadsafe-statics
LDFLAGS = -T libsam3s/link.ld
DEBUGGER = arm-none-eabi-gdb

all: build

build: $(TARGET)

clean:
	rm -r build/*

debug: build
	$(DEBUGGER) $(TARGET)

openocd: 
	openocd -f debug.cfg &

libsam3s: libsam3s/libsam3s.a
	cd libsams3 & make

sim: build
	qemu-system-arm \
	  -cpu cortex-m3 \
	  -nographic \
	  -monitor null \
	  -serial null \
	  -s -S \
	  -kernel $(TARGET) \
	  -daemonize

$(TARGET): 	$(patsubst src/%.c, build/%.o, $(wildcard src/*.c)) \
			$(patsubst src/%.cpp, build/%.o, $(wildcard src/*.cpp)) \
			$(patsubst src/%.S, build/%.o, $(wildcard src/*.S))
	$(LD) $(LDFLAGS) -o $@ $^

build/%.o: src/%.c
	$(CC) $(CCFLAGS) -c -o $@ $^

build/%.o: src/%.cpp
	$(CXX) $(CCFLAGS) -c -o $@ $^

build/%.o: src/%.S
	$(AS) $(CCFLAGS) -c -o $@ $^
