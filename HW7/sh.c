#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "fcntl.h"
#include "termios.h"
#include "string.h"
#include "sys/wait.h"

#define BUFFER 128

static void parse( char* input, char* args[] )
{
    int i = 0;
    
    // fgets reads the \n, so overwrite it
    input[strlen(input)-1] = '\0';
    
    // get the first token
    args[i] = strtok( input, " " );
    
    // get the rest of them
    while( ( args[++i] = strtok(NULL, " ") ) );
}

int main(int ac, char* args[]){
	signal(SIGINT, SIG_IGN);
	char string[BUFFER];
	int strwait, endwait, forkresult;
	int status=1;
	char* exitcmd = "exit";

	do{
		printf(":) "); 
		fgets(string, BUFFER, stdin); //get the input
		parse(string, args); //parse the input
	
		if (args[0] ==NULL){} //handler for ctrl-c
		else{
			status =strcmp(args[0],exitcmd);
		
			if (status==0){
				exit(1);
			}
			else if(strcmp(args[0], "cd")==0){
				if(chdir(args[1]) ==0){}
				else{
					perror("");
				}
			}
			else{
				forkresult=fork();
				
				switch(forkresult){
				case -1:
					perror("cannot fork");
					exit(2);
				case 0:
					if(!execvp(args[0],args)){							perror("");
					}
					break;
				default: 
					while(wait(&endwait) != forkresult);
					printf("return value: %i\n", endwait);
					break;
				}
				
			}
		}

	}while(status);

}
