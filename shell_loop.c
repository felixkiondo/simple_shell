#include "shell.h"

/**
 * shell_loop - function for main shell loop
 * @inf: parameter and return info struct
 * @v: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell_loop(inf_t *inf, char **v)
{
	ssize_t j = 0;
	int b = 0;

	while (j != -1 && b != -2)
	{
		initialize_struct(inf);
		if (interactive_mode(inf))
			put_string("$ ");
		error_putchar(BUF_FLUSH);
		j = minus_line(inf);
		if (j != -1)
		{
			set_struct(inf, v);
			b = find_builtin_cmd(inf);
			if (b == -1)
				find_command(inf);
		}
		else if (interactive_mode(inf))
			_putchar('\n');
		free_struct(inf, 0);
	}
	write_existing(inf);
	free_struct(inf, 1);
	if (!interactive_mode(inf) && inf->exec_status)
		exit(inf->exec_status);
	if (b == -2)
	{
		if (inf->error_num == -1)
			exit(inf->exec_status);
		exit(inf->error_num);
	}
	return (b);
}

/**
 * find_builtin_cmd - finds a builtin command
 * @inf: parameter and return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin_cmd(inf_t *inf)
{
	int j, b = -1;
	builtin_table built[] = {
		{"exit", shell_exit},
		{"env", print_env},
		{"help", ch_currentdir},
		{"history", shell_history},
		{"setenv", myset_env},
		{"unsetenv", myunset_env},
		{"cd", shell_cd},
		{"alias", shell_alias},
		{NULL, NULL}
	};

	for (j = 0; built[j].type; j++)
		if (str_compare(inf->argv[0], built[j].type) == 0)
		{
			inf->count_line++;
			b = built[j].func(inf);
			break;
		}
	return (b);
}

/**
 * find_command - finds a command in PATH
 * @inf: the parameter & return info struct
 *
 * Return: void
 */
void find_command(inf_t *inf)
{
	char *path = NULL;
	int j, l;

	inf->path = inf->argv[0];
	if (inf->line_count_flag == 1)
	{
		inf->count_line++;
		inf->line_count_flag = 0;
	}
	for (j = 0, l = 0; inf->arg[j]; j++)
		if (!char_delim(inf->arg[j], " \t\n"))
			l++;
	if (!l)
		return;

	path = find_command_path(inf, get_env(inf, "PATH="), inf->argv[0]);
	if (path)
	{
		inf->path = path;
		fork_command(inf);
	}
	else
	{
		if ((interactive_mode(inf) || get_env(inf, "PATH=")
			|| inf->argv[0][0] == '/') && check_cmd(inf, inf->argv[0]))
			fork_command(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->exec_status = 127;
			_print_error(inf, "not found\n");
		}
	}
}

/**
 * fork_command - function to fork command
 * @inf: the parameter & return info struct
 *
 * Return: void
 */
void fork_command(inf_t *inf)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(inf->path, inf->argv, _get_environ(inf)) == -1)
		{
			free_struct(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(inf->exec_status));
		if (WIFEXITED(inf->exec_status))
		{
			inf->exec_status = WEXITSTATUS(inf->exec_status);
			if (inf->exec_status == 126)
				_print_error(inf, "Permission denied\n");
		}
	}
}
