#include "shell.h"

/**
 * handle_cd - handle command cd
 * @argv: array of arguments
 * @args: array of line command
 * @status: integer
 */

void handle_cd(char **argv, char **args, int *status)
{
	(void)argv;
	(void)status;

	_chdir(argv, args);
}

