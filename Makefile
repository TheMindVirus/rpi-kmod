obj-m += kmod.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
install:
	insmod ./kmod.ko
remove:
	rmmod kmod
status:
	cat /var/log/messages
edit:
	nano ./kmod.c
