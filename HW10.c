
#include "stdio.h"
#include "signal.h"
#include "unistd.h"
#include "sys/types.h"
#include "stdlib.h"
#include "fcntl.h"
#include "termios.h"
#include "sys/time.h"
#include "utime.h"
#include "string.h"
#include "sys/wait.h"
#define oops( m, x ) { perror(m); exit(x); }
#define BUFF 128

static void parse( char* input, char* args[] );

int main(int argc, char * argv[])
{
    signal(SIGINT, SIG_IGN);
    char *command = "exit";
    char str[BUFF];
    int startWait, endWait, split, thepipe[2], newfd;
    
    int v = 1;
    
    while(v)
    {
        printf("$$ ");
        fgets (str, BUFF, stdin);

        parse(str, argv);
        
        
        if(argv[0] == NULL){}// handles ctrl-c
        else {
            v = strcmp(argv[0],command);
        
            if (v == 0)
                exit(1);
            else if(strcmp(argv[0], "cd") == 0){
                if(chdir(argv[1]) == 0){}
                else
                    perror("");
            }
            else{
                if(pipe(thepipe) == -1)
                    oops("Cannot create pipe", 1);
                if((split = fork()) == -1)
                    oops("Cannot fork", 2);
        
                switch(split){
                    case -1:
                        perror("");
                        break;
                    case 0:
                        if(!execvp(argv[0], argv))
                            perror("");
                        break;
                    default:
                        close(thepipe[1]);
                        if( dub2(thepipe[0],0) == -1)
                            oops("could not redirect", 3);
                        while (wait( &endWait ) != split);
                        printf(" return value %i\n", endWait);
                        break;
                }
            }
        }
    }

    
    
    return 0;
}
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