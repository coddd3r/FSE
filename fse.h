#ifndef FSE_H
#define FSE_H

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <arcfour.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <errno.h>
#include <assert.h>
#include <sys/random.h>


int8 *secure_rand(int16);
int8 *readkey(int8*);//reads key from user input
int main(int, char **);

#endif // !FSE_H