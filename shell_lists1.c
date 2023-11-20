#include "shell.h"

/**
 * linklist_len - function that determines length of linked list
 * @ptr: pointer to first node
 *
 * Return: size of list
 */
size_t linklist_len(const list_t *ptr)
{
	size_t j = 0;

	while (ptr)
	{
		ptr = ptr->next;
		j++;
	}
	return (j);
}

/**
 * list_array - a function that returns an array of strings of the list->str
 * @h: pointer to the first node
 *
 * Return: array of strings
 */
char **list_array(list_t *h)
{
	list_t *n = h;
	size_t j = linklist_len(h), k;
	char **s1;
	char *s;

	if (!h || !j)
		return (NULL);
	s1 = malloc(sizeof(char *) * (j + 1));
	if (!s1)
		return (NULL);
	for (j = 0; n; n = n->next, j++)
	{
		s = malloc(string_len(n->str) + 1);
		if (!s)
		{
			for (k = 0; k < j; k++)
				free(s1[k]);
			free(s1);
			return (NULL);
		}

		s = _strcopy(s, n->str);
		s1[j] = s;
	}
	s1[j] = NULL;
	return (s1);
}


/**
 * list_print - A function that prints all elements of a list_t linked list
 * @head: pointer to the first node
 *
 * Return: size of list
 */
size_t list_print(const list_t *head)
{
	size_t j = 0;

	while (head)
	{
		put_string(convertnum_function(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		put_string(head->str ? head->str : "(nil)");
		put_string("\n");
		head = head->next;
		j++;
	}
	return (j);
}

/**
 * begin_node - a function that returns node whose string starts with prefix
 * @n: pointer to the list head
 * @pref: the string to match
 * @ch: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *begin_node(list_t *n, char *pref, char ch)
{
	char *ptr = NULL;

	while (n)
	{
		ptr = haystack_check(n->str, pref);
		if (ptr && ((ch == -1) || (*ptr == ch)))
			return (n);
		n = n->next;
	}
	return (NULL);
}

/**
 * index_node - function that gets the index of a node
 * @h: pointer to the list head
 * @n: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t index_node(list_t *h, list_t *n)
{
	size_t j = 0;

	while (h)
	{
		if (h == n)
			return (j);
		h = h->next;
		j++;
	}
	return (-1);
}
