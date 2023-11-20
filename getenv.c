#include "shell.h"

/**
 * _get_environ - a function that returns the string array copy of our environ
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **_get_environ(inf_t *inf)
{
	if (!inf->mode_environ || inf->environ_changed)
	{
		inf->mode_environ = list_array(inf->link_env);
		inf->environ_changed = 0;
	}

	return (inf->mode_environ);
}

/**
 * unset_env - a function that removes an environment variable
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @v: the string env var property
 * Return: 1 on delete, 0 otherwise
 */
int unset_env(inf_t *inf, char *v)
{
	list_t *n = inf->link_env;
	size_t j = 0;
	char *ptr;

	if (!n || !v)
		return (0);

	while (n)
	{
		ptr = haystack_check(n->str, v);
		if (ptr && *ptr == '=')
		{
			inf->environ_changed = delete_node(&(inf->link_env), j);
			j = 0;
			n = inf->link_env;
			continue;
		}
		n = n->next;
		j++;
	}
	return (inf->environ_changed);
}

/**
 * set_env - Initialize a new environment variable,
 *             or modify an existing one
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @v: the string env var property
 * @val: the string env var value
 *  Return: Always 0
 */
int set_env(inf_t *inf, char *v, char *val)
{
	char *buffer = NULL;
	list_t *n;
	char *ptr;

	if (!v || !val)
		return (0);

	buffer = malloc(string_len(v) + string_len(val) + 2);
	if (!buffer)
		return (1);
	_strcopy(buffer, v);
	string_cat(buffer, "=");
	string_cat(buffer, val);
	n = inf->link_env;
	while (n)
	{
		ptr = haystack_check(n->str, v);
		if (ptr && *ptr == '=')
		{
			free(n->str);
			n->str = buffer;
			inf->environ_changed = 1;
			return (0);
		}
		n = n->next;
	}
	node_end(&(inf->link_env), buffer, 0);
	free(buffer);
	inf->environ_changed = 1;
	return (0);
}
