#include "syscall.h"
void print(char c, int n)
{
	int i;

	char string[n];


	for (i = 0; i < n; i++) {
		//Ancien test		
		//PutChar(c+i);
		string[i] = c + i;	
	}
	
	PutString(string);
	PutChar('\n');
}
int
main()
{
	print('a',30);
	Halt();
}

