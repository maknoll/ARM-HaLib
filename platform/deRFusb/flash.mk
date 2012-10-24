.PHONY: %.program
.PRECIOUS: ${BIN}/%.bin

OBJCPY_FLAGS := ${DEFAULT_OBJCPY_FLAGS}

${BIN}/%.bin: ${BIN}/%.elf | ${BIN}
	${OBJCPY} ${OBJCPY_FLAGS} $< $@

%.program: ${BIN}/%.bin
	openocd -f ${PLATFORM_DIR}/openocd.cfg -c "flash write_bank 0 $< 0" -c " reset run" -c "shutdown"
