#include "syscall.h"

int
main()
{
	int s;
	SynchGetInt(&s);
	SynchPutInt(s);
	return 0;
}