#include "hls.h"
#include <stdio.h>
#include <string.h>

void PrintUnique(DIR *dir, dir_t *opt);
void PrintSome(char **folders, int n, dir_t *opt);

/**
 * Print - print folders with defined options
 * @n_folders: number of folder to list
 * @folders: array of string
 * @opt: option of the print
 * Return: void
 */
void Print(int n_folders, char **folders, dir_t *opt)
{
	switch (n_folders)
	{
		case 0:
			PrintUnique(opendir("."), opt);
			break;
		case 1:
			PrintUnique(opendir(*folders), opt);
			break;
		default:
			PrintSome(folders, n_folders, opt);
	}
}
/**
 * PrintUnique - handle only one directory
 * @dir: directory to read
 * @opt: option of the print
 * Return: void
 */
void PrintUnique(DIR *dir, dir_t *opt)
{
	struct dirent *buff = NULL;

	while ((buff = readdir(dir)) != NULL)
	{
		if (!opt->hidden && *buff->d_name == '.')
			continue;

		printf("%s ", buff->d_name);

		if (opt->one)
			putchar('\n');
	}

	if (!opt->one)
		putchar('\n');

	closedir(dir);
}
/**
 * PrintSome- handle some directories
 * @folders: array of paths
 * @n: number of arguments
 * @opt: option of the print
 * Return: void
 */
void PrintSome(char **folders, int n, dir_t *opt)
{
	int x;

	for (x = 0; x < n; x++)
	{
		printf("%s:\n", folders[x]);
		PrintUnique(opendir(folders[x]), opt);
		if (x != (n - 1))
			putchar('\n');
	}
}
