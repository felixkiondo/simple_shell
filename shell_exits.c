#include "shell.h"

/**
 **_strncopy - A function that copies a string
 *@d: the destination string to where the source string is copied to
 *@s: the source string to be copied
 *@num: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncopy(char *d, char *s, int num)
{
	int k, j;
	char *ptr = d;

	k = 0;
	while (s[k] != '\0' && k < num - 1)
	{
		d[k] = s[k];
		k++;
	}
	if (k < num)
	{
		j = k;
		while (j < num)
		{
			d[j] = '\0';
			j++;
		}
	}
	return (ptr);
}

/**
 **str_cat - function that concatenates two strings
 *@d: the destination string
 *@source: the source string
 *@num: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *str_cat(char *d, char *source, int num)
{
	int i, j;
	char *ptr = d;

	i = 0;
	j = 0;
	while (d[i] != '\0')
		i++;
	while (source[j] != '\0' && j < num)
	{
		d[i] = source[j];
		i++;
		j++;
	}
	if (j < num)
		d[i] = '\0';
	return (ptr);
}

/**
 **str_char - a function that locates a character in a string
 *@str: the string to be parsed so as to locate a character
 *@ch: the character to be located
 *Return: (s) a pointer to the memory area s
 */
char *str_char(char *str, char ch)
{
	do {
		if (*str == ch)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
