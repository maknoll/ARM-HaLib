.PHONY: %.program
.PRECIOUS: ${BIN}/%.bin

LM4TOOLS  := ${HALIB_DIR}/external/lm4tools
LM4FLASH  := ${LM4TOOLS}/lm4flash/lm4flash

OBJCPY_FLAGS := ${DEFAULT_OBJCPY_FLAGS}

${BIN}/%.bin: ${BIN}/%.elf | ${BIN}
	${OBJCPY} ${OBJCPY_FLAGS} $< $@

${LM4FLASH}:
	${MAKE} -C $(dir ${LM4FLASH})

%.program: ${BIN}/%.bin ${LM4FLASH}
	${LM4FLASH} $<
