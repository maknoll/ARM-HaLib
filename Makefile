HALIB_DIR :=$(abspath $(dir $(lastword ${MAKEFILE_LIST})))

.PHONY: proxy

proxy: help

include ${HALIB_DIR}/make/lib.mk

.PHONY: help all ${PLATFORMS} distclean

help:
	@echo "Platforms: all ${PLATFORMS}"

all: ${PLATFORMS}

clean:

distclean:
	@echo ${DISTCLEAN_CMD}
