/*Library that contains the thee functions that returns a prime*/

#pragma once /*include only once*/

#define TRUE 1
#define FALSE 0

int modular_pow(unsigned int base, unsigned int exponent, unsigned int mod); /*efficient power function*/

int prime_1(int n);	/*Search for divisors across all numbers*/

int prime_2(int n);	/*Search for divisors until square root of n*/

int my_prime(int n);/*Miller Rabin implementation*/