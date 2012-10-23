.PHONY: %.debug

%.debug: ${TARGET}
	openocd -f ${PLATFORM_DIR}/openocd.cfg
	${DBG} ${TARGET}
	openocd -c "shutdown"
