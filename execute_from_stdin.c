#include "shell.h"

/**
 * execute_from_stdin - execute command from stdin
 * @argv: array of arguments
 * @built: struct to handle builtin functions
 */

void execute_from_stdin(char **argv, Built_fun *built)
{
	char *line;
	size_t n;

	while (1)
	{
		prompt();
		signal(SIGINT, ctrl_c);
		line = NULL;
		if (getline(&line, &n, stdin) != -1)
			handle_line(line, argv, built);
		else
		{
			if (isatty(STDIN_FILENO))
				write(STDIN_FILENO, "\n", 1);
			free(line);
			break;
		}
	}
}

