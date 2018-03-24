#include <__C.h>
#include <math.h>

/* Hypothetical example 
 * with a payload of 1 byte
		LEVEL 1 SECURITY 
	 --------------------------------
	|ID-2bits| DATA-3bits| MAC-3bits|
	 --------------------------------

 		LEVEL 2  SECURITY 
	 --------------------------------
	|ID-2bits| DATA-2bits| MAC-4bits|
	 --------------------------------
	

	Program to extract the fields from the message
	and a demostration of switch between two different
	security levels of interpetation of same message.


	Usage:	 
		
		

*/

/*	Globals	*/

int mac_min = 0;
int mac_max = 2;
int id_min = 6;
int id_max = 7;
int data_min = 3;
int data_max = 5;

char fid ;	/* Masks for id, data and Mac	*/
char fdata; 
char fmac ;

//	@filter.
// calulation of an integer that
// then should be ANDed with the 
// number. mix to max: field of interest.

int filter(int min, int max) {
	
	int res, i;
	res = 0;

	for ( i = min; i <= max; i++)
		res += (int) pow(2.0,(double)i);

	return res;

}

//	@setSecurity
//	changes the Security Level based on argument
//	provided.Sets different limits on bitfields
//	so when mask applied fields interpreted into
//	the desired way.

void setSecurity(int level) {
	
	switch(level) {
	
		case 1:
			mac_min = 0;
			mac_max = 2;	
			id_min = 6;
			id_max = 7;
			data_min = 3;
			data_max = 5;
			break;
		case 2:
			mac_min = 0;
			mac_max = 3;
			id_min = 6;
			id_max = 7;
			data_min = 4;
			data_max = 5;
			break;

		default:
			printf("Usage Error. Security Level remains as it is\n");
			break;
	}

	fid = filter(id_min, id_max);
	fdata = filter(data_min, data_max);
	fmac = filter(mac_min, mac_max);

}

//	@ext_field
//extracts the value as an integer
//from the field of interest.

int ext_field(char *val, char *mask, int shift) {
	
	int ret;

	ret = (*val) & (*mask);
	ret = ret >> shift;
	return ret;
}

void readMsg(char *payload, char * id, char *data, char *mac) {


	*id = ext_field(payload, &fid, id_min);
	*data = ext_field(payload, &fdata, data_min);
	*mac = ext_field(payload, &fmac, mac_min);

}

int main(int argc,char *argv[])
{
	char payload, data, id, mac;
	payload = 110;	// id: 1, data: 5, mac: 6
	
	setSecurity(1);	
	readMsg(&payload, &id,&data, &mac);

	printf("ID: %d Data: %d MAC: %d\n", id, data, mac);	
	
	setSecurity(2);
	readMsg(&payload, &id,&data, &mac);
	
	printf("ID: %d Data: %d MAC: %d\n", id, data, mac);	

	return 0;
}
