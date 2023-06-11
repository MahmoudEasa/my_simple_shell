#include "shell.h"

/**
 * exe - execute command
 * @arg0: string
 * @args: array of line command
 */

void exe(char *arg0, char **args)
{
	if (execve(arg0, args, environ) == -1)
	{
		perror("Error ");
		exit(EXIT_FAILURE);
	}
}

