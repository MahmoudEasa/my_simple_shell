#include "shell.h"

/**
 * file_error - print error
 * @arg0: string
 * @file: string
 */

void file_error(char *arg0, char *file)
{
	write(STDERR_FILENO, arg0, _strlen(arg0));
	write(STDERR_FILENO, ": 1: ", 5);
	write(STDERR_FILENO, file, _strlen(file));
	write(STDERR_FILENO, ": not found\n", 12);
}

