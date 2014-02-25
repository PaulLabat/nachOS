#include "syscall.h"

int
main()
{
	char s [512];
	SynchGetString(s,12);
	SynchPutString(s);
	return 0;
}
