#include "syscall.h"


void print(int i){

	SynchPutString("Coucou, je m'execute dans un thread");
	SynchPutInt(i);

	//char z = SynchGetChar();
	//PutChar(z);

	UserThreadExit();
}

int main(){

	UserThreadCreate(print,(void *) 7);
	UserThreadCreate(print,(void *) 8);
	//char a = SynchGetChar();
	//PutChar(a);
	SynchPutString("Je suis le thread principal !");
	return 0;
}