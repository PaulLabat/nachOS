#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"
#include "console.h"


static Semaphore *readAvail;
static Semaphore *writeDone;
static Semaphore *semaphoreSynchConsole;
static Semaphore *semaphoreSynchPut;
static Semaphore *semaphoreSynchGet;
static Semaphore *semaphoreSynchPut2;
static Semaphore *semaphoreSynchGet2;

static void ReadAvail(int arg) { readAvail->V(); }
static void WriteDone(int arg) { writeDone->V(); }

SynchConsole::SynchConsole(char *readFile, char *writeFile)
{
	readAvail = new Semaphore("read avail", 0);
	writeDone = new Semaphore("write done", 0);
	console = new Console(readFile, writeFile, ReadAvail, WriteDone, 0); // Completer, initialisation des sempahores a 0
	semaphoreSynchConsole = new Semaphore("SynchConsole", 1);
	semaphoreSynchPut = new Semaphore("SynchPut", 1);
	semaphoreSynchGet = new Semaphore("SynchGet", 1);
	semaphoreSynchPut2 = new Semaphore("SynchPut2", 1);
	semaphoreSynchGet2 = new Semaphore("SynchGet2", 1);
}

SynchConsole::~SynchConsole()
{
	delete console;
	delete writeDone;
	delete readAvail;
}

void SynchConsole::SynchPutChar(const char ch)
{
	semaphoreSynchConsole->P();
	/* Zone pour les <> autour des lettres
	if(ch != '\n'){
		console->PutChar('<');
		writeDone->P();
	}
	*/
	        
	console->PutChar(ch);
        writeDone->P();

    /* Zone pour <>    
	if(ch != '\n'){
		console->PutChar('>');
	    writeDone->P();
	}*/

	semaphoreSynchConsole->V();
}

char SynchConsole::SynchGetChar()
{

	readAvail->P ();
	return console->GetChar ();


}

void SynchConsole::SynchPutString(const char s[])
{
	semaphoreSynchPut->P();
	int i;
        for(i=0;i<MAX_STRING_SIZE && s[i]!='\0';i++) {
                synchconsole->SynchPutChar((char)s[i]);
        }
        synchconsole->SynchPutChar('\n');
    semaphoreSynchPut->V();    
}

void SynchConsole::SynchGetString(char *s, int n)
{
	semaphoreSynchGet->P();
	int i;
	char c;
	// attention a ne pas depasser la taille limite...
	for(i=0; i < n-1; i++){
		c = synchconsole->SynchGetChar();
		if(c == EOF || c == '\n'){
			break;
		}else{
			s[i] = c;
		}
	}
	s[i] = '\0';
	semaphoreSynchGet->V();
}

void SynchConsole::SynchPutInt(int n)
{
	semaphoreSynchPut2->P();
	char *s = new char[MAX_STRING_SIZE];
	snprintf(s, MAX_STRING_SIZE, "%d", n);
	synchconsole->SynchPutString(s);

	delete [] s;
	semaphoreSynchPut2->V();
}

void SynchConsole::SynchGetInt( int *n)
{
	semaphoreSynchGet2->P();
	int retour;
	// On travail sur des entiers...
	char *conversion = new char[12];
	SynchGetString(conversion, 12);
	sscanf(conversion, "%d", &retour);
	machine->WriteMem(*n, 4, retour);
	delete [] conversion;
	semaphoreSynchGet2->V();
}


#endif // CHANGED
