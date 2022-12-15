#include "monty.h"

/**
 * execute_line - function
 * @line: u8 ptr ptr
 * @index: u64
 * @stack: vector_t ptr
 *
 * Return: u8
*/
u8	execute_line(u8 **line, u64 index, vector_t *stack)
{
	if (line == 0)
		return (0);
	if (len_string_array(line) < 1)
		return (1);
	switch (execute_opcode(line[0]))
	{
		case OP_PUSH:
			return (execute_push(line, index, stack));
		case OP_PALL:
			return (execute_pall(line, index, stack));
		case OP_PINT:
			return (execute_pint(line, index, stack));
		default:
		{
			print_error("L");
			print_error_n(index + 1);
			print_error(": unknown instruction ");
			print_error((char *) line[0]);
			print_error("\n");
			return (2);
		}
	}
}

/**
 * execute_runtime - function
 * @lines: u8 ptr ptr
 * @stack: vector_t ptr
 *
 * Return: u8
*/
u8	execute_runtime(u8 **lines, vector_t *stack)
{
	u64	x;
	u8	**v;
	u8	c;

	for (x = 0; lines[x]; x++)
	{
		v = _strsplit(lines[x], (u8 *) " \t\r\n");
		if (v == 0)
		{
			print_error("Error: malloc failed\n");
			return (1);
		}
		c = execute_line(v, x, stack);
		free_string_array(v);
		if (c == 0)
			break;
		if (c == 1)
			continue;
		if (c == 2)
			return (1);
	}
	return (0);
}

/**
 * execute_process - function
 * @file: char ptr
 * @stack: vector_t ptr
 *
 * Return: int
*/
int	execute_process(char *file, vector_t *stack)
{
	int	f;
	u8	*s;
	u8	**v;
	u8	c;

	f = open_file(file, O_RDONLY);
	if (f == -1)
	{
		print_error("Error: Can't open file ");
		print_error(file);
		print_error("\n");
		return (EXIT_FAILURE);
	}
	s = read_file(f);
	close(f);
	if (s == 0)
	{
		print_error("Error: Can't open file ");
		print_error(file);
		print_error("\n");
		return (EXIT_FAILURE);
	}
	v = _strsplit_special(s, (u8 *) "\n");
	free(s);
	if (v == 0)
	{
		print_error("Error: malloc failed\n");
		return (EXIT_FAILURE);
	}
	c = execute_runtime(v, stack);
	free_string_array(v);
	if (c != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * main - function
 * @argc: int
 * @argv: char ptr ptr
 *
 * Return: int
*/
int	main(int argc, char **argv)
{
	vector_t	*stack;
	int		c;

	stack = vector_new(0);
	if (stack == 0)
	{
		print_error("Error: malloc failed\n");
		return (EXIT_FAILURE);
	}
	if (argc != 2)
	{
		vector_free(stack);
		print_error("USAGE: monty file\n");
		return (EXIT_FAILURE);
	}
	c = execute_process(argv[1], stack);
	vector_free(stack);
	return (c);
}
