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
	char *s, buff[1024];

	s = getcwd(buff, 1024);
	if (!s)
		put_string("Error: Unable to retrieve current working directory.\n");

	if (!inf->argv[1])
		handlehome_dir(inf, buff);
	else if (str_compare(inf->argv[1], "-") == 0)
		handle_oldPWD(inf);
	else
		handle_specificdir(inf, inf->argv[1]);

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
