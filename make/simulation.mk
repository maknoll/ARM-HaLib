sim: build
	qemu-system-arm \
	  -cpu cortex-m3 \
	  -nographic \
	  -monitor null \
	  -serial null \
	  -s -S \
	  -kernel ${TARGET} \
	  -daemonize
