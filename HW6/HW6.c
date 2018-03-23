#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "fcntl.h"
#include "termios.h"
#include "signal.h" 

int j=2;
int p=0;

void handler(int);

int main(int ac, char* args[])
{
    signal(SIGINT, &handler); //install the handler
    struct termios original; //terminal variable for orginal mode
    static int original_flags;
    struct termios variable;  //to check for start stop chars
    
    tcgetattr(0,&original); //get dirver settings
    original_flags = fcntl(0, F_GETFL); //get orginal flags
    tcgetattr(0, &variable); //new driver settings to edit
    variable.c_lflag &=~ECHO; //turn off echo bit
    tcsetattr(0,TCSANOW,&variable); //update driver settings
    
    int i =atoi(args[1]); //number to start timer on
    
    while (p==0 && i!=0){
        printf("%d\n",i);
        sleep(1);
        i--;
        while (p==1){}
    }
    
    //reset erminal modes and driver settings
    tcsetattr( 0, TCSANOW, &original);
    fcntl( 0, F_SETFL, original_flags );
    
    exit(3);
}

void handler(int signum){
    j++;
    if ((j%2)==0){
        p =0;
    }
    else {p = 1;}
}