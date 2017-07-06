#include <stdlib.h>

int main(int argc, char* argv[]) {
	execve("bash", "ls", NULL);

	return 0;
}