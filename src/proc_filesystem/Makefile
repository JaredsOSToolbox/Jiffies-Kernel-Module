SHELL := /bin/bash
obj-m += proct.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test:
	sudo dmesg -C
	sudo insmod proct.ko
	grep "proct" <<< `lsmod`
	sudo rmmod proct
	dmesg
