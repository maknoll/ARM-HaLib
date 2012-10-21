.PHONY: openocd debug telnet flash

OBJCPY_FLAGS := ${DEFAULT_OBJCPY_FLAGS}


${TARGET_BIN}: ${TARGET} | ./build
	${OBJCPY} ${OBJCPY_FLAGS} $< $@

debug: ${TARGET}
	${DBG} ${TARGET}

openocd: 
	openocd -f openocd/debug.cfg &

telnet:
	telnet localhost 4444

flash: ${TARGET_BIN}
	openocd -f openocd/init.cfg -c "at91sam3 gpnvm set 1" -c "flash write_bank 0 ${TARGET_BIN} 0" -f openocd/shutdown.cfg
