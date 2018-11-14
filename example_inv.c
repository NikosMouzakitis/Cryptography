#include <stdio.h>
#include "ecc.h"


// Example of use inv function.
// Finding invert of a number in a finite field.

int main(int argc, char *argv[])
{

	int rv ;
	int test = 4;
	int ff = 19;
	rv = inv(4, ff);		

	if(rv == -1) {
		printf("No invert of %d in the finite field of %d\n", test, ff);
	}
	else {
		printf("Invert of %d in the finite field of %d : %d\n", test, ff, rv);
	}



	return(0);
}
