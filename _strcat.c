#include "main.h"

/**
 * _strcat - concatenates two strings
 * @dest: first string
 * @src: second string
 *	appends the src string to the dest string
 *
 * Return: pointer to the resulting string dest
 */

char *_strcat(char *dest, char *src)
{
	int src_len = _strlen(src), i, dest_len;

	if (src_len == 0)
	{
		return (dest);
	}
	else
	{
		dest_len = _strlen(dest);

		for (i = 0; i <= src_len; i++)
		{
			dest[dest_len] = src[i];
			dest_len++;
		}
	}

	return (dest);
}

