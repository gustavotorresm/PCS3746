#include <stdio.h>
#include <string.h>

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
	const char *scenario = get_scenario(argc, argv);

	printf("Using scenario %s\n", scenario);
	execve(scenario, argv, NULL);

	while(1);
}

