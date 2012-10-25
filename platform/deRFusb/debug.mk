CLEAN += openocd.log

.PHONY: %.debug

%.debug: ${BIN}/%.elf
	${DBG} -ex "target remote | openocd -f ${PLATFORM_DIR}/openocd.cfg -p -c 'log_output openocd.log'" $<
