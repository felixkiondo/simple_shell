#include "shell.h"

/**
 * test_delim - function that tests for chain delimeter
 * @inf: parameter struct
 * @buffer: the char buffer
 * @k: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int test_delim(inf_t *inf, char *buffer, size_t *k)
{
	size_t m = *k;

	if (buffer[m] == '|' && buffer[m + 1] == '|')
	{
		buffer[m] = 0;
		m++;
		inf->cmd_buffer_type = CMD_OR;
	}
	else if (buffer[m] == '&' && buffer[m + 1] == '&')
	{
		buffer[m] = 0;
		m++;
		inf->cmd_buffer_type = CMD_AND;
	}
	else if (buffer[m] == ';')
	{
		buffer[m] = 0;
		inf->cmd_buffer_type = CMD_CHAIN;
	}
	else
		return (0);
	*k = m;
	return (1);
}

/**
 * chain_check - function to checks we should continue
 *               chaining based on last status
 * @inf: the parameter struct
 * @buffer: the char buffer
 * @a: address of current position in buf
 * @c: starting position in buffer
 * @l: length of buf
 *
 * Return: Void
 */
void chain_check(inf_t *inf, char *buffer, size_t *a, size_t c, size_t l)
{
	size_t b = *a;

	if (inf->cmd_buffer_type == CMD_AND)
	{
		if (inf->exec_status)
		{
			buffer[c] = 0;
			b = l;
		}
	}
	if (inf->cmd_buffer_type == CMD_OR)
	{
		if (!inf->exec_status)
		{
			buffer[c] = 0;
			b = l;
		}
	}

	*a = b;
}

/**
 * alias_rep - function that replaces an aliases in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int alias_rep(inf_t *inf)
{
	int j;
	list_t *n;
	char *c;

	for (j = 0; j < 10; j++)
	{
		n = begin_node(inf->node_alias, inf->argv[0], '=');
		if (!n)
			return (0);
		free(inf->argv[0]);
		c = str_char(n->str, '=');
		if (!c)
			return (0);
		c = dup_string(c + 1);
		if (!c)
			return (0);
		inf->argv[0] = c;
	}
	return (1);
}

/**
 * vars_rep - function that replaces vars in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int vars_rep(inf_t *inf)
{
	int j = 0;
	list_t *n;

	for (j = 0; inf->argv[j]; j++)
	{
		if (inf->argv[j][0] != '$' || !inf->argv[j][1])
			continue;

		if (!str_compare(inf->argv[j], "$?"))
		{
			string_rep(&(inf->argv[j]),
				dup_string(convertnum_function(inf->exec_status, 10, 0)));
			continue;
		}
		if (!str_compare(inf->argv[j], "$$"))
		{
			string_rep(&(inf->argv[j]),
				dup_string(convertnum_function(getpid(), 10, 0)));
			continue;
		}
		n = begin_node(inf->link_env, &inf->argv[j][1], '=');
		if (n)
		{
			string_rep(&(inf->argv[j]),
				dup_string(str_char(n->str, '=') + 1));
			continue;
		}
		string_rep(&inf->argv[j], dup_string(""));

	}
	return (0);
}

/**
 * string_rep - function that replaces string
 * @o: address of former string
 * @n: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int string_rep(char **o, char *n)
{
	free(*o);
	*o = n;
	return (1);
}
