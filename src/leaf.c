#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv){
	pid_t pid;
	pid = getpid();
	// int fd, status;
	// char* root_node = "root_node";
	// char str[100];
	// status = open(root_node, O_RDONLY);
	// read(fd, str, sizeof(str));
	// printf("Received %s\n", str);
	// printf("LID: %d Lower bound: %d\n", pid, atoi(argv[1]));
	// printf("LID: %d Upper bound: %d\n", pid, atoi(argv[2]));
	// printf("LID %d with id: %d\n",pid, atoi(argv[5]));
	
	kill(atoi(argv[5]),SIGUSR1);
	// close(fd);
	return 0;
}