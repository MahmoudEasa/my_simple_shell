/**
 * _strcmp_ - compares two strings
 * @s1: first string
 * @s2: second strign
 *
 * Return:
 *	0, if the s1 and s2 are equal
 *	a negative value if s1 is less than s2
 *	a positive value if s1 is greater than s2
 */

int _strcmp_(char *s1, char *s2)
{
	int i = 0, is_strcmp = 0;

		while (!(s1[i] == '\0' || s2[i] == '\0'))
		{
			is_strcmp = ((int)s1[i] - (int)s2[i]);
			if (is_strcmp > 0 || is_strcmp < 0)
				break;
			i++;
		}


	return (is_strcmp);
}

