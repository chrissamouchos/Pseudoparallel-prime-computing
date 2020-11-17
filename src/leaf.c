/*arguments for exec* nameofexec, low, up, numof, is, sroot_id	 /
/								0,	1,	2,		3,	4,	5		*/
	
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

#include "Find_primes.h"

int main(int argc, char** argv){
	pid_t pid;
	pid = getpid();
	int low, up, numof, is, sroot_id;
	low = atoi(argv[1]);
	up = atoi(argv[2]);
	numof = atoi(argv[3]);
	is = atoi(argv[4]);
	int flag = is % 3;
	sroot_id = atoi(argv[5]);

	// switch(flag){
	// 	case 0:
	// 		// for(int i)
	// 		// prime_1();
	// 	case 1:
	// 		// prime_2();
	// 	case 2:
	// 		// my_prime();

	// }
	char* send_pipe = malloc(sizeof(char)*2 + 10);
	/*--------------Open pipe to send----------------------*/
	sprintf(send_pipe, "le%d", is);
	int fd_id = open(send_pipe, O_WRONLY);

	// int fd, status;
	// char* root_node = "root_node";
	// char str[100];
	// status = open(root_node, O_RDONLY);
	// read(fd, str, sizeof(str));
	// printf("Received %s\n", str);
	// printf("LID: %d Lower bound: %d\n", pid, atoi(argv[1]));
	// printf("LID: %d Upper bound: %d\n", pid, atoi(argv[2]));
	// printf("LID %d with id: %d\n",pid, atoi(argv[5]));
	close(fd_id);
	unlink(send_pipe);

	kill(sroot_id, SIGUSR1);
	return 0;
}