ifneq ($(KERNELRELEASE),)

obj-m := driver.o

else
	KDIR := /home/osboxes/Documents/PCS3746

all:
	$(MAKE) ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean

endif