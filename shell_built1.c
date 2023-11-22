#include "shell.h"

/**
 * shell_exit - a function that exits the shell program
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int shell_exit(inf_t *inf)
{
	int e;

	if (inf->argv[1])
	{
		e = str_int(inf->argv[1]);
		if (e == -1)
		{
			inf->exec_status = 2;
			_print_error(inf, "Wrong number: ");
			input_string(inf->argv[1]);
			error_putchar('\n');
			return (1);
		}
		inf->error_num = str_int(inf->argv[1]);
		return (-2);
	}
	inf->error_num = -1;
	return (-2);
}

/**
 * shell_cd - a function that changes the current directory of the process
 * @inf: Structure containing potential arguments.
 *  Return: Always 0
 */
int shell_cd(inf_t *inf)
{
	char *s, *d, buff[1024];
	int c;

	s = getcwd(buff, 1024);
	if (!s)
		put_string("Error: Unable to retrieve current working directory.\n");
	if (!inf->argv[1])
	{
		d = get_env(inf, "HOME=");
		if (!d)
		{
			put_string("Error: HOME environment variable not set.\n");
			c = chdir((d = get_env(inf, "PWD=")) ? d : "/");
		}
		else
			c = chdir(d);
	}
	else if (str_compare(inf->argv[1], "-") == 0)
	{
		if (!get_env(inf, "OLDPWD="))
		{
			put_string(s);
			_putchar('\n');
			return (1);
		}
		put_string(get_env(inf, "OLDPWD=")), _putchar('\n');
		c = chdir((d = get_env(inf, "OLDPWD=")) ? d : "/");
	}
	else
		c = chdir(inf->argv[1]);
	if (c == -1)
	{
		_print_error(inf, "unable to cd to ");
		input_string(inf->argv[1]);
		error_putchar('\n');
	}
	else
	{
		set_env(inf, "OLDPWD", get_env(inf, "PWD="));
		set_env(inf, "PWD", getcwd(buff, 1024));
	}

	return (0);
}

/**
 * ch_currentdir - a function that changes the current directory of the process
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int ch_currentdir(inf_t *inf)
{
	char **ptr;

	ptr = inf->argv;
	put_string("help call works. Function not yet executed \n");
	if (0)
		put_string(*ptr);
	return (0);
}
