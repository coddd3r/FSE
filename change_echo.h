/* change echo to not print out input*/
#ifndef CHANGE_ECHO

#include "fse.h"
void change_echo(bool enabled)
{
    /*int tcgetattr(int fd, struct termios *termios_p);

       int tcsetattr(int fd, int optional_actions,
                     const struct termios *termios_p);*/
    /*
            
        struct termios old_tio, new_tio;
        tcgetattr(STDIN_FILENO, &old_tio);
        new_tio = old_tio;
        new_tio.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
    */
    
    struct termios *t;
    t = (struct termios *)malloc(sizeof(struct termios));
    tcgetattr(0, t);
}

#endif // !CHANGE_ECHO