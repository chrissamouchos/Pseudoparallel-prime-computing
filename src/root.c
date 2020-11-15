/*This is the master process, that all data is returned in order to be printed /
/ via condole. The user will able to see some simple statistics apart from the /
/ results. n,m are the boundaries that the program will search for primes	  */

#include <stdio.h>

#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

#include "Utils.h"


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

	/*--------------Create inner nodes----------------------------*/
	char* executable = "./inner_node";
	split_n_exec(n, m, NumOfChildren, executable); /*Split n exec innernodes.*/

	/*--------------End of Creation-------------------------------*/

	wait(NULL);

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