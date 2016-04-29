#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <stdlib.h>
#include <math.h>

// Brute force attack on a cipher text reading from a specified text in your pc.
// Developed by Mouzakitis Nikos.April 2016.
//IMPORTANT create your ciphertext and add the absolute path to open your own ciphertext to attack.


char *brute_force(char *line,int shift,char *decrypted)
{
	int i,emvl;
	int thesis;
	int lenght = strlen(line);
	for(i = 0; i < lenght; i++)
	{
		thesis = line[i] - 97 ; 

		if ( (thesis - shift) < 0 )
		{
			emvl = abs(thesis - shift);
		
			decrypted[i] = 97 + (26 - emvl);
		}
		else
			decrypted[i]  = (thesis - shift) +97;
	}



	return decrypted;
}

int main(void)
{

	FILE *fp;
	unsigned char ch,line[80],decrypted[80];
	int shift,op = 1;

	fp = fopen("/home/nikos/Documents/ProgrammingDevelopmentFolder/april/a13/ciphertext","r");

	if(fp == NULL)
	{
		perror("erron opening the file\n");
		exit(EXIT_FAILURE);
	}

	printf("Content of file is:\n");

	while( fgets(line,80,fp)  != NULL )
	{
		printf("%s",line);
	}


	while( op != 0)
	{

		printf("Enter the number of shift you wanna make to the ciphertext.\n");
		printf("(1 to 25) or enter -1 to exit\n");

		scanf("%d",&shift);

		if(shift == -1)
			exit(0);
		else
		{	
			printf("%s\n",brute_force(line,shift,decrypted));

		}
	
	}

	fclose(fp);

	return (0);
}
