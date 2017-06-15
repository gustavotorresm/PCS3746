#include <sys/syscall.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

#include "custom_syscalls.h"

int main() {
	srand(time(NULL));

	while(1) {
		long value;
		long waitTime = random() % 10 + 5;

		value = syscall(QUEUE_REMOVE, 0, NULL);
		if (value == -1) {
			printf("[remove] Could not fetch value from queue\n");
		} else {
			printf("[remove] Remove returned value %lu\n", value);
		}
		
		sleep(waitTime);
	}

	return 0;
}