#include <__C.h>


/* Hypothetical example 
 * payload of 1 byte
 	 --------------------------------
	|ID-2bits| DATA-3bits| MAC-3bits|
	 --------------------------------
	Program to extract the fields from the message.
*/
int main(int argc,char *argv[])
{
	char ch, data, id, mac;
	ch = 111;	// id: 1, data: 5, mac: 6
	char fid = 192;
	char fdata = 56;
	char fmac = 7;
	
	id = ch & fid;
	id = ch >>6;

	data = (ch & fdata) ;
	data = data>>3;	
	mac = (ch & fmac);

	printf("ID: %d Data: %d MAC: %d\n", id, data, mac);	

	return 0;
}
