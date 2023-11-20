#include "shell.h"

/**
 * history_file - A function that gets the history file
 * @inf: parameter structure
 *
 * Return: allocated string containg history file
 */

char *history_file(inf_t *inf)
{
	char *buffer, *d;

	d = get_env(inf, "HOME=");
	if (!d)
		return (NULL);
	buffer = malloc(sizeof(char) * (string_len(d) + string_len(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcopy(buffer, d);
	string_cat(buffer, "/");
	string_cat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_existing - creates a file, or appends to an existing file
 * @inf: the parameter structure
 *
 * Return: 1 on success, else -1
 */
int write_existing(inf_t *inf)
{
	ssize_t fd;
	char *filename = history_file(inf);
	list_t *n = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (n = inf->his_tory; n; n = n->next)
	{
		puts_fd(n->str, fd);
		put_fd('\n', fd);
	}
	put_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_existing - reads history from file
 * @inf: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_existing(inf_t *inf)
{
	int j, l = 0, count = 0;
	ssize_t fd, read_len, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filename = history_file(inf);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	read_len = read(fd, buffer, fsize);
	buffer[fsize] = 0;
	if (read_len <= 0)
		return (free(buffer), 0);
	close(fd);
	for (j = 0; j < fsize; j++)
		if (buffer[j] == '\n')
		{
			buffer[j] = 0;
			add_history_list(inf, buffer + l, count++);
			l = j + 1;
		}
	if (l != j)
		add_history_list(inf, buffer + l, count++);
	free(buffer);
	inf->hist_count = count;
	while (inf->hist_count-- >= HIST_MAX)
		delete_node(&(inf->his_tory), 0);
	history_renumber(inf);
	return (inf->hist_count);
}

/**
 * add_history_list - function that adds entry to a history linked list
 * @inf: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @count: the history linecount, histcount
 *
 * Return: Always 0
 */
int add_history_list(inf_t *inf, char *buffer, int count)
{
	list_t *n = NULL;

	if (inf->his_tory)
		n = inf->his_tory;
	node_end(&n, buffer, count);

	if (!inf->his_tory)
		inf->his_tory = n;
	return (0);
}

/**
 * history_renumber - function that renumbers the history linked list
 * @inf: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int history_renumber(inf_t *inf)
{
	list_t *n = inf->his_tory;
	int j = 0;

	while (n)
	{
		n->num = j++;
		n = n->next;
	}

	return (inf->hist_count = j);
}
