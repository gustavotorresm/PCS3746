/*
 *  linux/arch/arm/kernel/queue.c
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */
#include <linux/syscalls.h>
#include <linux/list.h>
#include <linux/slab.h>

/* Creates an empty queue */
unsigned int queue_elements = 0;
LIST_HEAD(head);

/**
 * Inserts a long value into the queue.
 * Returns 0 if everything went OK or not 0 otherwise.
 */
asmlinkage long sys_insert(long value) {
	QUEUE_NODE *newNode;

	newNode = kmalloc(sizeof *newNode, GFP_KERNEL);
	newNode->value = value;
	INIT_LIST_HEAD(&newNode->list);	

	//printk("[kernel] Insert %ld into System Queue!!\n", newNode->value);
	list_add_tail(&newNode->list, &head);

	queue_elements++;
	//printk("[kernel] System queue has currently %d element(s)\n", queue_elements);

	return 0;
}

asmlinkage long sys_remove(void) {
	QUEUE_NODE *node;
	long value;

	if (queue_elements < 1) {
		printk("[kernel] Queue is empty\n");
		return -1;
	}

	node = list_first_entry(&head, QUEUE_NODE, list);
	value =  node->value;
	list_del(&node->list);
	kfree(node);
	queue_elements--;

	printk("[kernel] Remove value %ld from System Queue!!\n", value);
	return value;
}