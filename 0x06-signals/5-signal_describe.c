#include "signals.h"

/**
 * main - entry
 * @argc: number of arguments
 * @argv: arguments, 0 is program name and 1 is SIGNUM
 * Return: 0 on success or EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
	char *sig_str;

	if (argc != 2)
	{
		printf("Usage: %s <signum>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	sig_str = strsignal(atoi(argv[1]));
	printf("%s: %s\n", argv[1], sig_str);
	return (0);
}
