#include "shell.h"

/**
 * handle_unsetenv - handle unsetenv command
 * @argv: array of arguments
 * @args: array of line command
 * @status: integer
 */

void handle_unsetenv(char **argv, char **args, int *status)
{
	(void)argv;
	(void)status;

	if (args[1])
		if (unsetenv(args[1]) == -1)
			perror("Error");
}

