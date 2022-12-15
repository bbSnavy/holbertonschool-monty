#include "monty.h"

/**
 * _strsplit_count - function
 * @str: u8 ptr
 * @lim: u8 ptr
 *
 * Return: u64
*/
u64	_strsplit_count(u8 *str, u8 *lim)
{
	u64	r;
	u64	m;
	u64	x;

	r = 0;
	m = 0;
	if (str == 0)
		return (0);
	if (lim == 0)
		return (0);
	for (x = 0; str[x]; x++)
	{
		if (_strchr(lim, str[x]))
		{
			if (m > 0)
				r++;
			m = 0;
		}
		else
			m++;
	}
	r += m > 0;
	return (r);
}

/**
 * _strsplit - function
 * @str: u8 ptr
 * @lim: u8 ptr
 *
 * Return: u8 ptr ptr
*/
u8	**_strsplit(u8 *str, u8 *lim)
{
	u8		**r;
	vector_t	*v;
	u64		s;
	u64		m;
	u64		x;

	if (str == 0 || lim == 0)
		return (0);
	r = (u8 **) malloc(sizeof(u8 *) * (_strsplit_count(str, lim) + 1));
	if (r == 0)
		return (0);
	s = 0;
	m = 0;
	v = vector_new(0);
	for (x = 0; str[x]; x++)
	{
		if (_strchr(lim, str[x]))
		{
			if (m > 0)
			{
				r[s++] = vector_consume(v);
				v = vector_new(0);
			}
			else
				v = vector_new(v);
			m = 0;
		}
		else
		{
			vector_write(v, &str[x], 1);
			m++;
		}
	}
	if (m > 0)
		r[s++] = vector_consume(v);
	else
		vector_free(v);
	r[s] = 0;
	return (r);
}

/**
 * _strsplit_special_count - function
 * @str: u8 ptr
 * @lim: u8 ptr
 *
 * Return: u64
*/
u64	_strsplit_special_count(u8 *str, u8 *lim)
{
	u64	r;
	u64	x;

	r = 0;
	if (str == 0)
		return (0);
	if (lim == 0)
		return (0);
	for (x = 0; str[x]; x++)
		if (_strchr(lim, str[x]))
			r++;
	r++;
	return (r);
}

/**
 * _strsplit_special - function
 * @str: u8 ptr
 * @lim: u8 ptr
 *
 * Return: u8 ptr ptr
*/
u8	**_strsplit_special(u8 *str, u8 *lim)
{
	u8		**r;
	vector_t	*v;
	u64		s;
	u64		x;

	if (str == 0 || lim == 0)
		return (0);
	r = (u8 **) malloc(sizeof(u8 *) * (_strsplit_special_count(str, lim) + 1));
	if (r == 0)
		return (0);
	for (x = 0; x < (_strsplit_special_count(str, lim) + 1); x++)
		r[x] = 0;
	s = 0;
	v = vector_new(0);
	if (v == 0)
		return ((u8 **) free_string_array(r));
	for (x = 0; str[x]; x++)
	{
		if (_strchr(lim, str[x]))
		{
			r[s++] = vector_consume(v);
			if (r[s - 1] == 0)
				return ((u8 **) free_string_array(r));
			v = vector_new(0);
			if (v == 0)
				return ((u8 **) free_string_array(r));
		}
		else
			if (vector_write(v, &str[x], 1) == 0)
				return ((u8 **) free_string_array(r));
	}
	r[s++] = vector_consume(v);
	if (r[s - 1] == 0)
		return ((u8 **) free_string_array(r));
	r[s] = 0;
	return (r);
}
