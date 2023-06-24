#include "shell.h"

/**
 * handle_s_sep - handle ; separator
 * @line: string
 * @line_len: integer
 * @argv: array of arguments
 * @built: struct to handle builtin functions
 * @status: integer
 *
 * Return: 1 if there is the ; separator or 0 if not
 */

int handle_s_sep(char *line, int line_len, char **argv,
		Built_fun *built, int *status)
{
	int found = 0, i, arg2_0_len;
	char **args = NULL, **args2 = NULL;

	for (i = 0; i < line_len; i++)
	{
		if (line[i] == ';')
		{
			found = 1;
			args = split_str(line, ";");
			free(line);
			if (!args)
				exit(EXIT_FAILURE);
			i = 0;
			while (args[i])
			{
				args2 = split_str(args[i], " \t");
				if (!args2)
				{
					_free(args);
					exit(EXIT_FAILURE);
				}
				handle_hash(args2);
				arg2_0_len = _strlen(args2[0]);
				if (_strcmp_(args2[0], "exit") == 0 &&
						arg2_0_len == _strlen("exit"))
					_free(args);

				if (!check_builtin(argv, args2, built, status))
					check_command(argv, args2, status);
				if (args2)
					_free(args2);
				i++;
				args2 = NULL;
			}
			if (args)
				_free(args);
			break;
		}
	}
	return (found);
}

