/*File that contains source code of various functions*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>		/* For file descriptors */
#include <sys/stat.h>
#include <string.h>

#include "Utils.h"

#define TRUE 1
#define FALSE 0

/*----------------- VARIOUS FUNCTIONS-------------------*/
void red(){
 	printf("\033[1;31m");
}

void green(){
	printf("\033[1;32m");
}

void cyan(){
	printf("\033[1;36m");
}

void reset(){
	printf("\033[0m");
}

void usage(const char* command){		/*Print expected command format*/
	cyan();
	printf("%s -l <lower bound> -u <upper bound> -w <Number of Children>\n",command);
	reset();
}
/*----------------- END OF FUNCTIONS--------------------*/

/*----------------START OF RANGE------------------------*/
Range range_create(int range, int remainder){
	Range r = malloc(sizeof(range));
	r -> range = range;
	r -> remainder = remainder;
	return r;
}

void range_change(Range r, int range, int remainder){
	r -> range = range;
	r -> remainder = remainder;
}

void range_delete(Range r){
	free(r);
}
/*----------------END OF RANGE--------------------------*/

Range find_range(int n, int m, int NumOfChildren){
	int var = m - n;
	int t_rem = var % NumOfChildren;
	int t_ran = var / NumOfChildren;
	Range r = range_create(t_ran, t_rem);
	return r;
}

void split_n_exec(int n, int m, int NumOfChildren, char* executable){
	pid_t pid;						/*Process id 									*/
	int status, fd;					/*Status to check validity, fd = file descriptor*/
	int flag = FALSE;
	char* up = malloc(sizeof(int));
	char* low = malloc(sizeof(int));
	char* numof = malloc(sizeof(int));

	sprintf(numof, "%d", NumOfChildren);

	char* nameofexec = malloc(sizeof(char)*(strlen(executable)-2));
	for(int i = 0; i < strlen(executable)-2; i++){
		nameofexec[i] = executable[i+2];
	}

	Range r = find_range(n, m, NumOfChildren);
	if( m - n + 1 < NumOfChildren){
		red();
		printf("Wrong input, NumOfChildren too big\n");
		reset();
		exit(-1);
	}
	if(r -> remainder != 0) flag = TRUE;
	int temp = n;
	/*Create NumOfChildren inner - nodes with the respective pipes*/
	for(int i = 0; i < NumOfChildren; i++){
		
		if((pid = fork()) < 0){		/*Fork validity check*/
			red();
			perror("Fork error");
			reset();
			exit(1);
		}
		if(pid == 0){  															/*Children stuff 		*/	
			temp = i*(r->range) + n;
			sprintf(low, "%d", temp);
			if((i == NumOfChildren - 1) && (flag == TRUE)){
				m = temp + r-> remainder + r->range;
				sprintf(up, "%d", m);
			}
			else if((i == NumOfChildren - 1 && flag == FALSE)||(i != NumOfChildren - 1)){
				m = temp + r->range;
				sprintf(up, "%d", m);
			}
			if((status = execl(executable, nameofexec, low, up, numof, NULL)) < 0){	/*Execl validity check 	*/
				red();
				perror("Execl error");
				reset();
				exit(2);
			}
		}
	}
	range_delete(r);
	free(up);
	free(low);
	free(nameofexec);
	free(numof);
}