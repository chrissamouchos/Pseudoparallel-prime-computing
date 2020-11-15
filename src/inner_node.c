#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>		/* For file descriptors */
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "Utils.h"

int main(int argc, char** argv){
	reset();
	pid_t pid;
	pid = getpid();

	// int fd, status;
	// char* root_node = "root_node";
	// char str[100];
	// status = open(root_node, O_RDONLY);
	// read(fd, str, sizeof(str));
	// printf("Received %s\n", str);

	printf("ID: %d Lower bound: %d\n", pid, atoi(argv[1]));
	printf("ID: %d Upper bound: %d\n", pid, atoi(argv[2]));

	char* executable = "./leaf";
	split_n_exec(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), executable);
	wait(NULL);
	// close(fd);
	return 0;
}