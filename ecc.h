#include <math.h>
#ifndef _ECC_H_
#define _ECC_H_

#define		NOTD	-0xf;

/*
			ecc.h  

   Library containing functions related to Elliptic Curve Cryptography.
   Written 2018, by Mouzakitis Nikolaos.
*/

/*
12/11/18	
 __________________________________________________________________________
|    FUNCTION :      inv					           |
|__________________________________________________________________________|
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

/*	
14/11/18
 _________________________________________________________________________
|     FUNCTION :      solve1						  |
|_________________________________________________________________________|

		Returns the integer solutions of equation in form
		y^2 = x^3+ax + b.
		Returns NOTD if not defined by D = -16(4a^3+27b^2) == 0,
		-1 if any other error occurs, and returns the number of 
		solutions as (x,y) written in the matrix p.
ARGUMENTS:
		a,b:	constants of the equation.
		p:	an array where in case of solutions will hold (x,y)'s.
*/

int  solve1(int a, int b, int p[][2],unsigned int search_size)
{
	int d, rv, x, cnt;
	double y1, y2, test;

	rv = NOTD;	
	cnt = 0;
	d = 16*(4*a*a*a + 27*b*b);

	if( d == 0)
		return rv;

	for (x = 0;x <= search_size; x++)
	{
		y1 = sqrt( (double)(x*x*x + a*x + b));	
		y2 = -sqrt((double)( x*x*x + a*x + b));	
		
		// Deciding whether y1/y2 are integers.

		test = floor(y1);
		
		if( (y1 - test) == 0 ) {
			p[cnt][0] = x;
			p[cnt][1] = y1;
			cnt++;
		}
		
		test = ceil(y2);

		if( (y2 - test) == 0 ) {
			p[cnt][0] = x;
			p[cnt][1] = y2;
			cnt++;
		}
		
	}
	if(!cnt)
		return -1;

	return cnt;	
}

//*************************************************************************

#endif
