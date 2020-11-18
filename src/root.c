/*This is the master process, that all data is returned in order to be printed /
/ via condole. The user will able to see some simple statistics apart from the /
/ results. n,m are the boundaries that the program will search for primes	  */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include "Utils.h"

volatile int signals_received = 0;

void signal_handler(int signum);

int main(int argc, char** argv){
	int NumOfChildren = 0;	/*Possible childern each node will have			*/
	int c;					/*Possible Options								*/
	int n, m;				/*Lower and Upper numeric bound, respectively 	*/

	/* -------------Get Optios of Command line--------------*/
	while( (c = getopt(argc,argv,"l:u:w:")) != -1) {
		switch(c) {
			case 'l':
				n = atoi(optarg);
				break;
			case 'u':
				m = atoi(optarg);
				break;
			case 'w':
				NumOfChildren = atoi(optarg);
				break;
			case '?':
				usage(argv[0]);	/*wrong input*/
				return 1;
		}	
	}
	/*---------------End of Options Parsing----------------*/

	if(n > m){			/*Check if given numbers are legit*/
		printf("Error: Lower bound greater than upper bound!\n");
		return(2);
	}
	else{
		/*Print start execution message	  */
		printf("Executing ./myprime within [%d,%d] with %d NumOfChildren...\n", n, m, NumOfChildren); 
	}
	
	int status;		/*flag to store info about mkfifo*/
	char name[24];	/*max string named computed from max int to be stored + 2, also memory multiple of 2*/
	char** fds = malloc(sizeof(char*)*NumOfChildren);
	int* fd_ids = malloc(sizeof(int)*NumOfChildren);

	/*---------Create named pipes for interprocess communication--*/
	for(int i = 0; i < NumOfChildren; i++){
		sprintf(name, "in%d", i);
		fds[i] = strdup(name);
		status = mkfifo(name, 0666);
		if(status < 0)
			perror("Error, pipe creation");
	}

	printf("OUTPUT (per invocation of program):\n\n");
	printf("Primes in [%d, %d] are: \n", n, m);
	
	/*--------------Create inner nodes----------------------------*/
	char* executable = "./inner_node";
	pid_t root_pid = getpid();
	signal(SIGUSR1, signal_handler);
	split_n_exec(n, m, NumOfChildren, executable, root_pid); /*Split n exec innernodes.*/
	/*--------------End of Creation-------------------------------*/

	/*--------------Open pipes for Reading------------------------*/
	for(int i = 0; i < NumOfChildren; i++)
		fd_ids[i] = open(fds[i], O_RDONLY | O_NONBLOCK);


	while(wait(NULL)>0);									/*wait until all inner nodes have finished*/
	printf("Num of USR1 Received : %d\n", signals_received);/*print all USR1 from leafs*/
	
	/*----------------Unlink all fifos-------------------*/
	for(int i = 0; i < NumOfChildren; i++){
		close(fd_ids[i]);
		unlink(fds[i]);
	}

	/*----------------Free all the allocated memory------*/
	free(fds);
	free(fd_ids);
	
	return 0;
}
/*--------------------Handle USR1 received---------------*/
void signal_handler(int signum){
	signals_received++;
}