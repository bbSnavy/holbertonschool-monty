#include "monty.h"

/**
 * execute_pall - function
 * @line: u8 ptr ptr
 * @index: u64
 * @stack: vector_t ptr
 *
 * Return: u8
*/
u8	execute_pall(u8 **line, u64 index, vector_t *stack)
{
	u64	l;
	u64	x;

	if (line == 0)
		return (0);
	if (stack == 0)
		return (0);
	l = stack->curr / (sizeof(int) / sizeof(u8));
	for (x = 0; x < l; x++)
	{
		putnbr((i64) * ((int *)(stack->data + (sizeof(int) * (l - 1 - x)))),
		       STDOUT_FILENO);
		print_char('\n');
	}
	(void) index;
	return (1);
}
