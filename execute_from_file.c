#include "shell.h"

/**
 * execute_from_file - execute command from file
 * @argv: array of arguments
 * @built: struct to handle builtin functions
 */

void execute_from_file(char **argv, Built_fun *built)
{
	char *line = NULL;
	FILE *fp;
	size_t n;

	fp = fopen(argv[1], "r");
		if (fp == NULL)
		{
			file_error(argv[0], argv[1]);
			exit(127);
		}

		while (getline(&line, &n, fp) != -1)
		{
			handle_line(line, argv, built);
			line = NULL;
		}
		if (line)
			free(line);
	fclose(fp);
}

