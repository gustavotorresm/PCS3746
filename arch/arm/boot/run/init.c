#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include <signal.h>

const char* get_scenario(int argc, char* argv[]) {
	if (argc == 1) {
		return "peterson";
	} else if (strcmp(argv[1], "dummy") == 0) {
		return "dummy_process";
	} else if (strcmp(argv[1], "peterson") == 0) {
		return "peterson";
	}
} 

void main(int argc, char* argv[]) {
	pid_t pid;
	const char *scenario = get_scenario(argc, argv);

	printf("Using scenario %s\n", scenario);

	//Runs remove
	pid = fork();
	if (pid == 0) {
		/* Child process */
		char *argv[] = {"1", NULL};
		execve(scenario, argv, NULL);;
	} else {
		/* Parent process */
		char *argv[] = {"2", NULL};
		execve(scenario, argv, NULL);
	}

	while(1);
}

