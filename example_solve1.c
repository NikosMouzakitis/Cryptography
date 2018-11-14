#include <stdio.h>
#include "ecc.h"


// Example of use solve1 function.
// Finding solutions of given constants
// a, b withing a finite field(Zp).

int main(int argc, char *argv[])
{

	int p[100][2];
	int rv ;
	
	int a = -1;
	int b = 1;

	rv = solve1(a, b, p,3000);		

	if(rv) {

		printf("Found %d solutions.\n", rv);
		
		for(int i = 0; i < rv; i++)
			printf("%d %d\n",p[i][0], p[i][1]);

	}
	else {

		printf("No integer solutions for a=%d b= %d .\n", a,b);

	}



	return(0);
}
