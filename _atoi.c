/**
 * _atoi - convert a string to an integer
 * @s: (char) Pointer to string
 *
 * Return: 0 If there are no numbers in the string
 * Otherwise return the number
 */

int _atoi(char *s)
{
	unsigned int i = 0, len = 0, negative = 0, num_in_str = 0;

	while (s[i++] != '\0')
		len++;

	for (i = 0; i < len; i++)
	{
		if (num_in_str > 0 && !(s[i] >= (int)'0' && s[i] <= (int)'9'))
			break;

		if (s[i] == '-')
			negative++;
		else if (s[i] >= (int)'0' && s[i] <= (int)'9')
			num_in_str = (num_in_str * 10) + (s[i] - '0');
	}

	if (negative % 2 != 0)
		return (-num_in_str);
	else
		return (num_in_str);
}

