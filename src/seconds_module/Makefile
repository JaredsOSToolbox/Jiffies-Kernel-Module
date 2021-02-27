SHELL := /bin/bash
obj-m += seconds_module.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test:
	sudo dmesg -C
	sudo insmod seconds_module.ko
	grep "seconds_module" <<< `lsmod` >/dev/null && echo "inserted into kernel" || echo "not properly inserted into kernel space"
	[[ -e /proc/seconds ]] && cat /proc/seconds || echo "nope"
	sleep 2
	sudo rmmod seconds_module
	[[ ! -e /proc/seconds ]] && echo "successfully removed seconds proc from kernel space" || echo "failed to remove seconds proc file"
	dmesg
