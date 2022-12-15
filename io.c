#include "monty.h"

/**
 * _print - function
 * @s: []u8
 * @f: int
 */
void	_print(u8 *s, int f)
{
	write(f, s, _strlen(s));
}

/**
 * _print_line - function
 * @l: u64
 * @s: []u8
 * @f: int
 */
void	_print_line(u64 l, u8 *s, int f)
{
	_print((u8 *) "L", f);
	_putnbr((i64) l + 1, f);
	_print((u8 *) ": ", f);
	_print(s, f);
}
