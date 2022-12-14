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
	u8 o;

	if (line == 0)
		return (0);
	if (len_string_array(line) < 1)
		return (1);
	o = execute_opcode(line[0]);
	if (o == 0)
	{
		print_error("L");
		print_error_n(index);
		print_error(": unknown instruction <opcode>\n");
		return (0);
	}
	switch (o)
	{
		case OP_PUSH:
			return (execute_push(line, index, stack));
		case OP_PALL:
			return (execute_pall(line, index, stack));
	}
	return (1);
}

/**
 * execute_runtime - function
 * @content: u8 ptr
 * @lines: u8 ptr ptr
 * @stack: vector_t ptr
 *
 * Return: u8
*/
u8	execute_runtime(u8 *content, u8 **lines, vector_t *stack)
{
	u64	x;
	u8	**v;
	u8	c;

	for (x = 0; lines[x]; x++)
	{
		v = _strsplit(lines[x], (u8 *) " ");
		if (v == 0)
		{
			free_string_array(lines);
			free(content);
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
*/
void	execute_process(char *file, vector_t *stack)
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
		exit(EXIT_FAILURE);
	}
	s = read_file(f);
	if (s == 0)
	{
		print_error("Error: Can't open file ");
		print_error(file);
		print_error("\n");
		exit(EXIT_FAILURE);
	}
	v = _strsplit_special(s, (u8 *) "\n");
	if (v == 0)
	{
		free(s);
		print_error("Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	c = execute_runtime(s, v, stack);
	free_string_array(v);
	if (c != 0)
		exit(EXIT_FAILURE);
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

	stack = vector_new(0);
	if (stack == 0)
	{
		print_error("Error: malloc failed\n");
		return (EXIT_FAILURE);
	}
	if (argc != 2)
	{
		print_error("USAGE: monty file\n");
		return (EXIT_FAILURE);
	}
	execute_process(argv[1], stack);
	return (0);
}
