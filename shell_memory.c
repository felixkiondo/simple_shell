#include "shell.h"

/**
 * free_pointer - A function that frees a pointer and NULLs the address
 * @p: The address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int free_pointer(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
