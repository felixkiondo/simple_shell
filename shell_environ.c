#include "shell.h"

/**
 * print_env - a function that prints the current environment
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int print_env(inf_t *inf)
{
	_printlist(inf->link_env);
	return (0);
}

/**
 * get_env - function that gets the value of an environ variable
 * @inf: Structure containing potential arguments. Used to maintain
 * @m: environ variable name
 *
 * Return: the value
 */
char *get_env(inf_t *inf, const char *m)
{
	list_t *n = inf->link_env;
	char *ptr;

	while (n)
	{
		ptr = haystack_check(n->str, m);
		if (ptr && *ptr)
			return (ptr);
		n = n->next;
	}
	return (NULL);
}

/**
 * myset_env - function that initialize a new environment variable,
 *             or modify an existing one
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int myset_env(inf_t *inf)
{
	if (inf->argc != 3)
	{
		input_string("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * myunset_env - function that erases an environment variable
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int myunset_env(inf_t *inf)
{
	int j;

	if (inf->argc == 1)
	{
		input_string("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= inf->argc; j++)
		unset_env(inf, inf->argv[j]);

	return (0);
}
