#include <sys/syscall.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "custom_syscalls.h"

#define TRUE 1
#define FALSE 0

static int flags[2] = {FALSE, FALSE};
static int turn;

int scheduler_disabled = 0;

int is_scheduler_disabled(int argc, char** argv) {
	return argc < 2 || argv[1] == NULL;
}

void wait_random() {
	#define MILISECOND 1000000

	struct timespec wait_time;
	wait_time.tv_sec = random() % 5;
	wait_time.tv_nsec = 500 * MILISECOND;

	nanosleep(&wait_time, NULL);
}

void iterate_long_loop() {

	long iterations = 10000000;
	for(int i = 0; i < iterations; ++i) {

	}
}

void *run(void *args) {
	char *process_number = (char*) args;
	int process_id = atoi(process_number) - 1;
	int other_process = (1 - process_id) % 2;

	if (scheduler_disabled)
		syscall(DISABLE_SCHEDULER, NULL, NULL);

	while(1) {
		long value;

		flags[process_id] = TRUE; // Processo Px quer entrar na região crítica
		turn = other_process; // Processo Px dá a vez ao outro processo

		while(flags[other_process] && turn == other_process) {
			// wait
		}
		// Critical section
		value = syscall(LEIA, 0, NULL);
		printf("[Process %s] %d\n",process_number, value);
		//iterate_long_loop();
		value += 1;
		syscall(ESCREVA, value);
		// End of critical section

		flags[process_id] = FALSE; // Processo não quer mais usar a região cŕitica

		if (!scheduler_disabled)
			wait_random();
	}
}

void create_process(pthread_t* process, const char process_number[]) {
	int thread_creation_status;

	thread_creation_status = pthread_create(process, NULL, run, (void *) process_number);
	if (thread_creation_status) {
		printf("Failed to create process #%d. Error code %d\n", process_number, thread_creation_status);
	}
}

int main(int argc, char** argv) {
	scheduler_disabled = is_scheduler_disabled(argc, argv);

	srand(time(NULL));
	pthread_t process1, process2;

	turn = 1;
	create_process(&process1, "1");
	create_process(&process2, "2");

	pthread_join(process1, NULL);
	pthread_join(process2, NULL);

	return 0;
}