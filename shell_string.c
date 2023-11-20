#include "shell.h"

/**
 * string_len - function that returns the length of a string
 * @str: the string to check the length.
 *
 * Return: integer length of string
 */
int string_len(char *str)
{
	int a = 0;

	if (!str)
		return (0);

	while (*str++)
		a++;
	return (a);
}

/**
 * str_compare - function that performs comparison of two strangs.
 * @str1: first string to be compared
 * @str2: second string to be compared
 *
 * Return: negative if str1 < str2, positive if str1 > str2, 0 if str1 == str2
 */
int str_compare(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * haystack_check - function that checks if needle begins with haystack
 * @hay_string: the string to check
 * @n: the substring to check
 *
 * Return: address of next char of haystack or NULL
 */
char *haystack_check(const char *hay_string, const char *n)
{
	while (*n)
		if (*n != *hay_string++)
			return (NULL);
	return ((char *)hay_string);
}

/**
 * string_cat - function that concatenates two strings
 * @d: destination of the buffer
 * @source: source of the buffer
 *
 * Return: pointer to destination buffer
 */
char *string_cat(char *d, char *source)
{
	char *c = d;

	while (*d)
		d++;
	while (*source)
		*d++ = *source++;
	*d = *source;
	return (c);
}
