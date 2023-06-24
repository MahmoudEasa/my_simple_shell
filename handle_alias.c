#include "shell.h"

/**
 * handle_alias - handle alias command
 * @argv: array of arguments
 * @args: array of line command
 * @status: integer
 */

void handle_alias(char **argv, char **args, int *status)
{
	(void)argv;
	(void)status;

	printf("Hello %s\n", args[0]);
}

