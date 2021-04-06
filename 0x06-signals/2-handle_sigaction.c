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
 * handle_sigaction - doc
 * Return: doc
 */
int handle_sigaction(void)
{
	struct sigaction action;

	action.sa_handler = handler;
	return (sigaction(SIGINT, &action, NULL));
}
