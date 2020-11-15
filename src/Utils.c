/*File that contains source code of various functions*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>		/* For file descriptors */
#include <sys/stat.h>
#include <string.h>

#include "Utils.h"

/*define default values*/
#define TRUE 1
#define FALSE 0

/*----------------- VARIOUS FUNCTIONS-------------------*/
void red(){
 	printf("\033[1;31m");	/*bold red*/
}

void green(){
	printf("\033[1;32m");	/*bold green*/
}

void cyan(){
	printf("\033[1;36m");	/*bold cyan*/
}

void reset(){
	printf("\033[0m");		/*reset color*/
}

void usage(const char* command){		/*Print expected command format*/
	cyan();
	printf("%s -l <lower bound> -u <upper bound> -w <Number of Children>\n",command);
	reset();
}
/*----------------- END OF FUNCTIONS--------------------*/

/*----------------START OF RANGE------------------------*/
Range range_create(int range, int remainder){
	Range r = malloc(sizeof(range));	/*allocate memory for struct*/
	
	/*assign given values*/
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
	int t_rem = var % NumOfChildren;	/*find remainder*/
	int t_ran = var / NumOfChildren;	/*find range 	*/
	Range r = range_create(t_ran, t_rem);
	return r;
}

void split_n_exec(int n, int m, int NumOfChildren, char* executable){
	pid_t pid;						/*Process id 									*/
	int status, fd;					/*Status to check validity, fd = file descriptor*/
	int flag = FALSE;				/*flag to check existence of remainder 			*/

	/*store values to strings to pass arguments to exec* */
	char* up = malloc(sizeof(int));
	char* low = malloc(sizeof(int));
	char* numof = malloc(sizeof(int));
	char* is = malloc(sizeof(int));
	char* nameofexec = malloc(sizeof(char)*(strlen(executable)-2));

	sprintf(numof, "%d", NumOfChildren);	/*convert to string*/

	for(int i = 0; i < strlen(executable)-2; i++){	/*dynamically store only the name of executable*/
		nameofexec[i] = executable[i+2];
	}

	Range r = find_range(n, m, NumOfChildren);	/*Compute range and remainder*/
	if(m - n + 1 < NumOfChildren){
		red();
		perror("Wrong input, NumOfChildren too big\n");
		reset();
		exit(-1);
	}
	if(r -> remainder != 0) flag = TRUE;	/*flag to show existence of */
	int temp = n;
	/*Create NumOfChildren inner - nodes with the respective pipes*/
	for(int i = 0; i < NumOfChildren; i++){
		sprintf(is, "%d", i);		/*pass i as argument for process identification	*/
		if((pid = fork()) < 0){		/*Fork validity check 							*/
			red();
			perror("Fork error");
			reset();
			exit(1);
		}
		if(pid == 0){  										/*Children stuff 		*/	
			temp = i*(r->range) + n;
			sprintf(low, "%d", temp);
			if((i == NumOfChildren - 1) && (flag == TRUE)){		/*Last child with existing remainder*/
				m = temp + r-> remainder + r->range;
				sprintf(up, "%d", m);
			}
			else if((i == NumOfChildren - 1 && flag == FALSE)||(i != NumOfChildren - 1)){	/*any other case*/
				m = temp + r -> range;
				sprintf(up, "%d", m);
			}
			if((status = execl(executable, nameofexec, low, up, numof, is, NULL)) < 0){	/*Execl validity check 	*/
				red();
				perror("Execl error");
				reset();
				exit(2);
			}
		}
	}

	range_delete(r); /*destroy range struct */

	/*free all allocated memory				*/
	free(up);
	free(low);
	free(nameofexec);
	free(numof);
	free(is);
}