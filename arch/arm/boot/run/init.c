#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include <signal.h>

void main() {
	pid_t pid;

	

	//Runs remove
	pid = fork();
	if (pid == 0) {
		/* Child process */
		char *argv[] = {"1", NULL};
		execve("dummy_process", argv, NULL);;
	} 

	// Runs insert
	pid = fork();
	if (pid == 0) {
		/* Child process */
		char *argv[] = {"2", NULL};
		execve("dummy_process", argv, NULL);
	} 

	while(1);
}

