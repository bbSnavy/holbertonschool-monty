#include "monty.h"

void	_print(u8 *s, int f)
{
	write(f, s, _strlen(s));
}

void	_print_line(u64 l, u8 *s, int f)
{
	_print((u8 *) "L", f);
	_putnbr((i64) l + 1, f);
	_print((u8 *) ": ", f);
	_print(s, f);
}
