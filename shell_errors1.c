#include "shell.h"

/**
 * str_int - a function that converts a string to an integer
 * @str: the string to be converted to an interger
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int str_int(char *str)
{
	int t = 0;
	unsigned long int r = 0;

	if (*str == '+')
		str++;
	for (t = 0;  str[t] != '\0'; t++)
	{
		if (str[t] >= '0' && str[t] <= '9')
		{
			r *= 10;
			r += (str[t] - '0');
			if (r > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}

	return (r);
}

/**
 * _print_error - a function that prints an error message
 * @inf: the parameter & return info structure
 * @str: string that contains the specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void _print_error(inf_t *inf, char *str)
{
	input_string(inf->file_name);
	input_string(": ");
	print_dec(inf->count_line, STDERR_FILENO);
	input_string(": ");
	input_string(inf->argv[0]);
	input_string(": ");
	input_string(str);
}

/**
 * print_dec - function prints a decimal (integer) number (base 10)
 * @p: the input
 * @fd: filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_dec(int p, int fd)
{
	int (*__putchar)(char) = _putchar;
	int k, count = 0;
	unsigned int b, curr;

	if (fd == STDERR_FILENO)
		__putchar = error_putchar;
	if (p < 0)
	{
		b = -p;
		__putchar('-');
		count++;
	}
	else
		b = p;
	curr = b;
	for (k = 1000000000; k > 1; k /= 10)
	{
		if (b / k)
		{
			__putchar('0' + curr / k);
			count++;
		}
		curr %= k;
	}
	__putchar('0' + curr);
	count++;

	return (count);
}

/**
 * convertnum_function - function that converts a function
 * @n: number
 * @b: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convertnum_function(long int n, int b, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long i = n;

	if (!(flags & CONVERT_UNSIGNED) && n < 0)
	{
		i = -n;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % b];
		i /= b;
	} while (i != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * comments_remover - a function that removes comments
 * @buffer: address of the string to remove comments
 *
 * Return: Always 0;
 */
void comments_remover(char *buffer)
{
	int j;

	for (j = 0; buffer[j] != '\0'; j++)
		if (buffer[j] == '#' && (!j || buffer[j - 1] == ' '))
		{
			buffer[j] = '\0';
			break;
		}
}
