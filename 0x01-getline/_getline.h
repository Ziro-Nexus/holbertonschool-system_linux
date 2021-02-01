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

/**
 * struct FileBuffer - stuct of fd
 * @fd: file descriptor
 * @buffer: current buffer
 * @size: size of the buffer
 * @lines_c: lines to handler
 */
typedef struct FileBuffer
{
	int fd;
	char *buffer;
	size_t size;
	int lines_c;
} fbuffer_t;
/**
 * struct LinkedList - stack of fb buffer
 * @file_buffer: fd buffer struct
 * @next: next element
 */
typedef struct LinkedList
{
	fbuffer_t *file_buffer;
	struct LinkedList *next;
} list_t;
/**
 * struct Line - struct of the line
 * @line: buffer of the line
 * @line_size: size of the line
 */
typedef struct Line
{
	char *line;
	size_t line_size;
} line_t;

char *_getline(const int fd);
fbuffer_t *parser(int fd);
int new_line_pos(char *bf);

#endif
