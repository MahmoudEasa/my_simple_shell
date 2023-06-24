#include "shell.h"

/**
 * handle_line - handle command line
 * @line: string
 * @argv: array of arguments
 * @built: struct to handle builtin functions
 */

void handle_line(char *line, char **argv, Built_fun *built)
{
	int line_len;
	static int status;
	char **args = NULL;

	if (!line)
		return;
	line_len = _strlen(line);
	handle_new_line(line, line_len);
	/* handle_s_sep => ; */
	if (handle_s_sep(line, line_len, argv, built, &status) == 1)
	{
		if (status)
			exit(status % 10);
		return;
	}
	/* handle_logic_sep => && || */
	/* if (handle_logic_sep(line, line_len, argv, built) == 1) return; */

	args = split_str(line, " \t");
	free(line);
	if (!args)
		return;

	handle_hash(args);
	if (!check_builtin(argv, args, built, &status))
		check_command(argv, args, &status);
	if (args)
		_free(args);
}

