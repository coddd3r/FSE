#ifndef READ_KEY
#define READ_KEY

#include "fse.h"

int8 *read_key(char *prompt)
{
    char buf[256];
    int8 *current_pointer;
    int8 size;

    printf("%s ", prompt);
    fflush(stdout);
    memset(buf, 0, 256);
    // read from standard input file descriptor into buf
    int read_res = read(STDIN_FILENO, buf, 255);
    if (read_res < 1)
        assert_perror(errno);

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
    return current_pointer;
}

#endif