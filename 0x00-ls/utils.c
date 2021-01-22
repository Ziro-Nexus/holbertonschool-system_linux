#include "hls.h"
/**
 * StrDup - get copy of src
 * @src: string to copy
 * Return: new string
 */
char *StrDup(char *src)
{
	char *new_str;
	int lenght = 0, into;

	if (!src)
	{
		return (NULL);
	}

	while (src[lenght] != '\0')
		lenght++;

	new_str = malloc(sizeof(char) * lenght + 1);
	for (into = 0; into < lenght; into++)
	{
		new_str[into] = src[into];
	}
	new_str[lenght] = '\0';
	return (new_str);
}
/**
 * StrLen - get lenght of string
 * @str: string to check
 * Return: Number of elements
 */
int StrLen(char *str)
{
	int c = 0;

	while (str[c] != '\0')
	{
		c++;
	}
	return (c);
}