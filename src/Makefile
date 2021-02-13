SHELL := /bin/bash
obj-m += jiffie.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test:
	sudo dmesg -C
	sudo insmod jiffie.ko
	grep "jiffie" <<< `lsmod`
	sudo rmmod jiffie
	dmesg
