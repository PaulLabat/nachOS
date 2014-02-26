#include "syscall.h"
void print(char c, int n)
{
	int i;

	char string[n];


	for (i = 0; i < n; i++) {
		//Ancien test		
		//PutChar(c+i);
		string[i] = c ;	
	}
	
	SynchPutString(string);
	PutChar('\n');
}
int
main()
{
	print('a',600);
	return 0;
	
}

