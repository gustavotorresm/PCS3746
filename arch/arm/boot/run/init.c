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
		execve("remove", 0, NULL);
	} 

	// Runs insert
	pid = fork();
	if (pid == 0) {
		/* Child process */
		execve("insert", 0, NULL);
	} 

	while(1);
}

