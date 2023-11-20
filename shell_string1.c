#include "shell.h"

/**
 * _strcopy - function that copies a string
 * @dst: destination to paste
 * @source: the source
 *
 * Return: pointer to destination
 */
char *_strcopy(char *dst, char *source)
{
	int a = 0;

	if (dst == source || source == 0)
		return (dst);
	while (source[a])
	{
		dst[a] = source[a];
		a++;
	}
	dst[a] = 0;
	return (dst);
}

/**
 * dup_string - function that duplicates a string
 * @string: the string to be duplicated
 *
 * Return: pointer to the duplicated string
 */
char *dup_string(const char *string)
{
	int len = 0;
	char *s;

	if (string == NULL)
		return (NULL);
	while (*string++)
		len++;
	len = malloc(sizeof(char) * (len + 1));
	if (!len)
		return (NULL);
	for (len++; len--;)
		s[len] = *--string;
	return (s);
}

/**
 *put_string - function that prints an input string
 *@string: the string that is printed
 *
 * Return: Nothing
 */
void put_string(char *string)
{
	int j = 0;

	if (!string)
		return;
	while (string[j] != '\0')
	{
		_putchar(string[j]);
		j++;
	}
}

/**
 * _putchar - function that writes the character ch to stdout
 * @ch: The character that is to be printed
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set.
 */
int _putchar(char ch)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(1, buf, a);
		a = 0;
	}
	if (ch != BUF_FLUSH)
		buf[a++] = ch;
	return (1);
}
