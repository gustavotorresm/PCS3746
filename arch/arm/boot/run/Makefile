GCC = "arm-none-linux-gnueabi-gcc"
CFLAGS = 

QEMU = "qemu-system-arm"
KERNEL = "../zImage"
INIT = "/init"

out/init: init.c
	$(GCC) -static $(CFLAGS) $(INCLUDES) $< -o $@ 

out/insert: queue_insert.c
	$(GCC) -static $(CFLAGS) $(INCLUDES) $< -o $@ 

out/remove: queue_remove.c
	$(GCC) -static $(CFLAGS) $(INCLUDES) $< -o $@ 


build: clean out/init out/insert out/remove
	cd out && find . -depth -print | cpio -o --format=newc > ../rootfs


run: build
	$(QEMU) -M versatilepb -m 128M -kernel $(KERNEL) -initrd rootfs -append "root=/dev/ram rdinit=$(INIT)"

debug: build
	$(QEMU) -M versatilepb -m 128M -kernel $(KERNEL) -initrd rootfs -append "root=/dev/ram rdinit=$(INIT)" -s -S

clean:
	rm -f out/*