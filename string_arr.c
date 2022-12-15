#include "monty.h"

/**
 * free_string_array - function
 * @v: u8 ptr ptr
 *
 * Return: void ptr
*/
void	*free_string_array(u8 **v)
{
	u64	x;

	if (v == 0)
		return (0);
	for (x = 0; v[x]; x++)
		free(v[x]);
	free(v);
	return (0);
}

/**
 * len_string_array - function
 * @v: u8 ptr ptr
 *
 * Return: u64
*/
u64	len_string_array(u8 **v)
{
	u64	x;

	if (v == 0)
		return (0);
	for (x = 0; v[x]; x++)
		;
	return (x);
}
