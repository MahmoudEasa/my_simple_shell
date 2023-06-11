#include "shell.h"

/**
 * handle_setenv - handle setenv command
 * @args: array of line command
 */

void handle_setenv(char **args)
{
	printf("Hello %s\n", args[0]);
}

