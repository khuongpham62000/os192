ifneq ($(KERNELRELEASE),)
    # call from kernel build system
	lifo-objs := main.o
	obj-m   := lifo.o
else
	4.15.0-99-generic ?= /lib/modules/$(shell uname -r)/build
	PWD       := $(shell pwd)
modules:
	echo $(MAKE) -C $(4.15.0-99-generic) M=$(PWD) LDDINC=$(PWD)/../include modules
	$(MAKE) -C $(4.15.0-99-generic) M=$(PWD) LDDINC=$(PWD)/../include modules
endif

clean:  
	rm -rf *.o *~ core .depend *.mod.o .*.cmd *.ko *.mod.c \
	.tmp_versions *.markers *.symvers modules.order

depend .depend dep:
	$(CC) $(CFLAGS) -M *.c > .depend

ifeq (.depend,$(wildcard .depend))
	include .depend
endif