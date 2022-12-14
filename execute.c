#include "monty.h"

/**
 * execute_opcode - function
 * @str: u8
 *
 * Return: u8
*/
u8	execute_opcode(u8 *str)
{
	if (str == 0)
		return (0);
	if (_strcmp(str, (u8 *) "push") == 0)
		return (OP_PUSH);
	if (_strcmp(str, (u8 *) "pall") == 0)
		return (OP_PALL);
	return (0);
}

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
		return (0);
	}
	v = (i32) atoi((char *) line[1]);
	stack = vector_write(stack, &v, sizeof(v));
	if (stack == 0)
	{
		print_error("Error: malloc failed\n");
		return (0);
	}
	return (1);
}

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
