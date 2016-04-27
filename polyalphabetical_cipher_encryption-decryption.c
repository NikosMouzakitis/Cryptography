#include <stdio.h>
#include <string.h>
#include <ncurses.h>
//--Polyalphabetical encryption/decryption implementation,by Mouzakitis Nikolaos,27 April 2016.
//---- -------------------  POLYALPHABETICAL CIPHER -------------------------------

void poly_encrypt(unsigned char *plaintext,unsigned char *key,unsigned char *cipher)
{

	unsigned char alpha_t[]="abcdefghijklmnopqrstuvwxyz";
	int i,j = 0;
	int shift,rem;
	for(i = 0;plaintext[i] != '\0'; i++)
	{
		if(plaintext[i] == ' ' )
			cipher[i] = plaintext[i];		
		else 
		{
		
			shift = (key[j] %97) +1;
			printf("%d\n",shift);
			cipher[i] = plaintext[i] + shift ;
		
			if(cipher[i] > 122)
			{
				rem = cipher[i] - 122 ;
				cipher[i] = alpha_t[rem-1];


			}

			j++;
		
			if(j == strlen(key))
				j=0;
		}
	}
}

void poly_decrypt(unsigned char *cipher,unsigned char *key,unsigned char *plaintext)
{
	unsigned char  alpha_t[]="abcdefghijklmnopqrstuvwxyz";
	int i,j = 0;
	int shift,rem;	
	for(i = 0;cipher[i] != '\0'; i++)
	{
		if(cipher[i] == ' ' )
			plaintext[i] = cipher[i];		
		else 
		{
		
			shift = (key[j] %97) +1;
			printf("%d\n",shift);
			cipher[i] = plaintext[i] - shift ;
		
			if(cipher[i] < 97)
			{
				rem = 97 -cipher[i];
				cipher[i] = alpha_t[26 -rem];


			}

			j++;
		
			if(j == strlen(key))
				j=0;
		}
	}



}


int main(void)
{
	unsigned char plaintext[40],key[5],cipher[40] ;

	printf("Enter plaintext:\n");
	gets(plaintext);
	
	printf("Enter the key:\n");
	gets(key);

	poly_encrypt(plaintext,key,cipher);

	printf("Encrypted:%s\n",cipher);
	
	poly_decrypt(cipher,key,plaintext);

	printf("Decrypted:%s\n",plaintext);

	return (0);
}
