/*File that contains source code of various functions*/
#include <stdio.h>
#include <stdlib.h>

#include "Utils.h"

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