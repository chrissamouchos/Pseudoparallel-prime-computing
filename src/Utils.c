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

Range split(int n, int m, int NumOfChildren){
	int var = m - n + 1;
	int t_rem = var % NumOfChildren;
	int t_ran = var / NumOfChildren;
	Range r = range_create(t_ran, t_rem);
	return r;
}