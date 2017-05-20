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

/* Creates the head node */
LIST_HEAD(head);

QUEUE queue = {.elements=0};

/**
 * Inserts a long value into the queue.
 * Returns 0 if everything went OK or not 0 otherwise.
 */
asmlinkage long sys_insert(long value) {
	QUEUE_NODE *newNode;

	if (!queue.head. next || !queue.head.prev) {
		&queue.head = &head;
	}

	newNode = kmalloc(sizeof *newNode, GFP_KERNEL);
	newNode->value = value;
	INIT_LIST_HEAD(&newNode->list);

	printk("Insert %ld into Levy Queue!!\n", newNode->value);
	list_add_tail(&newNode->list, &queue.head);

	queue.elements++;
	printk("Levy queue has currently %d element(s)\n", queue.elements);
	return 0;
}

asmlinkage long sys_remove(void) {
	QUEUE_NODE *node;

	if (queue.elements < 1) {
		printk("Queue is empty");
		return -1;
	}

	node = list_first_entry(&queue.head, QUEUE_NODE, list);

	printk("Remove value %ld from Levy Queue!!\n", node->value);
	return 0;
}