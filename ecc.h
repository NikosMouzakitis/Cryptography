#ifndef _ECC_H_
#define _ECC_H_

/*
   Written 2018, by Mouzakitis Nikolaos.
	
*/


//*************************************************************************
/*	
FUNCTION :      inv
		Returns the inverse of input(in) in the space Zp.
		Returns -1 if inverse doesn't exist.
ARGUMENTS:
		in: is the number we are intending to find the inverse.
		p:  is the possitive integer, that the space is modulo.(Zp)
			f.e: p = 7, Z7 = {0,1,2,3,4,5,6}.
*/

int inv(int in, int p)
{

	for( int i = 1; i < p; i++)
		if( ((in*i)%p) == 1)
			return i;
	return (-1);
}
//*************************************************************************










#endif
