SHELL := /bin/bash
obj-m += jiffies_module.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test:
	sudo dmesg -C
	sudo insmod jiffies_module.ko
	grep "jiffies_module" <<< `lsmod` >/dev/null && echo "inserted into kernel" || echo "not properly inserted into kernel space"
	[[ -e /proc/jiffies ]] && cat /proc/jiffies || echo "nope"
	sudo rmmod jiffies_module
	dmesg
