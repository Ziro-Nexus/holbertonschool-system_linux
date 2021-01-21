#include "hls.h"


/**
 * GetMode - check parameters and parse options
 * @argc: n of arguments
 * @argv: array of arguments
 * @dir_opt: options
 * Return: Success
 */
int GetMode(int argc, char **argv, dir_t **dir_opt)
{
	int x, z;

	for (z = 0; z < argc; z++)
	{
		if (*argv[z] == '-')
			for (x = 0; x < strlen(argv[z]); x++)
				switch (argv[z][x])
				{
					case 'a':
						(*dir_opt)->hidden = 1;
						break;
					case 'l':
						(*dir_opt)->long_info = 1;
						break;
					case 'A':
						(*dir_opt)->A = 1;
						break;
					case '1':
						(*dir_opt)->one = 1;
						break;
					case '-':
						break;
					default:
						(*dir_opt)->err = (int)argv[z][x];
						break;
				}
	}
	return (0);
}
/**
 * OnlyFolders - check only for folders in the arguments
 * @argc: n of arguments
 * @argv: array of arguments
 * @finfo: defined options
 * Return: Success
 */
int OnlyFolders(int argc, char **argv, folder_t *finfo)
{

	int i, c = 0;

	for (i = 0; i < argc; i++)
	{
		if (*argv[i] != '-')
		{
			finfo->paths[c] = strdup(argv[i]);
			c++;
		}

	}

	finfo->n = c;

	return (c);

}
/**
 * del - delete pointers
 * @argc: n of arguments
 * @arr: array of arguments
 * Return: void
 */
void del(int argc, char **arr)
{
	int x = 0;

	for (; x < argc; x++)
		free(arr[x]);

	free(arr);
}
