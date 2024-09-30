#include "fse.h"
#include "secure_rand.h"
#include "read_key.h"

int main(int argc, char *argv[])
{
    // Arcfour *rc4;
    int8 *in_file;
    int8 *out_file;
    int infd;
    int outfd;
    int8 *key;
    int16 key_size;
    int16 pad_size;

    // if not enough args print error return -1
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
    outfd = open((char *)out_file, O_WRONLY | O_CREAT, 00600);
    if (!outfd)
    {
        perror("open outfd");
        close(infd);
        return -1;
    }

    key = read_key("ENTER KEY:");
    assert(key);
    key_size = (int16)strlen((char *)key);
    key_size += 0;
    int8 *pad8 = secure_rand(2);
    pad_size = *(int16 *)pad8;

    close(infd);
    close(outfd);
    free(pad8);//malloced in secure_rand
    return 0;
}