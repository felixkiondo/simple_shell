#include "shell.h"

/**
 * initialize_struct - a function that initializes i_t structure
 * @inf: struct address
 */
void initialize_struct(inf_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * set_struct - function that initializes info_t struct
 * @inf: structure address
 * @v: argument vector
 */
void set_struct(inf_t *inf, char **v)
{
	int j = 0;

	inf->file_name = v[0];
	if (inf->arg)
	{
		inf->argv = strto_two(inf->arg, " \t");
		if (!inf->argv)
		{

			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = dup_string(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (j = 0; inf->argv && inf->argv[j]; j++)
			;
		inf->argc = j;

		alias_rep(inf);
		vars_rep(inf);
	}
}

/**
 * free_struct - frees info_t struct fields
 * @inf: addrress to the structure
 * @a_ll: true if freeing all fields
 */
void free_struct(inf_t *inf, int a_ll)
{
	free_strings(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (a_ll)
	{
		if (!inf->cmd_buffer)
			free(inf->arg);
		if (inf->link_env)
			free_list(&(inf->link_env));
		if (inf->his_tory)
			free_list(&(inf->his_tory));
		if (inf->node_alias)
			free_list(&(inf->node_alias));
		free_strings(inf->mode_environ);
			inf->mode_environ = NULL;
		free_pointer((void **)inf->cmd_buffer);
		if (inf->_readfd > 2)
			close(inf->_readfd);
		_putchar(BUF_FLUSH);
	}
}
