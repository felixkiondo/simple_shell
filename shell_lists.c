#include "shell.h"

/**
 * list_add_node - a function that adds a node to the start of the list
 * @head: address of pointer to the head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *list_add_node(list_t **head, const char *str, int num)
{
	list_t *new;

	if (!head)
		return (NULL);
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	mem_set_((void *)new, 0, sizeof(list_t));
	new->num = num;
	if (str)
	{
		new->str = dup_string(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	new->next = *head;
	*head = new;
	return (new);
}

/**
 * node_end - a function that adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *node_end(list_t **head, const char *str, int num)
{
	list_t *new, *i;

	if (!head)
		return (NULL);

	i = *head;
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	mem_set_((void *)new, 0, sizeof(list_t));
	new->num = num;
	if (str)
	{
		new->str = dup_string(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	if (i)
	{
		while (i->next)
			i = i->next;
		i->next = new;
	}
	else
		*head = new;

	return (new);
}

/**
 * _printlist - a function that prints only the str element of linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t _printlist(const list_t *head)
{
	size_t j = 0;

	while (head)
	{
		put_string(head->str ? head->str : "(nil)");
		put_string("\n");
		head = head->next;
		j++;
	}
	return (j);
}

/**
 * delete_node - function that deletes node at given index
 * @h: address of pointer to first node
 * @i: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node(list_t **h, unsigned int i)
{
	list_t *n, *prev;
	unsigned int j = 0;

	if (!h || !*h)
		return (0);

	if (!i)
	{
		n = *h;
		*h = (*h)->next;
		free(n->str);
		free(n);
		return (1);
	}
	n = *h;
	while (n)
	{
		if (j == i)
		{
			prev->next = n->next;
			free(n->str);
			free(n);
			return (1);
		}
		j++;
		prev = n;
		n = n->next;
	}
	return (0);
}

/**
 * free_list - function that frees all nodes of a list
 * @h_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **h_ptr)
{
	list_t *n, *next_, *h;

	if (!h_ptr || !*h_ptr)
		return;
	h = *h_ptr;
	n = h;
	while (n)
	{
		next_ = n->next;
		free(n->str);
		free(n);
		n = next_;
	}
	*h_ptr = NULL;
}
