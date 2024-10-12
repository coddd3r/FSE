#ifndef READ_FILE
#define READ_FILE

#include "fse.h"
// char *read_file(FILE *f)
int8 *read_file(FILE *f)
{
    int8 *from;
    fseek(f, 0, SEEK_END);
    int length = ftell(f);
    fseek(f, 0, SEEK_SET);

    from = (int8 *)malloc(sizeof(char) * (length + 1));
    char c;
    int i = 0;
    while ((c = fgetc(f)) != EOF)
    {
        from[i] = (int8)c;
        i++;
    }
    from[i] = '\0';
    return from;
}



#endif