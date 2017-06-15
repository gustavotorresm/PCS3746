#include <sys/syscall.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

#include "custom_syscalls.h"

int main() {
	srand(time(NULL));

	while(1) {
		int value = rand();
		long waitTime = random() % 5 + 1;

		printf("[insert] Call insert with value %lu\n", value);
		syscall(QUEUE_INSERT, value, NULL);
		sleep(waitTime);
	}

	return 0;
}