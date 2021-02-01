#include "_getline.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void insert(list_t **list, int fd)
{
    list_t *tmp = (*list);
    list_t *new_node = NULL;

    if (!*list)
    {
        (*list) = malloc(sizeof(list_t));
        (*list)->file_buffer = parser(fd);
        (*list)->next = NULL;
        return;
    }

    while(tmp->next != NULL)
        tmp = tmp->next;
    
    new_node = malloc(sizeof(list_t));
    new_node->file_buffer = parser(fd);
    new_node->next = NULL;

    tmp->next = new_node;
}


int new_line_pos(char *bf)
{
    int i;

    for (i = 0; bf[i] != '\0'; i++)
        if (bf[i] == '\n')
            return (i);
    
    return (0);
}


fbuffer_t *parser(int fd)
{
    char buf[READ_SIZE];
    fbuffer_t *f_struct = NULL; 
    char *buffer = (char *)malloc(sizeof(char) * READ_SIZE);
    int pos = 0, ch, fl = 0, n;
    int a;

    if (fd == -1)
        return (NULL);

    n = read(fd, buf, READ_SIZE);

    printf("fd: %d, %d\n",fd, n);
    memcpy(buffer, buf, n);
    buffer[n] = '\0';
    f_struct = malloc(sizeof(fbuffer_t));
    f_struct->buffer = buffer;
    f_struct->fd = fd;
    f_struct->size = n;
    return f_struct;
}

char *_getline(const int fd)
{
    
    //memcpy(buff2, buf, new_line_pos(buf));
    static list_t *fd_list = NULL;
    char *line = NULL;
    int line_size;
    
    if (!fd_list)
    {
        insert(&fd_list, fd);
        line_size = new_line_pos(fd_list->file_buffer->buffer) + 1;
        line = malloc(sizeof(char) * line_size);
        memcpy(line, fd_list->file_buffer->buffer, line_size);
        line[line_size - 1] = '\0';
        close(fd);
        return line;
    }

    return NULL;
}

int main()
{
    char *s = _getline(open("file1", O_RDONLY));
    printf("%s\n", s);
    return (0);
}
