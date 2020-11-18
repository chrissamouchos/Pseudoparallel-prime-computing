# include <stdio.h>
# include <stdlib.h>
#include <math.h>

#include "Find_primes.h"

int modular_pow(unsigned int base, unsigned int exponent, unsigned int mod){
  int result = 1;
  base = base % mod;                              // Update x if it is more than or  equal to p
  if (base == 0)                                  // In case x is divisible by p;
    return 0;

  while(exponent > 0){
    	if (exponent & 1)                             //This action is equivalent to exponent % 2
      		result = (result*base) % mod;

    	exponent = exponent >> 1;                     //This action is equivalent to exponent = exponent/2
    	base = (base*base) % mod;
    }
    return result;
}

int prime_1(int n){
	int i;
	if(n == 1)	return FALSE;
	for(i = 2; i < n; i++)
		if( n % i == 0)
			return FALSE;
	return TRUE;
}

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
	int flag = -1;
	/*to be fixed for big numbers, set default a = 2*/
	int a = 2;
	
	if(n % 2 == 0) return FALSE;
	flag = modular_pow(a, n-1, n);
	if(flag == 1) return TRUE;
	else return FALSE;
}