/**
 * _strcpy - copies the string including the terminating null byte (\0),
 * @dest: copy to it
 * @src: copy from it
 *
 * Return: the pointer to dest
 */

char *_strcpy(char *dest, char *src)
{
	int i = 0, len = 1;

	while (src[i++] != '\0')
		len++;

	for (i = 0; i < len; i++)
		dest[i] = src[i];

	return (dest);
}

