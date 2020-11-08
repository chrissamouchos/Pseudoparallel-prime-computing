/*This is the master process, that all data is returned in order to be printed /
/ via condole. The user will able to see some simple statistics apart from the /
/ results. n,m are the boundaries that the program will search for primes	  */

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

#define TRUE 1
#define FALSE 0

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
				usage(argv[0]);
				return 1;
		}	
	}
	/*---------------End of Options Parsing----------------*/


	if(n > m){			/*Check if given numbers are legit*/
		red();
		printf("Error: Lower bound greater than upper bound!\n");
		reset();
		return(2);
	}
	else{
		cyan();			/*Print start execution message	  */
		printf("Executing ./myprime within [%d,%d] with %d NumOfChildren\n", n, m, NumOfChildren);
		reset(); 
	}

	pid_t pid;						/*Process id 									*/
	int status, fd;					/*Status to check validity, fd = file descriptor*/
	int flag = FALSE;
	char* up = malloc(sizeof(int));
	char* low = malloc(sizeof(int));

	Range r = split(n, m, NumOfChildren);
	if(r -> remainder != 0) flag = TRUE;

	/*Create NumOfChildren inner - nodes with the respective pipes*/
	for(int i = 1; i < NumOfChildren; i++){
		
		if((pid = fork()) < 0){		/*Fork validity check*/
			red();
			perror("Fork error");
			reset();
			exit(1);
		}
		if(pid == 0){  															/*Children stuff 		*/
			printf("Creating inner_node...\n");
			
			n = i*(r->range);
			sprintf(low, "%d", n);
			
			if((i == NumOfChildren - 1) && (flag == TRUE)){
				m = n + r->range + r-> remainder;
				sprintf(up, "%d", m);
			}
			else{
				m = n + r->range;
				sprintf(up, "%d", m);
			}
			if((status = execl("./inner_node", "inner_node", low, up, NULL)) < 0){	/*Execl validity check 	*/
				red();
				perror("Execl error");
				reset();
				exit(2);
			}
		}
	}
	wait(NULL);

	free(up);
	free(low);
	// status = mkfifo(root_node, 0666);
	// if(status < 0) perror("Pipe creation error");

	// char* buf = malloc(sizeof(char)*20);
	// buf = "Hello from parent!\n";

	
	// else{
	// 	printf("I am parent!\n");
	// 	if(fd = open("root_node", O_WRONLY) < 0)
	// 		perror("Error open pipe");
	// 	if(fd = write(fd, buf, strlen(buf)) != strlen(buf))
	// 		perror("Error write in pipe");
	// 	wait(NULL);
	// }
	// close(fd);
	printf("End of root\n");

	return 0;
}