/*arguments for exec* nameofexec, low, up, numof, is, sroot_id	 /
/								0,	1,	2,		3,	4,	5		*/

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
// #include <poll.h>

#include "Utils.h"
#include "Status.h"
#include "Records.h"

#define MSG_SZ 16

int main(int argc, char** argv){
	pid_t pid;
	pid = getpid();
	/*---------------Initialize values given from exec----*/
	int low, up, numof, is, sroot_id;
	low = atoi(argv[1]);
	up = atoi(argv[2]);
	numof = atoi(argv[3]);
	is = atoi(argv[4]);
	sroot_id = atoi(argv[5]);
	/*---------------End of initialization-----------------*/

	Status s = create_status(numof);							/*struct to store info about sending/receiving pipes*/

	/*--------------Open pipe to send----------------------*/
	sprintf(s -> send_pipe, "in%d", is);						/*open pipe to send to root*/
	s -> fd_id = open(s -> send_pipe, O_WRONLY);	

	Record_info r = create_head();								/*create sorted simple linked list to store primes-times*/
	/*-----------------Read info---------------------------*/

	char* executable = "./leaf";
	printf("inner node with id: %d\n", pid);					/*printf info to ensure proper function of exec*/

	/*--------------Create and open pipes to read----------*/
	for(int i = 0; i < numof; i++){
		sprintf(s -> fd_name[i], "le%dp%d", i, getpid());		/*unique names of leaf pipes*/
		if(mkfifo(s -> fd_name[i], 0666) < 0)					/*create pipes*/
			perror("Error, pipe creation");
	}
	
	split_n_exec(low, up, numof, executable, sroot_id);			/*split numbers and create prover exe*/
	
	for(int i = 0; i < numof; i++)
		s -> fifo_id[i] = open(s -> fd_name[i], O_RDONLY);	/*non blocking open for created pipes*/

	Record temp = NULL;
	// struct pollfd* pollfd = malloc(sizeof(struct pollfd) * numof);		/*create info for polling*/
	// int flag = 0;														/*flag to indicate the end of data receiving*/
	int prime;
	double time;

	double* stats = malloc(sizeof(double)*numof);	/*array of doubles to store execution time for all childs*/

	for(int i = 0; i < numof; i++){
		while(1){
			read(s -> fifo_id[i], &prime, sizeof(int));
			read(s -> fifo_id[i], &time, sizeof(double));
			// printf("inner node %d received %d\n", pid, prime);
			if(prime != -1){
				temp = create_node(prime, time);	/*create a node and do insertion sort in list*/
				insert_node(r, temp);
			}
			else{
				stats[i] = time;
				break;
			}
		}
	}

	// for(int i = 0; i < numof; i++){
	// 	pollfd[i].fd = s -> fifo_id[i];			/*store all fifo ids						 */
	// 	pollfd[i].events = POLLIN;				/*POLLIN -> capable of receiving data		 */
	// 	pollfd[i].revents = 0;					/*if someone is ready to send, find id index */
	// }
	// int rt;
	// while(s -> flag != numof){						/*while there are processes capable of sending data*/	
	// 	// printf("here %d\n", pid);
<<<<<<< HEAD
	// 	rt = poll(pollfd, numof, -1);			/*-1 indicates blocking until someone finishes sending		*/
=======
	// 	rt = poll(pollfd, numof, -1);		/*-1 indicates blocking until someone finishes sending		*/
>>>>>>> refs/remotes/origin/main
	// 	prime = 0;								/*where the prime will be stored 							*/
	// 	time = 0.0;								/*where time will be stored 								*/
	// 	for(int i = 0; i < numof; i++){
	// 		if(pollfd[i].revents != 0){
	// 		if(pollfd[i].revents & POLLIN){
	// 			int rcv1;
	// 			pollfd[i].revents = 0;						/*re-initialize sending index 			*/
	// 			rcv1 = read(pollfd[i].fd, &prime, sizeof(int));
	// 			while (read(pollfd[i].fd, &time, sizeof(double)) > 0);

	// 			printf("process %d received %d %lf and i %d with rcv %d \n", pid, prime, time ,i, rcv1);
				
				// if(prime == -1){		when a process finished it sends -1 and execution time
	// 				s -> flag ++;
	// 				stats[i] = time;
	// 				pollfd[i].events = 0;
	// 				pollfd[i].fd = 0;				
	// 			}
	// 			else{
	// 				temp = create_node(prime, time);	/*create a node and do insertion sort in list*/
	// 				insert_node(r, temp);
	// 			}
	// 		}
	// 		else if(pollfd[i].revents & (POLLNVAL| POLLERR | POLLHUP)){
	// 			printf("%d, pollfd: %d, %d---------\n", pid, pollfd[i].fd, rt);
	// 			while(1){
	// 				read(pollfd[i].fd, &prime, sizeof(int));
	// 				read(pollfd[i].fd, &time, sizeof(double));
	// 				printf("prime:%d,  time:%lf-----------\n", prime, time);
	// 				if(prime == -1 || prime == 0){
	// 					s -> flag ++;
	// 					stats[i] = time;
	// 					pollfd[i].events = 0;
	// 					pollfd[i].fd = 0;
	// 					break;	
	// 				}
	// 			}
	// 		}}
	// 	}
	// }
	
	while(wait(NULL)>0);	/*wait until all childern are finished*/

	/*---------------Unlink all fifos----------------------*/
	for(int i = 0; i < numof; i++){
		close(s -> fifo_id[i]);
		unlink(s -> fd_name[i]);
	}

	/*---------------Begin sending data to root------------*/
	Record tem = r -> next;
	while(tem != NULL){
		tem = tem -> next;
		write(s -> fd_id, &(tem -> number), sizeof(int));
		write(s -> fd_id, &(tem -> time), sizeof(double));
	}
	prime = -1;
	time = 0.0;

	write(s -> fd_id, &prime, sizeof(int));
	write(s -> fd_id, &time, sizeof(double));

	for(int i = 0; i < numof; i++){
		write(s -> fd_id, &stats[i], sizeof(double));
	}

	close(s -> fd_id);
	/*---------------End of sending data to root-----------*/

	/* free all allocated memory */
	delete_status(s);
	destroy_records(r);
	free(stats);
	// free(pollfd);
	
	return 0;
}