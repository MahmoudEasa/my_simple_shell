#include "shell.h"

/**
 * handle_alias - handle alias command
 * @args: array of line command
 */

void handle_alias(char **args)
{
	printf("Hello %s\n", args[0]);
}

