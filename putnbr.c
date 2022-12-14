#include "monty.h"

/**
 * putnbr - function
 * @v: i64
 * @f: int
*/
void	putnbr(i64 v, int f)
{
	char	c;

	if (v < 0)
	{
		c = '-';
		write(f, &c, 1);
		putnbr(-v, f);
	}
	else if (v < 10)
	{
		c = '0' + v;
		write(f, &c, 1);
	}
	else
	{
		putnbr(v / 10, f);
		putnbr(v % 10, f);
	}
}
