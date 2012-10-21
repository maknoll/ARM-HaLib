PLATFORMS := $(notdir $(wildcard ${HALIB_DIR}/platform/*))

${PLATFORMS}: %:
	${MAKE} PLATFORM=$@ -C ${HALIB_DIR} -f ${HALIB_DIR}/make/build_lib.mk lib

${HALIB_DIR}/lib/lib%.a: %
