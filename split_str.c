#include "main.h"

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

	strp = malloc(sizeof(char) * _strlen(str));
	_strcpy(strp, str);
	arg = _strtok(strp, tok);
	if (arg != NULL && *arg != '#')
		len = 1;

	while (((arg = _strtok(NULL, tok)) != NULL && *arg != '#'))
		len++;
	free(strp);

	arg = _strtok(str, tok);
	if (arg && *arg != '#')
	{
		command = malloc(sizeof(char *) * (len + 1));
		if (!command)
			exit(EXIT_FAILURE);
		i = 0;
		while ((arg && *arg != '#'))
		{
			len = _strlen(arg);
			command[i] = malloc(sizeof(char) * len);
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
	return (command);
}

