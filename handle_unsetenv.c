#include "shell.h"

/**
 * handle_unsetenv - handle unsetenv command
 * @args: array of line command
 */

void handle_unsetenv(char **args)
{
	printf("Hello %s\n", args[0]);
}

