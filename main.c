#include "monty.h"

/**
 * main - function
 * @argc: int
 * @argv: [][]char
 *
 * Return: int
 */
int	main(int argc, char **argv)
{
	int		r;
	wrapper_t	*w;

	r = EXIT_SUCCESS;
	w = wrapper_new(0);
	if (w == 0)
	{
		_print((u8 *) "Error: malloc failed\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (argc != 2)
	{
		wrapper_free(w);
		_print((u8 *) "USAGE: monty file\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	r = runtime(w, argv[1]);
	wrapper_free(w);
	return (r);
}
