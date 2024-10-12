/* change echo to not print out input*/
#ifndef CHANGE_ECHO

#include "fse.h"
void change_echo(bool enable)
{   
    struct termios term;
    // t = (struct termios *)malloc(sizeof(struct termios));
    tcgetattr(STDIN_FILENO, &term);

    if (enable)
        term.c_lflag |= ECHO; // will enable echo
    else
        term.c_lflag &= ~ECHO; // will set all bits to zero, disable echo

    tcsetattr(STDIN_FILENO, 0, &term);
}

#endif // !CHANGE_ECHO