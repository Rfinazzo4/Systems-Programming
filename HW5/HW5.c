#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "fcntl.h"
#include "termios.h"

int main(int ac, char* args[])
{
	struct termios var; //terminal variable to check for start stop chars
	tcgetattr(0,&var);
	
	var.c_lflag &= ~ECHO;
	var.c_iflag |= IXON;

	var.c_cc[VSTART]='u';
	var.c_cc[VSTOP]='p';

	tcsetattr(0,TCSANOW,&var);
	//timer loop
	for (int i = atoi(args[1]);i!=0;i--){
		printf("%d\n",i);
		sleep(1);
	}
	
	exit(1);
}
