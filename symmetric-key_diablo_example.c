#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// symmetric - key encryption example.
// key is 'diablo'
//written by Mouzakitis Nikoloas,April 26 2016.

 void  encrypt(char *plaintext,int size)
 {
	int i;
	for(i = 0; i < size; i ++)
	{	if(plaintext[i] =='a')
			plaintext[i] = 'd';
		else if(plaintext[i] == 'b')
			plaintext[i] = 'i';
		else if(plaintext[i] == 'c')
			plaintext[i] = 'a';
		else if(plaintext[i] == 'd')
			plaintext[i] = 'b';
		else if(plaintext[i] == 'e')
			plaintext[i] = 'l';
		else if(plaintext[i] == 'f')
			plaintext[i] = 'o';
		else if(plaintext[i] == 'g')
			plaintext[i] = 'c';
		else if(plaintext[i] == 'h')
			plaintext[i] = 'e';
		else if(plaintext[i] == 'i')
			plaintext[i] = 'f';
		else if(plaintext[i] == 'j')
			plaintext[i] = 'g';
		else if(plaintext[i] == 'k')
			plaintext[i] = 'h';
		else if(plaintext[i] == 'l')
			plaintext[i] = 'j';
		else if(plaintext[i] == 'm')
			plaintext[i] = 'k';
		else if(plaintext[i] == 'n')
			plaintext[i] = 'm';
		else if(plaintext[i] == 'o')
			plaintext[i] = 'n';
		else if(plaintext[i] == 'p')
			plaintext[i] = 'p';
		else if(plaintext[i] == 'q')
			plaintext[i] = 'q';
		else if(plaintext[i] == 'r')
			plaintext[i] = 'r';
		else if(plaintext[i] == 's')
			plaintext[i] = 's';
		else if(plaintext[i] == 't')
			plaintext[i] = 't';
		else if(plaintext[i] == 'u')
			plaintext[i] = 'u';
		else if(plaintext[i] == 'v')
			plaintext[i] = 'v';
		else if(plaintext[i] == 'w')
			plaintext[i] = 'w';
		else if(plaintext[i] == 'x')
			plaintext[i] = 'x';
		else if(plaintext[i] == 'y')
			plaintext[i] = 'y';
		else if(plaintext[i] == 'z')
			plaintext[i] = 'z';										
	}


 }
void decrypt(char *plaintext,int size)
{
	int i;
	for(i = 0; i < size; i ++)
	{	if(plaintext[i] =='a')
			plaintext[i] = 'c';
		else if(plaintext[i] == 'b')
			plaintext[i] = 'd';
		else if(plaintext[i] == 'c')
			plaintext[i] = 'g';
		else if(plaintext[i] == 'd')
			plaintext[i] = 'a';
		else if(plaintext[i] == 'e')
			plaintext[i] = 'h';
		else if(plaintext[i] == 'f')
			plaintext[i] = 'i';
		else if(plaintext[i] == 'g')
			plaintext[i] = 'j';
		else if(plaintext[i] == 'h')
			plaintext[i] = 'k';
		else if(plaintext[i] == 'i')
			plaintext[i] = 'b';
		else if(plaintext[i] == 'j')
			plaintext[i] = 'l';
		else if(plaintext[i] == 'k')
			plaintext[i] = 'm';
		else if(plaintext[i] == 'l')
			plaintext[i] = 'e';
		else if(plaintext[i] == 'm')
			plaintext[i] = 'n';
		else if(plaintext[i] == 'n')
			plaintext[i] = 'o';
		else if(plaintext[i] == 'o')
			plaintext[i] = 'f';
		else if(plaintext[i] == 'p')
			plaintext[i] = 'p';
		else if(plaintext[i] == 'q')
			plaintext[i] = 'q';
		else if(plaintext[i] == 'r')
			plaintext[i] = 'r';
		else if(plaintext[i] == 's')
			plaintext[i] = 's';
		else if(plaintext[i] == 't')
			plaintext[i] = 't';
		else if(plaintext[i] == 'u')
			plaintext[i] = 'u';
		else if(plaintext[i] == 'v')
			plaintext[i] = 'v';
		else if(plaintext[i] == 'w')
			plaintext[i] = 'w';
		else if(plaintext[i] == 'x')
			plaintext[i] = 'x';
		else if(plaintext[i] == 'y')
			plaintext[i] = 'y';
		else if(plaintext[i] == 'z')
			plaintext[i] = 'z';										
	}






}
int main(void)
{
	int lenght= 1;
	char e[1024];
	strcpy(e,"securedmessage");
	
	lenght = strlen(e);
	printf("We will use the key: 'diablo' \n");


	printf("lenght of message is : %d\n",lenght);
	printf("message is : %s\n", e);
	encrypt(e,lenght);
	printf("Encrypted :  %s\n",e);
	decrypt(e,lenght);
	printf("Decrypted :  %s\n",e);

	return (0);
}
