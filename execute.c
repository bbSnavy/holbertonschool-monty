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
	return (1);
}

/**
 * execute_pop - function
 * @line: u8 ptr ptr
 * @index: u64
 * @stack: vector_t ptr
 *
 * Return: u8
*/
u8	execute_pop(u8 **line, u64 index, vector_t *stack)
{
	u64	p;
	u8	*v;
	u64	x;

	if (line == 0)
		return (0);
	if (stack == 0)
		return (0);
	if (stack->curr == 0)
	{
		print_error("L");
		print_error_n(index + 1);
		print_error(": can't pop an empty stack\n");
		return (2);
	}
	p = sizeof(int) / sizeof(u8);
	v = (u8 *) malloc(stack->curr - p);
	if (v == 0)
	{
		print_error("Error: malloc failed\n");
		return (2);
	}
	for (x = 0; x < (stack->curr - p); x++)
		v[x] = stack->data[x];
	free(stack->data);
	stack->data = v;
	stack->curr = stack->curr - p;
	return (1);
}

/**
 * execute_swap - function
 * @line: u8 ptr ptr
 * @index: u64
 * @stack: vector_t ptr
 *
 * Return: u8
*/
u8	execute_swap(u8 **line, u64 index, vector_t *stack)
{
	u64	p;
	int	v;
	int	*a;
	int	*b;

	if (line == 0)
		return (0);
	if (stack == 0)
		return (0);
	p = sizeof(int) / sizeof(u8);
	if (stack->curr < (p * 2))
	{
		print_error("L");
		print_error_n(index + 1);
		print_error(": can't swap, stack too short\n");
		return (2);
	}
	a = (int *) (&stack->data[stack->curr - (p * 2)]);
	b = (int *) (&stack->data[stack->curr - (p * 1)]);
	v = *a;
	*a = *b;
	*b = v;
	return (1);
}
