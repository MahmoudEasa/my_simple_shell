#include "main.h"

/**
 * _chdir - a function that change directory
 * @path: a path that be passed
*/

void _chdir(char **path)
{
	char *old_path, *new_path, *str;

	str = path[1];
	old_path = malloc(sizeof(char) * 1024);
	if (!old_path)
	{
		_free(path);
		handle_error("old_path");
	}
	new_path = malloc(sizeof(char) * 1024);
	if (!new_path)
	{
		free(old_path);
		_free(path);
		handle_error("old_path");
	}
	if (getcwd(old_path, 1024) == NULL)
	{
		free_paths(old_path, new_path, path);
		handle_error("getcwd");
	}
	if (!path[1])
		str = check_path(path, old_path, new_path, "HOME");
	else if (_strcmp_(path[1], "-") == 0)
		str = check_path(path, old_path, new_path, "OLDPWD");
	if (chdir(str) == -1)
		free_paths(old_path, new_path, NULL);
	if (getcwd(new_path, 1024) == NULL)
		free_paths(old_path, new_path, NULL);
	update_pwd(old_path, new_path);
	free_paths(old_path, new_path, NULL);
}

/**
 * check_path - a function that checks path that be passed
 * @path: path that be passed
 * @old_path: old path passed
 * @new_path: new path passed
 * @name_var: variable name
 *
 * Return: return str
*/

char *check_path(char **path, char *old_path, char *new_path, char *name_var)
{
	char *str;

	str = _getenv(name_var);
	if (str == NULL)
	{
		write(STDERR_FILENO, "cd: ", 4);
		write(STDERR_FILENO, name_var, _strlen(name_var));
		write(STDERR_FILENO, " not sets\n", 10);
		free_paths(old_path, new_path, path);
		exit(EXIT_FAILURE);
	}
	return (str);
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
 * free_paths - a function that free paths
 * @old_path: first path freed
 * @new_path: second path freed
 * @path: array
*/

void free_paths(char *old_path, char *new_path, char **path)
{
	(void)path;
	free(old_path);
	free(new_path);
	if (path)
		_free(path);
}

/**
 * handle_error - a function that handle errors
 * @path: path passed
*/

void handle_error(char *path)
{
	perror(path);
	exit(EXIT_FAILURE);
}

