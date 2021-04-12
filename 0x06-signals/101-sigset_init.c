#include "signals.h"

/**
 * sigset_init - doc
 * @set: doc
 * @signals: doc
 * Return: doc
 */
int sigset_init(sigset_t *set, int *signals)
{
	for (sigemptyset(set); *signals; signals++)
		if (sigaddset(set, *signals))
			return (-1);
	return (0);
}
