#ifndef SECURERAND_H
#define SECURERAND_H
#include "fse.h"

int8 *secure_rand(int16 size)
{
    int8 *curr;
    int8 *initial_pointer;
    ssize_t n;
    assert(size > 0);
    curr = (int8 *)malloc(size);
    // assert(curr);
    if (!curr)
    {
        printf("MALLOC ERROR SECURE RAND\n");
        assert_perror(errno);
    }

    initial_pointer = curr;
    n = getrandom(curr, (size_t)size, GRND_RANDOM|GRND_NONBLOCK);
    if (n == -1)
    {
        printf("GET RANDOM ERROR, entropy pool not initialized, please wait...");
        perror("getrandom");
        free(initial_pointer);
        return 0;
    }
    else if( n == size)
        return curr;
    
    curr += n;
    //try again for the remaining number of ubfilled bytes
    n = getrandom(curr, (size-n), GRND_RANDOM);

    if(n == size)
        return initial_pointer;
    else if (n < 0)
    {
        free(initial_pointer);
        return 0;
    }
    return 0;
}

#endif // !SECURERAND_H