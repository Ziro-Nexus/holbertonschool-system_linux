#ifndef LS_H_
#define LS_H_

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
/**
 * struct DirOptions - define the functionality of list directories
 * @hidden: -a
 * @long_info: -l
 * @A: -A
 * @err: define the err state of ls
 * @one: -1
 */
typedef struct DirOptions
{
	int hidden;
	int long_info;
	int A;
	int err;
	int one;
} dir_t;
/**
 * struct FolderInfo - contains parsed folder(paths)
 * @n: Number of folders to open
 * @err: define the err state of the directory open
 * @paths: the routes to open
 */
typedef struct FolderInfo
{
	int n;
	int err;
	char *err_str;
	char **paths;
} folder_t;

int GetMode(int argc, char **argv, dir_t **dir_opt);
void Print(int n_folders, char **folders, dir_t *opt);
int OnlyFolders(int argc, char **argv, folder_t *finfo);
void del(int argc, char **arr);
char *StrDup(char *src);
int StrLen(char *str);
#endif /* hls header */
