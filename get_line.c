#include "shell.h"

/**
 * buf_command - a function that buffers chained commands
 * @inf: parameter struct
 * @buffer: the address of the buffer
 * @l: address of the length variable
 *
 * Return: bytes read
 */
ssize_t buf_command(inf_t *inf, char **buffer, size_t *l)
{
	ssize_t i = 0;
	size_t len = 0;

	if (!*l)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, block_copy);
#if USE_GETLINE
		i = get_line(buffer, &len, stdin);
#else
		i = get_line(inf, buffer, &len);
#endif
		if (i > 0)
		{
			if ((*buffer)[i - 1] == '\n')
			{
				(*buffer)[i - 1] = '\0';
				i--;
			}
			inf->line_count_flag = 1;
			comments_remover(*buffer);
			add_history_list(inf, *buffer, inf->hist_count++);
			if (str_char(*buffer, ';'))
			{
				*l = i;
				inf->cmd_buffer = buffer;
			}
		}
	}
	return (i);
}

/**
 * minus_line - gets a line minus the newline
 * @inf: the parameter structure
 *
 * Return: bytes read
 */
ssize_t minus_line(inf_t *inf)
{
	static char *buffer;
	static size_t j, k, l;
	ssize_t q = 0;
	char **z = &(inf->arg), *ptr;

	_putchar(BUF_FLUSH);
	q = buf_command(inf, &buffer, &l);
	if (q == -1)
		return (-1);
	if (l)
	{
		k = j;
		ptr = buffer + j;

		chain_check(inf, buffer, &k, j, l);
		while (j < l)
		{
			if (test_delim(inf, buffer, &k))
				break;
			k++;
		}

		j = k + 1;
		if (j >= l)
		{
			j = l = 0;
			inf->cmd_buffer_type = CMD_NORM;
		}

		*z = ptr;
		return (string_len(ptr));
	}

	*z = buffer;
	return (q);
}

/**
 * read_buffer - a function that reads a buffer
 * @inf: parameter structure
 * @buffer: buffer
 * @j: the size
 *
 * Return: r
 */
ssize_t read_buffer(inf_t *inf, char *buffer, size_t *j)
{
	ssize_t q = 0;

	if (*j)
		return (0);
	q = read(inf->_readfd, buffer, READ_BUF_SIZE);
	if (q >= 0)
		*j = q;
	return (q);
}

/**
 * get_line - A function gets the next line of input from STDIN
 * @inf: parameter struct
 * @pt: address of pointer to buffer, preallocated or NULL
 * @len: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int get_line(inf_t *inf, char **pt, size_t *len)
{
	static char buf[READ_BUF_SIZE];
	static size_t j, l;
	size_t q;
	ssize_t b = 0, t = 0;
	char *m = NULL, *new = NULL, *ch;

	m = *pt;
	if (m && len)
		t = *len;
	if (j == l)
		j = l = 0;

	b = read_buffer(inf, buf, &l);
	if (b == -1 || (b == 0 && len == 0))
		return (-1);

	ch = str_char(buf + j, '\n');
	q = ch ? 1 + (unsigned int)(ch - buf) : l;
	new = realloc_mem(m, t, t ? t + q : q + 1);
	if (!new)
		return (m ? free(m), -1 : -1);

	if (t)
		str_cat(new, buf + j, q - j);
	else
		_strncopy(new, buf + j, q - j + 1);

	t += q - j;
	j = q;
	m = new;

	if (len)
		*len = t;
	*pt = m;
	return (t);
}

/**
 * block_copy - A function that blocks control-C
 * @num_signal: number of the signal
 *
 * Return: void
 */
void block_copy(__attribute__((unused))int num_signal)
{
	put_string("\n");
	put_string("$ ");
	_putchar(BUF_FLUSH);
}
