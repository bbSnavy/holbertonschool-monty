#include "monty.h"

/**
 * print_char - function
 * @c: char
*/
void	print_char(char c)
{
	write(1, &c, 1);
}

/**
 * print_string - function
 * @str: char ptr
*/
void	print_string(char *str)
{
	if (str == 0)
		return;
	write(STDOUT_FILENO, str, _strlen((u8 *) str));
}

/**
 * open_file - function
 * @path: char ptr
 * @mode: int
 *
 * Return: int
*/
int	open_file(char *path, int mode)
{
	int	r;

	r = open(path, mode);
	if (r == -1)
		return (-1);
	return (r);
}

/**
 * read_file - function
 * @f: int
 *
 * Return: []u8
*/
u8	*read_file(int f)
{
	vector_t	*v;
	u8		*b;
	i64		l;

	b = (u8 *) malloc(sizeof(u8) * (BUFFER_SIZE));
	if (b == 0)
		return (0);
	v = vector_new(0);
	if (v == 0)
	{
		free(b);
		return (0);
	}
	while (1)
	{
		l = read(f, b, BUFFER_SIZE);
		if (l == -1)
		{
			free(b);
			vector_free(v);
			return (0);
		}
		if (l == 0)
		{
			free(b);
			vector_free(v);
			return (0);
		}
		vector_write(v, b, l);
		if (l < BUFFER_SIZE)
			break;
	}
	free(b);
	return (vector_consume(v));
}
