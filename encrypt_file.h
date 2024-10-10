
#ifndef ENCRYPT_FILE
#define ENCRYPT_FILE

#include "fse.h"
void encrypt_file(char *in_file, char *out_file, Arcfour *rc4, char *r_opt, char *w_opt)
{
    FILE *f = fopen(in_file, r_opt);

    if (f == NULL)
    {
        printf("OPEN FAILED");
        assert_perror(errno);
    }

    int8 *from;
    int8 *encrypted;
    fseek(f, 0, SEEK_END);
    int length = ftell(f);
    fseek(f, 0, SEEK_SET);
    printf("length of file is: %d \n", length);
    from = (int8 *)malloc(sizeof(char) * (length + 1));
    size_t read_res = fread(from, sizeof(int8), length, f);

    if (read_res < 2)
    {
        printf("READ ERROR");
        exit(1);
    }
    
    if (strcmp(r_opt, "rb") == 0)
    {
        printf("BINARY INPUT:");
        printbin(from, length);
    }
    else
        printf("ORG TEXT ' %s '\n", from);
    int16 stext = length;
    encrypted = rc4encrypt(rc4, (int8 *)from, stext);
    if (strcmp(r_opt, "rb") == 0)
        printf("DECRYPTED STR: '%s'", encrypted);
    else
    {
        printf("ENCRYPTED BIN STR:");
        printbin(encrypted, length);
    }


    FILE *output_file_p = fopen(out_file, w_opt);
    size_t w_res = fwrite(encrypted, sizeof(int8), stext, output_file_p);
    printf("num bytes written:%d \n", (int)w_res);
    
    rc4uninit(rc4);
    free(from);
    fclose(f);
}
#endif