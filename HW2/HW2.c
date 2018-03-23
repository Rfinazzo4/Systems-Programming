#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"

#define BUFFERSIZE  4096

int main(int ac, char* args[])
{
	int in_fd, n_chars;
	char buf[BUFFERSIZE];
	if (ac!=2){ 		//if not enough arguments given then send synopsis message
		printf("prt  FILENAME\n");
		exit(1); 	//exit the program
	}
	else{
		in_fd = open(args[1], O_RDONLY);	//Open file for reading
		if (in_fd==-1){			//check open status	
			printf("%s file cannot be open.\n", args[1]);
			exit(1);		//exit if file does not open
		}	
			
		while (( n_chars = read( in_fd, buf, BUFFERSIZE ) ) > 0 ){
		}
		printf("%s", buf);
		close(in_fd);
   		return 0;

	}

}
