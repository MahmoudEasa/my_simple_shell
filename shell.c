#include "shell.h"

/**
 * main - Entry point
 * @argc: The count of arguments
 * @argv: An array of arguments
 *
 * Return: 0
 */

int main(int argc, char **argv)
{
	Built_fun built[8] = {
		{"cd", handle_cd},
		{"exit", handle_exit},
		{"setenv", handle_setenv},
		{"unsetenv", handle_unsetenv},
		{"alias", handle_alias},
		{NULL, NULL},
	};

	if (argc == 2)
		execute_from_file(argv, built);
	else
		execute_from_stdin(argv, built);

	return (0);
}

