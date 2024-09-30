#ifndef READ_KEY
#define READ_KEY

#include "fse.h"
// #include "change_echo.h"
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

int8 *read_key(char *prompt)
{
    char buf[256];
    // char buf2[256];
    int8 *current_pointer;
    int8 size;

    printf("%s ", prompt);
    fflush(stdout);
    // disable output of printing onto terminal
    change_echo(false);
    
    memset(buf, 0, 256);
    // read from standard input file descriptor into buf
    int read_res = read(STDIN_FILENO, buf, 255);
    // char *fgets_res = fgets(buf2, 256, stdin);
    if (read_res < 1)
    {
        printf("ERROR WITH READ\n");
        exit(1);
    }

    // printf("\nyour input is: %s\n", fgets_res);
    // if (fgets_res == NULL)
    //     assert_perror(errno);

    size = (int8)strlen(buf);
    int8 last_pos = size - 1; // size of string without null pointer;
    current_pointer = (int8 *)&buf + last_pos;
    *current_pointer = 0;
    // *current_pointer = NULL;

    current_pointer = (int8 *)malloc(size);
    if (!current_pointer)
    {
        fprintf(stderr, "readkey malloc failed");
        assert(current_pointer);
    }

    strncpy((char *)current_pointer, buf, size - 1);
    //reenable keystrokes displaying on terminal
    change_echo(true);
    return current_pointer;
}

#endif