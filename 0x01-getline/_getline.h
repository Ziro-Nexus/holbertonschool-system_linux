#ifndef _GETLINE_
#define _GETLINE_
#define READ_SIZE 1024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


typedef struct FileBuffer {
    int fd;
    char *buffer;
    size_t size;
} fbuffer_t;

typedef struct LinkedList {
    fbuffer_t *file_buffer;
    struct LinkedList *next;
} list_t;

char *_getline(const int fd);
fbuffer_t *parser(int fd);
int new_line_pos(char *bf);

#endif
