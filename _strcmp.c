#include "monty.h"

i32	_strcmp(u8 *a, u8 *b)
{
	u64	x;

	if (a == 0 || b == 0)
		return (-1);
	for (x = 0; a[x] && b[x]; x++)
		if (a[x] != b[x])
			return (a[x] - b[x]);
	return (0);
}
