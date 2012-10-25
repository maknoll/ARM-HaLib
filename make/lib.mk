CLEAN += ${PLATFORM_LIB} ${HALIB_BUILD_DIR}/${PLATFORM}
DISTCLEAN += ${HALIB_LIB_DIR} ${HALIB_BUILD_DIR}

PLATFORMS := $(notdir $(wildcard ${HALIB_DIR}/platform/*))
LIB_DEPS  := $(wildcard ${HALIB_BUILD_DIR}/${PLATFORM}/*.d)

.PHONY: ${PLATFORMS}

${PLATFORMS}: %:
	${MAKE} PLATFORM=$@ -C ${HALIB_DIR} -f ${HALIB_DIR}/make/build_lib.mk lib

${PLATFORM_LIB}:
	${MAKE} PLATFORM=${PLATFORM} -C ${HALIB_DIR} -f ${HALIB_DIR}/make/build_lib.mk lib
