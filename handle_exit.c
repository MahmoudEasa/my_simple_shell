#include "shell.h"

/**
 * handle_exit - handle exit command
 * @argv: array of arguments
 * @args: array of line command
 * @status: integer
 */

void handle_exit(char **argv, char **args, int *status)
{
	int i = 0, exit_status = 0;

	if (args[1])
	{
		exit_status = _atoi(args[1]);
		while (args[1][i])
			if (_isalpha(args[1][i++]) != 0 || exit_status < 0)
			{
				write_err(argv, args);
				exit_status = 2;
				break;
			}
	}
	_free(args);
	if (!isatty(STDIN_FILENO) && *status)
		exit((*status % 10));
	exit(exit_status);
}

/**
 * write_err - print error for exit
 * @argv: array of arguments
 * @cmd: array of commands
 */

void write_err(char **argv, char **cmd)
{
	write(STDERR_FILENO, argv[0], _strlen(argv[0]));
	write(STDERR_FILENO, ": 1: exit: Illegal number: ", 27);
	write(STDERR_FILENO, cmd[1], _strlen(cmd[1]));
	write(STDERR_FILENO, "\n", 1);
}

