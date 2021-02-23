SHELL := /bin/bash
obj-m += golden_ratio.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test:
	sudo dmesg -C
	sudo insmod golden_ratio.ko
	grep "golden_ratio" <<< `lsmod` >/dev/null && echo "inserted into kernel" || echo "not properly inserted into kernel space"
	#[[ -e /proc/jiffies ]] && cat /proc/jiffies || echo "nope"
	sudo rmmod golden_ratio
	dmesg
