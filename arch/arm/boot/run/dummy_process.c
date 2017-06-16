#include <sys/syscall.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

#include "custom_syscalls.h"

void wait_random() {

	struct timespec wait_time;
	wait_time.tv_sec = random() % 5;
	wait_time.tv_nsec = 500000000;

	nanosleep(&wait_time, NULL);
}

void iterate_long_loop() {
	srand(time(NULL));

	long iterations = random() % 5000000;
	for(int i = 0; i < iterations; ++i) {

	}
}

int main(int argc, char** argv) {
	srand(time(NULL));
	char* process_number = argv[0];

	while(1) {
		long value;

		value = syscall(LEIA, 0, NULL);
		printf("[Process %s] %d\n",process_number, value);
		iterate_long_loop();
		value += 1;
		syscall(ESCREVA, value);

		wait_random();
	}

	return 0;
}