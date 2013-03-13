GEN_DIRS     := $(sort ${GEN_DIRS})
CLEAN        := $(sort ${CLEAN})
DISTCLEAN    := $(sort ${CLEAN} ${DISTCLEAN})

INCLUDES     := $(addprefix -I, ${INCLUDES} ${PLATFORM_INCLUDES} ${HALIB_INC} ${EXT_INC})

ASFLAGS      += ${PLATFORM_ASFLAGS} ${DEFAULT_ASFLAGS}
CFLAGS       += ${PLATFORM_CFLAGS} ${DEFAULT_CFLAGS}
CXXFLAGS     += ${PLATFORM_CXXFLAGS} ${DEFAULT_CXXFLAGS}
LDFLAGS      += ${PLATFORM_LDFLAGS} ${DEFAULT_LDFLAGS}
OBJDMP_FLAGS += ${DEFAULT_OBJDMP_FLAGS}

DEPS         := $(wildcard ${BUILD}/*.d)

.PHONY: clean distclean
.PRECIOUS: ${BUILD}/%.o

vpath %.c   ${SRC} ${HALIB_SRC}
vpath %.S   ${SRC} ${HALIB_SRC}
vpath %.cpp ${SRC} ${HALIB_SRC}
vpath %.h   ${INCLUDES}

${GEN_DIRS}: %:
	mkdir -p $@

${BUILD}/%.o: %.c ${MAKEFILE_LIST} | ${BUILD}
	$(CC) ${CFLAGS} ${INCLUDES} -MT $@ -MM -o $@.d $< 
	$(CC) ${CFLAGS} ${INCLUDES} -c -o $@ $< 

${BUILD}/%.o: %.cpp ${MAKEFILE_LIST} | ${BUILD}
	$(CXX) ${CXXFLAGS} ${INCLUDES} -MT $@ -MM -o $@.d $< 
	$(CXX) ${CXXFLAGS} ${INCLUDES} -c -o $@ $< 

${BUILD}/%.o: %.S ${MAKEFILE_LIST} | ${BUILD}
	$(AS) ${ASFLAGS} ${INCLUDES} -MT $@ -MM -o $@.d $< 
	$(AS) ${ASFLAGS} ${INCLUDES} -c -o $@ $< 

clean:
	rm -rf ${CLEAN}

distclean:
	rm -rf ${DISTCLEAN}

include ${DEPS}
