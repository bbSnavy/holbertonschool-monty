#include "monty.h"

/**
 * print_error_n - function
 * @v: u64
*/
void	print_error_n(u64 v)
{
	putnbr((i64) v, STDERR_FILENO);
}

/**
 * print_error - function
 * @str: char ptr
*/
void	print_error(char *str)
{
	write(STDERR_FILENO, str, _strlen((u8 *) str));
}
