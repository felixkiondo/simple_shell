#include "shell.h"

/**
 * **strwords - a function that splits a string into words
 *              and ignores repeat delimiters
 * @s: the input string
 * @delim: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strwords(char *s, char *delim)
{
	int a, b, c, d = 0;
	int num_words = 0;
	char **ch;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (a = 0; s[a] != '\0'; a++)
		if (!char_delim(s[a], delim) && (char_delim(s[a + 1], delim) || !s[a + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	ch = malloc((1 + num_words) * sizeof(char *));
	if (!ch)
		return (NULL);
	for (a = 0, b = 0; b < num_words; b++)
	{
		while (char_delim(s[a], delim))
			a++;
		c = 0;
		while (!char_delim(s[a + c], delim) && s[a + c])
			c++;
		ch[b] = malloc((b + 1) * sizeof(char));
		if (!ch[b])
		{
			for (c = 0; c < b; c++)
				free(ch[c]);
			free(ch);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			ch[b][d] = s[a++];
		ch[b][d] = 0;
	}
	ch[b] = NULL;
	return (ch);
}

/**
 * **strto_two - splits a string into words
 * @string: the input string
 * @delim: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strto_two(char *string, char delim)
{
	int a, b, c, d = 0;
	int num_words = 0;
	char **ch;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (a = 0; string[a] != '\0'; a++)
		if ((string[a] != delim && string[a + 1] == delim) ||
		    (string[a] != delim && !string[a + 1]) || string[a + 1] == delim)
			num_words++;
	if (num_words == 0)
		return (NULL);
	ch = malloc((1 + num_words) * sizeof(char *));
	if (!ch)
		return (NULL);
	for (a = 0, b = 0; b < num_words; b++)
	{
		while (string[a] == delim && string[a] != delim)
			a++;
		c = 0;
		while (string[a + c] != delim && string[a + c] && string[a + c] != delim)
			c++;
		ch[b] = malloc((c + 1) * sizeof(char));
		if (!ch[b])
		{
			for (c = 0; c < b; c++)
				free(ch[c]);
			free(ch);
			return (NULL);
		}
		for (d = 0; d < b; d++)
			ch[b][d] = string[a++];
		ch[b][d] = 0;
	}
	ch[b] = NULL;
	return (ch);
}
