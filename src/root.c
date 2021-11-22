/*This is the master process, that all data is returned in order to be printed /
/ via console. The user will able to see some simple statistics apart from the /
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
#include <poll.h>

#include "Utils.h"
#include "Records.h"

<<<<<<< HEAD
volatile int signals_received = 0; /*Volatile: This variable could be changed unexpectedly*/
=======
volatile int signals_received = 0;
>>>>>>> refs/remotes/origin/main
int errno;

void signal_handler(int signum);	/*Simple signal handler prototype*/

int main(int argc, char** argv){
	int NumOfChildren = 0;	/*Possible childern each node will have			*/
	int c;					/*Possible Options								*/
	int n, m;				/*Lower and Upper numeric bound, respectively 	*/

	/* -------------Get Options of Command line--------------*/
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
	double* stats = malloc(sizeof(double)*NumOfChildren*NumOfChildren);	/*array of doubles to store execution time for all childs*/

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
		fd_ids[i] = open(fds[i], O_RDONLY);
<<<<<<< HEAD
=======

	Record_info r = create_head();
	Record temp = NULL;
	int prime = 0, flag = 0;
	double time = 0.0;
	// struct pollfd* pollfd = malloc(sizeof(struct pollfd) * NumOfChildren);		/*create info for polling*/
	
	// for(int i = 0; i < NumOfChildren; i++){
	// 	pollfd[i].fd = fd_ids[i];				/*store all fifo ids						 */
	// 	pollfd[i].events = POLLIN;				/*POLLIN -> capable of receiving data		 */
	// 	pollfd[i].revents = 0;					/*if someone is ready to send, find id index */
	// }

	// while(flag != NumOfChildren){
	// 	poll(pollfd, NumOfChildren, -1);		/*-1 indicates blocking untill someone finishes sending		*/
	// 	prime = 0;
	// 	time = 0.0;
	// 	for(int i = 0; i < NumOfChildren; i++){
	// 		if(pollfd[i].revents & POLLIN){
	// 			pollfd[i].revents = 0;						/*re-initialize sending index 			*/
	// 			read(pollfd[i].fd, &prime, sizeof(int));
	// 			read(pollfd[i].fd, &time, sizeof(double));
				
	// 			if((prime == -1)&&(time == 0.0)){		/*when a process finished it sends -1 and execution time*/
	// 				flag ++;
	// 				pollfd[i].events = 0;
	// 			}
	// 			else{
	// 				temp = create_node(prime, time);	/*create a node and do insertion sort in list*/
	// 				insert_node(r, temp);
	// 				r -> size++;
	// 			}
	// 		}			
	// 	}
	// }


	for(int i = 0; i < NumOfChildren; i++){
		while(1){
			read(fd_ids[i], &prime, sizeof(int));
			read(fd_ids[i], &time, sizeof(double));
			if(prime != -1){
				temp = create_node(prime, time);	/*create a node and do insertion sort in list*/
				insert_node(r, temp);
			}
			else break;
		}
		for(int j = 0; j < NumOfChildren; j++){
			read(fd_ids[i], &stats[NumOfChildren*i + j], sizeof(double));	
		}
	}
>>>>>>> refs/remotes/origin/main

	Record_info r = create_head();
	Record temp = NULL;
	int prime = 0, flag = 0;
	double time = 0.0;
	// struct pollfd* pollfd = malloc(sizeof(struct pollfd) * NumOfChildren);		/*create info for polling*/
	
	// for(int i = 0; i < NumOfChildren; i++){
	// 	pollfd[i].fd = fd_ids[i];				/*store all fifo ids						 */
	// 	pollfd[i].events = POLLIN;				/*POLLIN -> capable of receiving data		 */
	// 	pollfd[i].revents = 0;					/*if someone is ready to send, find id index */
	// }

	// while(flag != NumOfChildren){
	// 	poll(pollfd, NumOfChildren, -1);		/*-1 indicates blocking until someone finishes sending		*/
	// 	prime = 0;
	// 	time = 0.0;
	// 	for(int i = 0; i < NumOfChildren; i++){
	// 		if(pollfd[i].revents & POLLIN){
	// 			pollfd[i].revents = 0;						/*re-initialize sending index 			*/
	// 			read(pollfd[i].fd, &prime, sizeof(int));
	// 			read(pollfd[i].fd, &time, sizeof(double));
				
	// 			if((prime == -1)&&(time == 0.0)){		/*when a process finished it sends -1 and execution time*/
	// 				flag ++;
	// 				pollfd[i].events = 0;
	// 			}
	// 			else{
	// 				temp = create_node(prime, time);	/*create a node and do insertion sort in list*/
	// 				insert_node(r, temp);
	// 				r -> size++;
	// 			}
	// 		}			
	// 	}
	// }


	for(int i = 0; i < NumOfChildren; i++){
		while(1){
			read(fd_ids[i], &prime, sizeof(int));
			read(fd_ids[i], &time, sizeof(double));
			if(prime != -1){
				temp = create_node(prime, time);	/*create a node and do insertion sort in list*/
				insert_node(r, temp);
			}
			else break;
		}
		for(int j = 0; j < NumOfChildren; j++){
			read(fd_ids[i], &stats[NumOfChildren*i + j], sizeof(double));	
		}
	}

	while(wait(NULL)>0);			/*wait until all inner nodes have finished*/
	/*----------------Begin printing stats ---------------*/
	Record tem = NULL;
	tem = r -> next;
	double min_time = 0.0, max_time = 0.0;
	while(tem !=  NULL){
		printf("%d %lf ms\n", tem -> number, tem -> time);
		tem = tem -> next;
	}

	for(int j = 0; j < NumOfChildren*NumOfChildren; j++){
		printf("Time for W%d: %lf msecs\n", j, stats[j]);
	}

<<<<<<< HEAD
=======
	while(wait(NULL)>0);			/*wait until all inner nodes have finished*/
	/*----------------Begin printing stats ---------------*/
	Record tem = NULL;
	tem = r -> next;
	double min_time = 0.0, max_time = 0.0;
	while(tem !=  NULL){
		printf("%d %lf ms\n", tem -> number, tem -> time);
		tem = tem -> next;
	}

	for(int j = 0; j < NumOfChildren*NumOfChildren; j++){
		printf("Time for W%d: %lf msecs\n", j, stats[j]);
	}

>>>>>>> refs/remotes/origin/main
	printf("Num of USR1 Received : %d\n", signals_received);/*print all USR1 from leafs*/
	/*----------------End of printing stats -------------*/


	/*----------------Unlink all fifos-------------------*/
	for(int i = 0; i < NumOfChildren; i++){
		close(fd_ids[i]);
		unlink(fds[i]);
	}

	/*----------------Free all the allocated memory------*/
	free(fds);
	free(fd_ids);
	destroy_records(r);
	// free(pollfd);
	free(stats);
	
	return 0;
}
/*--------------------Handle USR1 received---------------*/
void signal_handler(int signum){
	signals_received++;
}