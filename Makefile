HALIB_DIR :=$(abspath $(dir $(lastword ${MAKEFILE_LIST})))

include ${HALIB_DIR}/make/lib.mk

.PHONY: help all ${PLATFORMS}

help:
	@echo "Platforms: all ${PLATFORMS}"

all: ${PLATFORMS}
