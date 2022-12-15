#include "monty.h"

/**
 * is_number - function
 * @str: u8 ptr
 *
 * Return: u8
 */
u8	is_number(u8 *str)
{
	u64	x;

	if (str == 0)
		return (0);
	for (x = 0; str[x]; x++)
		if (_strchr((u8 *) "-0123456789", str[x]) == 0)
			return (0);
	return (1);
}
