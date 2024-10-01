#include "fse.h"
#include "secure_rand.h"
#include "read_key.h"
#include "read_file.h"
#include "encrypt_file.h"


void printbin(int8 *text, const int16 size)
{
    int16 i;
    int8 *p;

    assert(size > 0); // assert - abort the program if assertion is false
    for (i = size, p = text; i > 0; i--, p++)
    {
        if (!(i % 2))
            printf(" ");
        printf("%.02x", *p);
    }
    printf("\n");
    return;
}

int main(int argc, char *argv[])
{
    Arcfour *rc4;
    int8 *in_file;
    int8 *out_file;
    int infd;
    int outfd;
    int8 *key;
    int16 key_size;
    int16 pad_size;
    // int8 *from;
    // int8 *encrypted;

    if (argc < 3)
    {
        fprintf(stderr, "Please enter inout and output files \n Usage: %s <in_file> <out_file>\n", *argv);
        return -1;
    }

    in_file = (int8 *)argv[1];
    out_file = (int8 *)argv[2];

    infd = open((char *)in_file, O_RDONLY);
    if (!infd)
    {
        perror("open infd");
        return -1;
    }
    outfd = open((char *)out_file, O_WRONLY | O_CREAT, 00777);
    if (!outfd)
    {
        perror("open outfd");
        close(infd);
        return -1;
    }

    int opt;
    char *r_opt;
    char *w_opt;
    printf("TO DECRYPT ENTER 1:\n TO ENCRYPT ENTER 2:\n");
    scanf("%d", &opt);
    if (opt == 1)
    {
        r_opt = "rb";
        w_opt = "w";
    }
    else if (opt == 2)
    {
        r_opt = "r";
        w_opt = "wb";
    }
    else
        assert_perror(errno);

    key = read_key("ENTER KEY:");
    assert(key);
    key_size = (int16)strlen((char *)key);
    key_size += 0;
    int8 *pad8 = secure_rand(2);
    pad_size = *(int16 *)pad8;

    printf("initializing encryptions...");
    fflush(stdout);
    rc4 = rc4init((int8 *)key, (int16)(key_size));
    printf("done\n");

    // read from input file
    encrypt_file(argv[1], argv[2], rc4, r_opt, w_opt);

    close(infd);
    close(outfd);
    free(pad8); // malloced in secure_rand
    // free(from); // malloced in read file
    return 0;
}