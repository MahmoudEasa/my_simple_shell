#include "shell.h"

/**
 * ctrl_c - handle ctrl C
 * @signum: integer
 */

void ctrl_c(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	prompt();
}

