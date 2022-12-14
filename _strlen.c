#include "monty.h"

/**
 * _strlen - function
 * @str: u8 ptr
 *
 * Return: u64
*/
u64	_strlen(u8 *str)
{
	u64	x;

	if (str == 0)
		return (0);
	for (x = 0; str[x]; x++)
		;
	return (x);
}
