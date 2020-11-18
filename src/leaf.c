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
	printf("leaf with id: %d\n", pid);
	int low, up, numof, is, sroot_id;
	low = atoi(argv[1]);
	up = atoi(argv[2]);
	numof = atoi(argv[3]);
	is = atoi(argv[4]);
	int flag = is % 3;
	sroot_id = atoi(argv[5]);

	char* send_pipe = malloc(sizeof(char)*2 + 10);
	/*--------------Open pipe to send----------------------*/
	sprintf(send_pipe, "le%dp%d", is, getppid());
	int fd_id = open(send_pipe, O_WRONLY | O_NONBLOCK);

	double prime_time = 0.0, time_spent = 0.0;
	clock_t begin = clock(), t_begin, t_end;
	int cur = low + 1;
	int prime_found;
	
	switch(flag){
		case 0:
			for(; cur <= up; cur++){
				t_begin = clock();
				prime_found = prime_1(cur);
				t_end = clock();
				prime_time += (double)(t_end - begin)*1000 / CLOCKS_PER_SEC;
				//write();
				//write();	
			}
			break;
		case 1:
			for(; cur <= up; cur++){
				t_begin = clock();
				prime_found = prime_2(cur);
				t_end = clock();
				prime_time += (double)(t_end - begin)*1000 / CLOCKS_PER_SEC;
				//write();
				//write();
			}
			break;
		case 2:
			for(; cur <= up; cur++){
				t_begin = clock();
				prime_found = my_prime(cur);
				t_end = clock();
				prime_time += (double)(t_end - begin)*1000 / CLOCKS_PER_SEC;
				//write();
				//write();
			}
			break;
	}

	clock_t end = clock();
	time_spent += (double)(end - begin)*1000 / CLOCKS_PER_SEC;

	//write

	close(fd_id);
	unlink(send_pipe);

	kill(sroot_id, SIGUSR1);
	return 0;
}