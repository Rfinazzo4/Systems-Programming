#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/time.h"
#include "sys/types.h"
#include "utime.h"

int main(int ac, char* args[])
{

	int in_fd, val;
	if (ac == 2){

		//sets the access and modification time of foo.txt to the current time if
		//foo.txt exists, creates it otherwise

		in_fd = open(args[1], O_WRONLY); //open file for writing
		if (in_fd==-1){			// check to see if file opened
			creat(args[1], O_WRONLY); //if not create a file
		}

	struct utimbuf para;
	val = utime(args[1], &para);

	}
	if (ac==3){


		//sets the access and modification time of foo.txt to the time given by user if
		//foo.txt exists, creates it otherwise

		in_fd = open(args[1], O_WRONLY); //open file for writing
		if (in_fd==-1){			// check to see if file opened
			creat(args[1], O_WRONLY); //if not create a file
		}

	struct utimbuf para;
	int val = atoi(args[2]); //turns input 
	para.modtime = val;
	val = utime(args[1], &para);
	}

}

