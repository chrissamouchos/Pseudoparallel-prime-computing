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
	// close(fd);
	return 0;
}