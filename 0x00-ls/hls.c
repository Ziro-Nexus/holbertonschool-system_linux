#include "hls.h"
#include <asm-generic/errno-base.h>
#include <stdio.h>
#include <string.h>
/**
 * main - Entry Point
 * @argc: number of arguments
 * @argv: Array of String
 * Return: 0 if success, other if error
*/
int main(int argc, char *argv[])
{
	dir_t *opt = malloc(sizeof(dir_t));
	folder_t *finfo = malloc(sizeof(folder_t));

	opt->hidden = 0;
	opt->one = 0;
	opt->long_info = 0;
	opt->A = 0;
	opt->err = 0;
	finfo->n = 0;
	finfo->err = 0;
	finfo->paths = malloc(sizeof(char *) * (argc - 1));
	GetMode(argc - 1, (argv + 1), &opt);
	OnlyFolders(argc - 1, (argv + 1), finfo);
	if (opt->err != 0)
	{
		printf("hls: invalid option -- %c\n", opt->err);
		errno = 2;
	}
	switch (finfo->err)
	{
		case ENOENT:
			dprintf(2, "hls: cannot access %s: %s\n",
			finfo->err_str, "No such file or directory");
			free(finfo->err_str);
			break;
		case EACCES:
			dprintf(2, "hls: cannot open directory %s: %s\n",
			finfo->err_str, "Permission denied");
			free(finfo->err_str);
			break;
	}
	if (opt->err == 0 && finfo->err == 0)
		Print(finfo->n, finfo->paths, opt);
	if (finfo->paths)
		del(finfo->n, finfo->paths);
	free(finfo);
	free(opt);
	return (errno);
}
