GEN_DIRS     := $(sort ${GEN_DIRS} ${BUILD})

INCLUDES     := $(addprefix -I, ${INCLUDES} ${PLATFORM_INCLUDES} ${HALIB_INC} ${EXT_INC})

ASFLAGS      += ${PLATFORM_ASFLAGS} ${DEFAULT_ASFLAGS}
CFLAGS       += ${PLATFORM_CFLAGS} ${DEFAULT_CFLAGS}
CXXFLAGS     += ${PLATFORM_CXXFLAGS} ${DEFAULT_CXXFLAGS}
LDFLAGS      += ${PLATFORM_LDFLAGS} ${DEFAULT_LDFLAGS}
OBJDMP_FLAGS += ${DEFAULT_OBJDMP_FLAGS}

vpath %.c   ${SRC} ${HALIB_SRC}
vpath %.S   ${SRC} ${HALIB_SRC}
vpath %.cpp ${SRC} ${HALIB_SRC}
vpath %.h   ${INCLUDES}

${GEN_DIRS}: %:
	mkdir -p $@

${BUILD}/%.o: %.c   | ${BUILD}
	$(CC) ${CFLAGS} -c -o $@ $< ${INCLUDES}

${BUILD}/%.o: %.cpp | ${BUILD}
	$(CXX) ${CXXFLAGS} -c -o $@ $< ${INCLUDES}

${BUILD}/%.o: %.S   | ${BUILD}
	$(AS) ${ASFLAGS} -c -o $@ $< ${INCLUDES}
