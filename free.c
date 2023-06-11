#include "shell.h"

/**
 * _free - free allocated memory
 * @cmd: pointer
 */

void _free(char **cmd)
{
	int i;

	if (cmd)
	{
		for (i = 0; cmd[i]; i++)
			free(cmd[i]);

		free(cmd);
	}
}

