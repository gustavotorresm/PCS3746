/*
 *  linux/arch/arm/kernel/shared_memory.c
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */
#include <linux/syscalls.h>
#include <linux/slab.h>

long stored_value;
unsigned int read_without_write_pid = 0;

void verify_racing_condition() {
	if (current->pid != read_without_write_pid) {
		printk("------ Racing condition\n");
	} else {
		read_without_write_pid = 0;
	}
}


asmlinkage long sys_leia() {
	read_without_write_pid = current->pid;

	return stored_value;
}

asmlinkage long sys_escreva(long value) {
	verify_racing_condition();

	stored_value = value;
	return 0;
}