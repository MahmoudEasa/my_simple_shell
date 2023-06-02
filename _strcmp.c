#include "main.h"

/**
 * _strcmp - a function that compare between two strings
 * @s1: first string
 * @s2: second string
 * @len: length of the second string
 *
 * Return: on success return 0
*/

int _strcmp(char *s1, char *s2, int len)
{
	int i = 0;

	while (s1[i] != '\0' && s2[i] && len != 0)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
		len--;
	}
	return (0);
}

