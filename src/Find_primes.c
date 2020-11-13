# include <stdio.h>
# include <stdlib.h>
#include <math.h>

#include "Find_primes.h"

#define TRUE 1
#define FALSE 0

int prime_1(int n){
	int i;
	if(n == 1)	return FALSE;
	for(i = 2; i < n; i++)
		if( n % i == 0)
			return FALSE;
	return TRUE;

int prime_2(int n){
	int i = 0, limitup = 0;
	limitup = (int) sqrt((float)n);
	if(n == 1) return FALSE;
	for (i = 2; i <= limitup; i++)
		if(n % i == 0)
			return FALSE;
	return TRUE;
}

int my_prime(int n){
	
}