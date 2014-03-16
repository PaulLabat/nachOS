#ifdef CHANGED

typedef struct{
	int f;
	int arg;
}argThreadUser;

extern int do_UserThreadCreate(int f, int arg);
extern void do_UserThreadExit();

#endif //CHANGED