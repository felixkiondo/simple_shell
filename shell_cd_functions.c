#include "shell.h"

/**
 * handlehome_dir - Handles changing the directory to the HOME directory.
 * @inf: Structure containing potential arguments.
 * @buff: Buffer to store directory information.
 */
void handlehome_dir(inf_t *inf, char *buff)
{
	char *d;
	int c;

	d = get_env(inf, "HOME=");
	if (!d)
	{
		put_string("Error: HOME environment variable not set.\n");
		c = chdir((d = get_env(inf, "PWD=")) ? d : "/");
	}
	else
	{
		c = chdir(d);
	}

	if (c == -1)
	{
		_print_error(inf, "unable to cd to ");
		input_string(d);
		error_putchar('\n');
	}
	else
	{
		set_env(inf, "OLDPWD", get_env(inf, "PWD="));
		set_env(inf, "PWD", getcwd(buff, 1024));
	}
}

/**
 * handle_oldPWD - Handles changing the directory to the OLDPWD directory.
 * @inf: Structure containing potential arguments.
 */
void handle_oldPWD(inf_t *inf)
{
	char *s, *d, buff[1024];
	int c;

	s = getcwd(buff, 1024);

	if (!get_env(inf, "OLDPWD="))
	{
		put_string(s);
		_putchar('\n');
		return;
	}

	put_string(get_env(inf, "OLDPWD="));
	_putchar('\n');

	c = chdir((d = get_env(inf, "OLDPWD=")) ? d : "/");
	if (c == -1)
	{
		_print_error(inf, "unable to cd to ");
		input_string(d);
		error_putchar('\n');
	}
	else
	{
		set_env(inf, "OLDPWD", get_env(inf, "PWD="));
		set_env(inf, "PWD", getcwd(buff, 1024));
	}
}

/**
 * handle_specificdir - Handles changing the directory to a specific directory.
 * @inf: Structure containing potential arguments.
 * @dir: The directory to navigate to.
 */
void handle_specificdir(inf_t *inf, char *dir)
{
	char buff[1024];
	int c;

	c = chdir(dir);
	if (c == -1)
	{
		_print_error(inf, "unable to cd to ");
		input_string(dir);
		error_putchar('\n');
	}
	else
	{
		set_env(inf, "OLDPWD", get_env(inf, "PWD="));
		set_env(inf, "PWD", getcwd(buff, 1024));
	}
}
