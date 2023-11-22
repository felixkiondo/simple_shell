#include "shell.h"

/**
 * shell_history - a function that displays the history list,
 *                 one command by line, preceded with line numbers,
 *                 starting at 0.
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int shell_history(inf_t *inf)
{
	list_print(inf->his_tory);
	return (0);
}

/**
 * alias_string- a function that sets alias to a string
 * @inf: parameter structure
 * @s: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_string(inf_t *inf, char *s)
{
	char *ptr, ch;
	int r;

	ptr = str_char(s, '=');
	if (!ptr)
		return (1);
	ch = *ptr;
	*ptr = 0;
	r = delete_node(&(inf->node_alias),
		index_node(inf->node_alias, begin_node(inf->node_alias, s, -1)));
	*ptr = ch;
	return (r);
}

/**
 * setstring_alias - a function that sets alias to a string
 * @inf: parameter structure
 * @s: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int setstring_alias(inf_t *inf, char *s)
{
	char *ptr;

	ptr = str_char(s, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (alias_string(inf, s));

	alias_string(inf, s);

	return (node_end(&(inf->node_alias), s, 0) == NULL);
}

/**
 * _printalias - a function that prints an alias string
 * @n: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int _printalias(list_t *n)
{
	char *ptr = NULL, *ch = NULL;

	if (n)
	{
		ptr = str_char(n->str, '=');
		for (ch = n->str; ch <= ptr; ch++)
			_putchar(*ch);
		_putchar('\'');
		put_string(ptr + 1);
		put_string("'\n");
		return (0);
	}
	return (1);
}

/**
 * shell_alias - a function that mimics the alias builtin (man alias)
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int shell_alias(inf_t *inf)
{
	int j = 0;
	char *ptr = NULL;
	list_t *n = NULL;

	if (inf->argc == 1)
	{
		n = inf->node_alias;
		while (n)
		{
			_printalias(n);
			n = n->next;
		}
		return (0);
	}
	for (j = 1; inf->argv[j]; j++)
	{
		ptr = str_char(inf->argv[j], '=');
		if (ptr)
			setstring_alias(inf, inf->argv[j]);
		else
			_printalias(begin_node(inf->node_alias, inf->argv[j], '='));
	}

	return (0);
}
