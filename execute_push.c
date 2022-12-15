#include "monty.h"

/**
 * execute_push - function
 * @line: u8 ptr ptr
 * @index: u64
 * @stack: vector_t ptr
 *
 * Return: u8
*/
u8	execute_push(u8 **line, u64 index, vector_t *stack)
{
	i32	v;

	if (line == 0)
		return (0);
	if (stack == 0)
		return (0);
	if (len_string_array(line) < 2)
	{
		print_error("L");
		print_error_n(index + 1);
		print_error(": usage: push integer\n");
		return (2);
	}
	if (is_number(line[1]) != 1)
	{
		print_error("L");
		print_error_n(index + 1);
		print_error(": usage: push integer\n");
		return (2);
	}
	v = (i32) atoi((char *) line[1]);
	stack = vector_write(stack, &v, (sizeof(v) / sizeof(u8)));
	if (stack == 0)
	{
		print_error("Error: malloc failed\n");
		return (2);
	}
	return (1);
}
