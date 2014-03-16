#include "syscall.h"

void print(int i){

	SynchPutString("Coucou, je m'execute dans un thread");
	SynchPutInt(i);
	UserThreadExit();
}

int main(){
	UserThreadCreate(print,(void *) 7);
	

	char a = SynchGetChar();
	PutChar(a);
	return 0;
}