#include "monty.h"

/**
 * runtime_close - function
 * @f: int
 *
 * Return: int
 */
int	runtime_close(int f)
{
	close(f);
	return (EXIT_FAILURE);
}

/**
 * runtime_close_s - function
 * @f: int
 * @s: []u8
 *
 * Return: int
 */
int	runtime_close_s(int f, u8 *s)
{
	free(s);
	return (runtime_close(f));
}

/**
 * runtime_close_v - function
 * @f: int
 * @v: *vector_t
 *
 * Return: int
 */
int	runtime_close_v(int f, vector_t *v)
{
	vector_free(v);
	return (runtime_close(f));
}

/**
 * runtime_close_s_v - function
 * @f: int
 * @s: []u8
 * @v: *vector_t
 *
 * Return: int
 */
int	runtime_close_s_v(int f, u8 *s, vector_t *v)
{
	free(s);
	vector_free(v);
	return (runtime_close(f));
}

/**
 * runtime_error_f - function
 * @f: int
 * @s: []char
 *
 * Return: int
 */
int	runtime_error_f(int f, char *s)
{
	_print((u8 *) s, STDERR_FILENO);
	return (f);
}
