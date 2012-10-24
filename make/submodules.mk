.PHONY: submodules

submodules:
	cd ${HALIB_DIR} && git submodule init && git submodule update && cd ${OLD_PWD}
