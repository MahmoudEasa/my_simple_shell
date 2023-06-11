#include "shell.h"

/**
 * handle_hash - handle #
 * @args: array of line command
 */

void handle_hash(char **args)
{
	int i = 0, j;

	while (args[i])
	{
		if (*args[i] == '#')
		{
			j = i;
			while (args[j])
				free(args[j++]);
			args[i] = NULL;
			break;
		}
		i++;
	}
}

