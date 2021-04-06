#include "signals.h"

/**
 * handler - doc
 * @sig: SIGNUM
 * @siginfo: info struct for SIG to access si_pid
 * @context: not used
 * Return: void
 */
void handler(int sig, siginfo_t *siginfo, void *context)
{
	pid_t sender_pid = siginfo->si_pid;
	(void)sig;
	(void)context;

	printf("SIGQUIT sent by %d\n", sender_pid);
	fflush(stdout);
}


/**
 * trace_signal_sender - doc
 * Return: 0
 */
int trace_signal_sender(void)
{
	struct sigaction act;

	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;

	return (sigaction(SIGQUIT, &act, NULL));
}
