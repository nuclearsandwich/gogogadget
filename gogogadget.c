#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void usage() {
	printf("USAGE: gogogadget PROGRAM {ARGS} -- FILES\n");
	printf("\tWatches files for changes and re-runs the program.\n");
	return;
}

int main(int argc, char *argv[]) {
	pid_t child_pid;
	int i, child_status;
	char **program = &argv[1], **watched_files;

	for (i = 0; i < argc; i++) {
		/* Find the break between the program and watched files */
		if (strcmp(argv[i], "--") == 0) {
			printf("Found -- on %d\n", i);
			argv[i] = NULL;
			watched_files = &argv[i + 1];
			i = argc;
		}
	}


	child_pid = fork();
	if (child_pid == 0) {
		if (execvp(program[0], program) > 0) {
			printf("Well something went wrong. Obviously.\n");
			return 1;
		}
	} else {
		printf("Spawned child pid %d\n", child_pid);
		waitpid(child_pid, &child_status, 0);
	}

	return 0;
}
