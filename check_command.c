#include "shell.h"

/**
 * check_command - handle the bath
 * @argv: array of arguments
 * @args: array of line commend
 * @status: integer
 */

void check_command(char **argv, char **args, int *status)
{
	char *paths, path[100], *path_tok;
	struct stat st;

	if (args[0])
	{
		if (*args[0] != '/' && *args[0] != '.')
		{
			paths = _getenv("PATH");
			path_tok = _strtok(paths, ":");
			while (path_tok)
			{
				_strcpy(path, path_tok);
				_strcat(path, "/");
				_strcat(path, args[0]);

				if (stat(path, &st) == 0)
				{
					run_fork(path, args, status);
					return;
				}
				path_tok = _strtok(NULL, ":");
			}
			file_error(argv[0], args[0]);
			if (!isatty(STDIN_FILENO))
				exit(127);
		}
		else
		{
			if (stat(args[0], &st) == 0)
				run_fork(args[0], args, status);
			else
				file_error(argv[0], args[0]);
		}
	}
}

