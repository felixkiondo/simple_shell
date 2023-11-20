#include "shell.h"

/**
 * main - entry point to the shell program
 * @arg_count: argument count
 * @arg_vector: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int arg_count, char **arg_vector)
{
	inf_t inf[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (arg_count == 2)
	{
		fd = open(arg_vector[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				input_string(arg_vector[0]);
				input_string(": 0: Can't open ");
				input_string(arg_vector[1]);
				error_putchar('\n');
				error_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->_readfd = fd;
	}
	envlist_populate(inf);
	read_existing(inf);
	shell_loop(inf, arg_vector);
	return (EXIT_SUCCESS);
}
