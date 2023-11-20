#include "shell.h"

/**
 * check_cmd - A function that determines if a file is an executable command
 * @inf: the info struct
 * @p: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int check_cmd(inf_t *inf, char *p)
{
	struct stat st;

	(void)inf;
	if (!p || stat(p, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * char_dup - A function that duplicates characters
 * @str_path: the PATH of the string
 * @s: first index
 * @p: final index
 *
 * Return: pointer to new buffer
 */
char *char_dup(char *str_path, int s, int p)
{
	static char buffer[1024];
	int k = 0;
	int j = 0;

	for (j = 0, k = s; k < p; k++)
		if (str_path[k] != ':')
			buffer[j++] = str_path[k];
	buffer[j] = 0;
	return (buffer);
}

/**
 * find_command_path - function that finds the command
 * @inf: the info struct
 * @str_path: the PATH string
 * @c: the command to find
 *
 * Return: full path of the command if found or NULL
 */
char *find_command_path(inf_t *inf, char *str_path, char *c)
{
	int j = 0;
	int current = 0;
	char *p;

	if (!str_path)
		return (NULL);
	if ((string_len(c) > 2) && haystack_check(c, "./"))
	{
		if (check_cmd(inf, c))
			return (c);
	}
	while (1)
	{
		if (!str_path[j] || str_path[j] == ':')
		{
			p = char_dup(str_path, current, j);
			if (!*p)
				string_cat(p, c);
			else
			{
				string_cat(p, "/");
				string_cat(p, c);
			}
			if (check_cmd(inf, p))
				return (p);
			if (!str_path[j])
				break;
			current = j;
		}
		j++;
	}
	return (NULL);
}
