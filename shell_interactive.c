#include "shell.h"

/**
 * interactive_mode - a function that returns true if shell is interactive mode
 * @inf: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive_mode(inf_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->_readfd <= 2);
}

/**
 * char_delim - a function that checks if a character is a delimeter
 * @ch: the character to check
 * @d: the delimeter string
 * Return: 1 if true, 0 if false
 */
int char_delim(char ch, char *d)
{
	while (*d)
		if (*d++ == ch)
			return (1);
	return (0);
}

/**
 *check_alpha - a function that checks for alphabetic character
 *@ch: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int check_alpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *convert_string_to_int - a function that converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int convert_string_to_int(char *str)
{
	int i, t = 1, f = 0, p;
	unsigned int r = 0;

	for (i = 0;  str[i] != '\0' && f != 2; i++)
	{
		if (str[i] == '-')
			t *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			f = 1;
			r *= 10;
			r += (str[i] - '0');
		}
		else if (f == 1)
			f = 2;
	}

	if (t == -1)
		p = -r;
	else
		p = r;

	return (p);
}
