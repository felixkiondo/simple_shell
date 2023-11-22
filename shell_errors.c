#include "shell.h"

/**
 *input_string -  a function that prints an input string
 * @string: the string that is to be printed
 *
 * Return: Nothing
 */
void input_string(char *string)
{
	int j = 0;

	if (!string)
		return;
	while (string[j] != '\0')
	{
		error_putchar(string[j]);
		j++;
	}
}

/**
 * error_putchar - a function that writes the character ch to stderr
 * @ch: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int error_putchar(char ch)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (ch != BUF_FLUSH)
		buf[j++] = ch;
	return (1);
}

/**
 * put_fd - a function that writes the character c to given file descriptor
 * @ch: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int put_fd(char ch, int fd)
{
	static int k;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(fd, buf, k);
		k = 0;
	}
	if (ch != BUF_FLUSH)
		buf[k++] = ch;
	return (1);
}

/**
 * puts_fd - a function that prints an input string
 * @string: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of chars put
 */
int puts_fd(char *string, int fd)
{
	int t = 0;

	if (!string)
		return (0);
	while (*string)
	{
		t += put_fd(*string++, fd);
	}
	return (t);
}
