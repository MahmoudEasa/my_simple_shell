/**
 * _strlen - return the length of a string
 * @s: (char) Pointer of string
 *
 * Return: Length of s
 */

int _strlen(char *s)
{
	int len = 0;
	char *p = s;

	while (*p != '\0')
	{
		len++;
		p++;
	}

	return (len);
}

