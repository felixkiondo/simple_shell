#include "shell.h"

/**
 **mem_set_ - A function that fills memory with a constant byte
 *@q: pointer to the memory area
 *@t: the byte to fill the memory area with
 *@num: the amount of bytes to be filled
 *Return: (q) a pointer to the memory area q
 */
char *mem_set_(char *q, char t, unsigned int num)
{
	unsigned int j;

	for (j = 0; j < num; j++)
		q[j] = t;
	return (q);
}

/**
 * free_strings - A function that frees a string of strings
 * @ss: string of strings
 */
void free_strings(char **ss)
{
	char **b = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(b);
}

/**
 * realloc_mem - function that reallocates a block of memory
 * @t: pointer to previous malloc'ated block
 * @o: byte size of the previous block
 * @n: byte size of the new block
 *
 * Return: pointer to the old block.
 */
void *realloc_mem(void *t, unsigned int o, unsigned int n)
{
	char *ptr;

	if (!t)
		return (malloc(n));
	if (!n)
		return (free(t), NULL);
	if (n == o)
		return (t);

	ptr = malloc(n);
	if (!ptr)
		return (NULL);

	o = o < n ? o : n;
	while (o--)
		ptr[o] = ((char *)t)[o];
	free(t);
	return (ptr);
}
