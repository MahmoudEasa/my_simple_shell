#include "shell.h"

/**
 * prompt - display prompet in stdin
 */

void prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "($) ", 4);
}

