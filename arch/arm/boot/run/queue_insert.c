#include <sys/syscall.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

#include "queue.h"

int main() {
	srand(time(NULL));

	while(1) {
		int value = rand();
		long waitTime = random() % 10 + 5;

		syscall(QUEUE_INSERT, value, NULL);
		sleep(waitTime);
	}

	return 0;
}