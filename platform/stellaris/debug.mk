.PHONY: %.debug

LM4TOOLS := ${HALIB_DIR}/external/lm4tools
LMICDI   := ${LM4TOOLS}/lmicdiusb/lmicdi

${LMICDI}:
	${MAKE} -C $(dir ${LMICDI})

%.program: ${BIN}/%.bin ${LM4FLASH}
	${LM4FLASH} $<

%.debug: ${BIN}/%.elf ${LMICDI}
	${LMICDI} &
	${DBG} $<
