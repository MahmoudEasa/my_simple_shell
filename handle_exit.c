#include "shell.h"

/**
 * handle_exit - handle exit command
 * @args: array of line command
 */

void handle_exit(char **args)
{
	int num;

	if (args[1])
	{
		num = _atoi(args[1]);
		_free(args);
		exit(num);
	}
	else
	{
		_free(args);
		exit(EXIT_SUCCESS);
	}
}

