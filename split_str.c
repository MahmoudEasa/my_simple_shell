#include "shell.h"

char *copy_str(char **strp, char *str, char **arg, char *tok);
/**
 * split_str - split string
 * @str: string
 * @tok: character
 *
 * Return: pointer to array of string
 */

char **split_str(char *str, char *tok)
{
	char **command = NULL, *arg, *strp;
	int len, i;

	if (str && tok)
	{
		if (!copy_str(&strp, str, &arg, tok))
			return (NULL);
		len = 1;
		while (((arg = strtok(NULL, tok)) != NULL))
			len++;
		free(strp);
		arg = strtok(str, tok);
		if (arg)
		{
			command = malloc(sizeof(char *) * (len + 1));
			if (!command)
				exit(EXIT_FAILURE);
			i = 0;
			while (arg)
			{
				len = _strlen(arg);
				command[i] = malloc(sizeof(char) * (len + 1));
				if (!command[i])
				{
					_free(command);
					exit(EXIT_FAILURE);
				}
				_strcpy(command[i], arg);
				i++;
				arg = strtok(NULL, tok);
			}
			command[i] = NULL;
		}
	}
	return (command);
}

/**
 * copy_str - copy string
 * @strp: pointer
 * @str: string
 * @arg: pointer
 * @tok: string
 *
 * Return: NULL or arg
 */

char *copy_str(char **strp, char *str, char **arg, char *tok)
{
	*strp = malloc(sizeof(char) * (_strlen(str) + 1));
	if (!(*strp))
		return (NULL);
	_strcpy(*strp, str);
	*arg = strtok(*strp, tok);
	if (!(*arg))
	{
		free(*strp);
		return (NULL);
	}

	return (*arg);
}
