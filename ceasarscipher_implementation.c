#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <math.h>

//Encryption and decryption on Ceasar's cipher with initialized shift,by Mouzakitis Nikoloas.April 2016.

void encrypt(char *message,char *encrypted,int shift)
{
	printf("%d\n",strlen(message));
	int i;
	int thesis;
	for(i = 0; i < strlen(message); i ++)
	{
		thesis = message[i]-97 ;

		encrypted[i] = (thesis + shift) % 26 + 97 ;
	
	}

}

void decrypt(char *encrypted,char *message,int shift)
{

	int i;
	int thesis;
	int emvl;

	for(i = 0; i <strlen(encrypted); i++)
	{

		thesis = encrypted[i] - 97;
		if(thesis - shift < 0 )
		{
			emvl = abs(thesis - shift);

			printf("%d\n",emvl);
			message [i] = 97 + (26 - emvl );
		}
		else
			message[i] =( thesis - shift) % 26 + 97;

	}

}

int main(void)
{
	int shift;
	unsigned char message[100],encrypted[100],decrypted[100];

	printf("Quick encryption and decryption using the Ceasar's cipher\n");
	printf("Enter your swift value:\n");
	scanf("%d",&shift);
	printf("Enter your message\n");

	scanf("%s",message);	
	
	printf("You typed: %s\n",message);
	
	encrypt(message,encrypted,shift);

	printf("Encrypted: %s\n",encrypted);

	decrypt(encrypted,message,shift);

	printf("Decrypted: %s\n",message);

	
	return 0;
}
