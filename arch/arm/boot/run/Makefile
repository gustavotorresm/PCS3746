GCC = "arm-none-linux-gnueabi-gcc"
CFLAGS = "-std=c99"

QEMU = "qemu-system-arm"
QUEMUFLAGS = ""
KERNEL = "../zImage"
INIT = "/init"

out/init: init.c
	$(GCC) -static $(CFLAGS) $(INCLUDES) $< -o $@ 

out/insert: queue_insert.c
	$(GCC) -static $(CFLAGS) $(INCLUDES) $< -o $@ 

out/remove: queue_remove.c
	$(GCC) -static $(CFLAGS) $(INCLUDES) $< -o $@ 

out/dummy_process: dummy_process.c
	$(GCC) -static $(CFLAGS) -D_POSIX_C_SOURCE=199309L $(INCLUDES) $< -o $@ 


build: clean out/init out/dummy_process
	cd out && find . -depth -print | cpio -o --format=newc > ../rootfs


run: build
	$(QEMU) -M versatilepb -m 128M -kernel $(KERNEL) -serial stdio -initrd rootfs -append "root=/dev/ram rdinit=$(INIT)" $(QEMUFLAGS)

run_terminal: build
	$(QEMU) -M versatilepb -m 128M -kernel $(KERNEL) -initrd rootfs -append "root=/dev/ram rdinit=$(INIT) console=ttyAMA0  console=ttyS0" $(QEMUFLAGS)

debug: build
	$(QEMU) -M versatilepb -m 128M -kernel $(KERNEL) -initrd rootfs -append "root=/dev/ram rdinit=$(INIT)" -s -S

clean:
	rm -f out/*