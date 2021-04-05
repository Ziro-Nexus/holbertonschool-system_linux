#include "signals.h"

/**
 * handler - handler for signal 'sig'
 * @sig: number of signal sent
 * Return: void
 */
void handler(int sig)
{
	printf("Gotcha! [%d]\n", sig);
	fflush(stdout);
}

/**
 * handle_signal - sets a handler for the signal SIGINT
 * Return: 0
 */
int handle_signal(void)
{
	if (signal(SIGINT, handler) != SIG_ERR)
		return (0);
	else
		return (-1);
}
