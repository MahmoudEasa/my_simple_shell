#include "shell.h"

/**
 * handle_env - print environment
 * @argv: array
 * @commands: array
 * @status: integer
 */

void handle_env(char **argv, char **commands, int *status)
{
	char **envp = environ;
	(void)argv;
	(void)commands;
	(void)status;

	while (*envp)
	{
		write(STDOUT_FILENO, *envp, _strlen(*envp));
		write(STDOUT_FILENO, "\n", 1);
		envp++;
	}
}

