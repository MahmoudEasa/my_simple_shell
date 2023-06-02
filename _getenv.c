#include "main.h"

/**
 * _getenv - a function that get env variable
 * @name: input name
 * Return: return value
*/

char *_getenv(char *name)
{
	int i;
	int len;
	char *value = NULL;

	len = _strlen(name);
	for (i = 0; *environ[i]; i++)
	{
		if (_strcmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			value = &environ[i][len + 1];
			break;
		}
	}
	return (value);
}

