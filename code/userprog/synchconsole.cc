#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"
#include "console.h"


static Semaphore *readAvail;
static Semaphore *writeDone;

static void ReadAvail(int arg) { readAvail->V(); }
static void WriteDone(int arg) { writeDone->V(); }

SynchConsole::SynchConsole(char *readFile, char *writeFile)
{
	readAvail = new Semaphore("read avail", 0);
	writeDone = new Semaphore("write done", 0);
	console = new Console(readFile, writeFile, ReadAvail, WriteDone, 0); // Completer, initialisation des sempahores a 0
}

SynchConsole::~SynchConsole()
{
	delete console;
	delete writeDone;
	delete readAvail;
}

void SynchConsole::SynchPutChar(const char ch)
{

	console->PutChar (ch);
	writeDone->P();
	
	if (ch != '\n' && ch != EOF){	// On affiche pas les caractères retour a la ligne et end of file
		console->PutChar ('>');	
		writeDone->P ();	// Attente de la fin du write du >
	}
}

char SynchConsole::SynchGetChar()
{
	readAvail->P ();
	char ch = console->GetChar ();

	  
	if (ch != '\n' && ch != EOF){	// On affiche pas les caractères retour a la ligne et end of file
	  	console->PutChar ('<');	
	  	writeDone->P ();	// Attente de la fin du write du <
	}
	
	return ch;
}

void SynchConsole::SynchPutString(const char s[])
{
// ...
}

void SynchConsole::SynchGetString(char *s, int n)
{
// ...
}


#endif // CHANGED
