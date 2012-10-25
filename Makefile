HALIB_DIR :=$(abspath $(dir $(lastword ${MAKEFILE_LIST})))

#DISTCLEAN += ${HALIB_DIR}/external/lm4tools

.PHONY: proxy doc

proxy: help

include ${HALIB_DIR}/make/defaults.mk
include ${HALIB_DIR}/make/lib.mk

.PHONY: help all ${PLATFORMS} distclean

help:
	@echo "Platforms: all ${PLATFORMS}"

doc:
	doxygen doc/Doxyfile

all: ${PLATFORMS}

clean:

distclean:
	rm -rf ${DISTCLEAN}
	${MAKE} -C ./examples distclean
