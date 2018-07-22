#include <__C.h>

/*	Returns the modular inverse of 
 *	a in Zprime	*/

int modular_inverse( int a, int prime)
{	
	int res;

	for(int i = 0; i <=31; i++) {
		res = (a*i)%prime;
		if(res == 1) 
			return i;	
	}
}


int main(int argc,char *argv[])
{
	
	int sample = 15;
	int prime = 31;
	
	printf("%d\n",modular_inverse(sample, prime));
	return 0;
}
