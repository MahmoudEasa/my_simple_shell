#include "shell.h"

/**
 * _chdir - a function that change directory
 * @argv: array of arguments
 * @path: a path that be passed
*/

void _chdir(char **argv, char **path)
{
	char old_path[1024], new_path[1024], *str = NULL;

	if (path[1])
		str = path[1];
	if (getcwd(old_path, 1024) == NULL)
		perror("getcwd");
	if (!path[1])
		str = _getenv("HOME");
	else if (_strcmp_(path[1], "-") == 0 && _strlen(path[1]) == 1)
	{
		str = _getenv("OLDPWD");
		if (str)
			printf("%s\n", str);
		else
			printf("%s\n", _getenv("PWD"));
	}
	if (!str)
		return;
	if (chdir(str) == -1)
		handle_error(argv[0], str);
	else if (getcwd(new_path, 1024) == NULL)
		perror("Error");
	else
		update_pwd(old_path, new_path);
}

/**
 * update_pwd - a function that update pwd
 * @old_path: first input
 * @new_path: second input
*/

void update_pwd(char *old_path, char *new_path)
{
	if (setenv("OLDPWD", old_path, 1) == -1)
		exit(EXIT_FAILURE);
	if (setenv("PWD", new_path, 1) == -1)
		exit(EXIT_FAILURE);
}

/**
 * handle_error - a function that handle errors
 * @arg0: program name
 * @path: path passed
*/

void handle_error(char *arg0, char *path)
{
	write(STDERR_FILENO, arg0, _strlen(arg0));
	write(STDERR_FILENO, ": 1: cd: can't cd to ", 21);
	write(STDERR_FILENO, path, _strlen(path));
	write(STDERR_FILENO, "\n", 1);
}

