#include <stdio.h>

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

int main(void){
	int n;
    int flag;
    int a = 2;    
    while(1){
    	flag = -1;
    	printf("Give number to test:\n");
    	scanf("%d", &n);
        if(n == 0) break;
        flag = modular_pow(a, n-1, n);
        if(flag == 1) printf("PRIME\n");
        else printf("Composite\n");
    }
    printf("End of program...\n");
    return 0;
}