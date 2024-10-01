#ifndef FSE_H
#define FSE_H

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <errno.h>
#include <assert.h>
#include <sys/random.h>
#include <termios.h>

#include <arcfour.h>

void change_echo(bool);                 
int8 *secure_rand(int16);
int8 *read_key(char *); // reads key from user input
void printbin(int8 *, const int16);
int8 *read_file(FILE *infd);
void encrypt_file(char *, char *, Arcfour *, char *, char *);

int main(int, char **);

#endif // !FSE_H