#include "main.h"

/**
 * _strtok - a function that seprate a string when find delimeter
 * @str: an input string
 * @delims: an input delimeters
 * Return: return string if success
*/


char *_strtok(char *str, char *delims)
{
	static char str_copy[100];
	static size_t i;
	char *string = NULL;
	int j, len = _strlen(delims), found;

	if (str)
	{
		_strcpy(str_copy, str);
		i = 0;
	}
	if (!str_copy[i])
		return (NULL);
	for (; str_copy[i]; i++)
	{
		found = 0;
		for (j = 0; j < len; j++)
			if (str_copy[i] == delims[j])
			{
				found = 1;
				str_copy[i] = '\0';
				break;
			}

		if (found)
		{
			if (!string)
				continue;
			else
			{
				i++;
				break;
			}
		}
		else if (!string)
			string = &str_copy[i];
	}
	return (string);
}
