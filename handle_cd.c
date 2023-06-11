#include "shell.h"

/**
 * handle_cd - handle command cd
 * @args: array of line command
 */

void handle_cd(char **args)
{
	_chdir(args);
}

