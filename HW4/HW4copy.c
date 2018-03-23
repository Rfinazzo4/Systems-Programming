#include "stdio.h"
#include "termios.h"
#include "fcntl.h"
#include "string.h"
#include "signal.h"
#include "stdlib.h"

void ctrl_c_handler( int );

int main(int ac, char* args[]){
    
}

    
    tty_mode(0);                                // save current mode
    set_cr_noecho_mode();                       // set -icanon -echo
    set_nodelay_mode();                         // noinput ==> EOF
    signal ( SIGINT, ctrl_c_handler );          // handle INT
    signal ( SIGQUIT, SIG_IGN );                // ignore QUIT signals
    response = get_response( ASK, TRIES );      // get some answer
    tty_mode(1);                                // reset original mode
    
    return response;
}


// put file descriptor 0 into chr-by-chr  mode and no echo mode
// uses bits in termios
void set_cr_noecho_mode()
{
    struct termios ttystate;
    
    tcgetattr( 0, &ttystate );                  // read curr settig
    ttystate.c_lflag &= ~ICANON;                // no buffering
    ttystate.c_lflag &= ~ECHO;                  // no echo either
    ttystate.c_cc[VMIN] = 1;                    // get 1 char at a time
    tcsetattr( 0, TCSANOW, &ttystate );         // install settings
}

// how == 0=> save current mode,    how == 1 => restore mode
// handles termios and fcntl flags
void tty_mode( int how )
{
    static struct termios original_mode;
    static int original_flags;
    static int stored = 0;
    
    if( how == 0 )
    {
        tcgetattr( 0, &original_mode );
        original_flags = fcntl( 0, F_GETFL );
        stored = 1;
    }
    else if ( stored )
    {
        tcsetattr( 0, TCSANOW, &original_mode );
        fcntl( 0, F_SETFL, original_flags );
    }
}

// called if SIGINT is detected - resets tty and exits
void ctrl_c_handler( int signum )
{
    tty_mode(1);
    exit(1);
}
