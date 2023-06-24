#include "shell.h"

/**
 * _isalpha - a function that checks for alphabetic character
 * @c: input value
 * Return: return 0 (Successful)
*/

int _isalpha(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		return (1);
	}
	else if (c >= 'A' && c <= 'Z')
	{
		return (1);
	}
	else
		return (0);
}
