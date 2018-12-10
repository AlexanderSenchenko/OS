#ifndef MAIN_H
#define MAIN_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>

#define FIFO "fifo.l"
#define PERM 0666
#define MAXBUFF 30
// 123456789012345678901234567890
#define TEMPLATE "FILENAME~"
char sig = 26;

#endif

// 111111111111111111111111111111
// 1111111111111111111111111111