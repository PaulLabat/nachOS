#include "syscall.h"

int
main()
{
	char s = SynchGetChar();
	PutChar(s);
	return 0;
}