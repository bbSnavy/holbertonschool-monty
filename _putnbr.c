#include "monty.h"

/**
 * _putnbr - function
 * @v: i64
 * @f: int
*/
void	_putnbr(i64 v, int f)
{
	char	c;

	if (v < 0)
	{
		c = '-';
		write(f, &c, 1);
		_putnbr(-v, f);
	}
	else if (v < 10)
	{
		c = '0' + v;
		write(f, &c, 1);
	}
	else
	{
		_putnbr(v / 10, f);
		_putnbr(v % 10, f);
	}
}
