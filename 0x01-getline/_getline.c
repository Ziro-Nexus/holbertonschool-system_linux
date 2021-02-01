#include "_getline.h"
#include <stdio.h>

/**
 * insert - insert new element to linked list
 * @list: head of linked list
 * @fd: file descriptor buffer
 * Return: void
 */
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

	while (tmp->next != NULL)
		tmp = tmp->next;

	new_node = malloc(sizeof(list_t));
	new_node->file_buffer = parser(fd);
	new_node->next = NULL;
	tmp->next = new_node;
}
/**
 * new_line_pos - get the pos of the next new line
 * @bf: buffer to read
 * Return: new line pos or 0
 */
int new_line_pos(char *bf)
{
	int i = 0;

	for (; bf[i] != '\0'; i++)
		if (bf[i] == '\n')
			return (i);

	return (i);
}
/**
 * parser - parse the fd buffer to a readable char*
 * @fd: file descriptor to open
 * Return: new fd buffer or NULL
 */
fbuffer_t *parser(int fd)
{
	char buf[READ_SIZE];
	fbuffer_t *f_struct = NULL;
	char *buffer = (char *)malloc(sizeof(char) * READ_SIZE);
	int n;
	int a, lines_c = 0;

	if (fd == -1)
		return (NULL);

	n = read(fd, buf, READ_SIZE);
	memcpy(buffer, buf, n);
	buffer[n] = '\0';
	f_struct = malloc(sizeof(fbuffer_t));
	f_struct->buffer = buffer;
	for (a = 0; a < n; a++)
		if (f_struct->buffer[a] == '\n')
			lines_c++;
	f_struct->fd = fd;
	f_struct->size = n;
	f_struct->lines_c = lines_c;
	return (f_struct);
}
/**
 * parse_line - get the line from the fd stack
 * @head: head of linked list
 * @fd: file descriptor
 * Return: line_t struct or NULL
 */
line_t *parse_line(list_t **head, int fd)
{
	list_t *tmp = (*head);
	line_t *liner;
	char *line;
	size_t line_size;

	while (tmp != NULL)
	{
		if (tmp->file_buffer->fd == fd)
		{
			if (tmp->file_buffer->lines_c == 0)
				break;

			liner = malloc(sizeof(line_t));
			line_size = (size_t)new_line_pos(tmp->file_buffer->buffer) + 1;
			line = malloc(sizeof(char) * line_size);
			memcpy(line, tmp->file_buffer->buffer, line_size);
			line[line_size - 1] = '\0';
			liner->line = line;
			tmp->file_buffer->buffer += line_size;
			tmp->file_buffer->lines_c--;
			return (liner);
		}
		tmp = tmp->next;
	}

	return (NULL);
}
/**
 * _getline - get line pointer of fd
 * @fd: fd to open
 * Return: current line
 */
char *_getline(const int fd)
{
	static list_t *fd_list;
	char *line = NULL;
	size_t line_size;
	line_t *line_handler = NULL;

	if (!fd_list)
	{
		insert(&fd_list, fd);
		if (fd_list->file_buffer->buffer == NULL)
			return (NULL);

		line_size = new_line_pos(fd_list->file_buffer->buffer) + 1;
		line = malloc(sizeof(char) * line_size);
		memcpy(line, fd_list->file_buffer->buffer, line_size);
		line[line_size - 1] = '\0';
		fd_list->file_buffer->buffer += line_size;
		fd_list->file_buffer->lines_c--;
		return (line);
	}
	line_handler = parse_line(&fd_list, fd);

	if (!line_handler)
		return (NULL);

	return (line_handler->line);
}
