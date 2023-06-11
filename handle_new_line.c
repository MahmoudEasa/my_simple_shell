#include "shell.h"

/**
 * handle_new_line - handle \n
 * @line: string
 * @line_len: integer
 */

void handle_new_line(char *line, int line_len)
{
	if (line[line_len - 1] == '\n')
		line[line_len - 1] = '\0';
}

