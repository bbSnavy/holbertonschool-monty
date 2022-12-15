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

/**
 * execute_opcode - function
 * @str: u8 ptr
 *
 * Return: u8
*/
u8	execute_opcode(u8 *str)
{
	if (str == 0)
		return (0);
	if (_strlen(str) == 4 && _strcmp(str, (u8 *) "push") == 0)
		return (OP_PUSH);
	if (_strlen(str) == 4 && _strcmp(str, (u8 *) "pall") == 0)
		return (OP_PALL);
	if (_strlen(str) == 4 && _strcmp(str, (u8 *) "pint") == 0)
		return (OP_PINT);
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
	stack = vector_write(stack, &v, sizeof(v));
	if (stack == 0)
	{
		print_error("Error: malloc failed\n");
		return (2);
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

/**
 * execute_pint - function
 * @line: u8 ptr ptr
 * @index: u64
 * @stack: vector_t ptr
 *
 * Return: u8
*/
u8	execute_pint(u8 **line, u64 index, vector_t *stack)
{
	if (line == 0)
		return (0);
	if (stack == 0)
		return (0);
	if (stack->curr == 0)
	{
		print_error("L");
		print_error_n(index + 1);
		print_error(": can't pint, stack empty\n");
		return (2);
	}
	putnbr((i64) * ((int *)(&stack->data[stack->curr - sizeof(int)])),
	       STDOUT_FILENO);
	print_string("\n");
	(void) index;
	return (1);
}
