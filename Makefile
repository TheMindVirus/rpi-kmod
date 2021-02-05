obj-m += kmod.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
install:
	insmod ./kmod.ko
remove:
	rmmod kmod
status:
	cat /var/log/messages
edit:
	nano ./kmod.c
