#include <stdio.h>
#include <string.h>

const char* get_scenario(int argc, char* argv[]) {
	if (argc < 2) {
		return "peterson";
	} else if (strcmp(argv[1], "dummy") == 0) {
		return "dummy_process";
	} else if (strcmp(argv[1], "peterson") == 0) {
		return "peterson";
	}
}

const int get_scheduler(int argc, char* argv[]) {
	if (argc < 3) {
		return 1;
	} else if (strcmp(argv[2], "true") == 0) {
		return 1;
	} else if (strcmp(argv[2], "false") == 0) {
		return 0;
	}
} 

void main(int argc, char* argv[]) {
	const char *scenario = get_scenario(argc, argv);
	const int scheduler_enabled = get_scheduler(argc, argv);

	printf("Using scenario %s with scheduler %s.\n", scenario, scheduler_enabled ? "enabled" : "disabled");

	char *scheduler_status = scheduler_enabled ? "true": NULL;
	const char *args[] = {scenario, scheduler_status, NULL};
	execve(scenario, args, NULL);

	while(1);
}

