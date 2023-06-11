#include "shell.h"

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
		strp = malloc(sizeof(char) * (_strlen(str) + 1));
		_strcpy(strp, str);
		arg = _strtok(strp, tok);
		if (arg != NULL)
			len = 1;

		while (((arg = _strtok(NULL, tok)) != NULL))
			len++;
		free(strp);

		arg = _strtok(str, tok);
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
				arg = _strtok(NULL, tok);
			}
			command[i] = NULL;
		}
	}
	return (command);
}

