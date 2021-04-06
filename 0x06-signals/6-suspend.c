#include "signals.h"

/**
 * handler - doc
 * @sig: number of signal sent
 * Return: void
 */
void handler(int sig)
{
	printf("Caught %d\n", sig);
	fflush(stdout);
}

/**
 * handle_signal - doc
 * Return: 0 on success, -1 on error
 */
int handle_signal(void)
{
	if (signal(SIGINT, handler) != SIG_ERR)
		return (0);
	else
		return (-1);
}

/**
 * main - entru
 * Return: 1
 */
int main(void)
{
	if (handle_signal() != 0)
		return (EXIT_FAILURE);
	pause();
	printf("Signal received\n");
	return (EXIT_SUCCESS);
}
