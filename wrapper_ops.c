#include "monty.h"

/**
 * wrapper_push - function
 * @w: *wrapper_t
 * @v: int
 *
 * Return: status_t
 */
status_t	wrapper_push(wrapper_t *w, int v)
{
	if (w == 0 || w->v == 0)
		return (STATUS_FAILED);
	w->v = vector_write(w->v, &v, sizeof(v) / sizeof(u8));
	if (w->v == 0)
	{
		_print((u8 *) "Error: malloc failed\n", STDERR_FILENO);
		return (STATUS_FAILED);
	}
	return (STATUS_OK);
}

/**
 * wrapper_pall - function
 * @w: *wrapper_t
 *
 * Return: status_t
 */
status_t	wrapper_pall(wrapper_t *w)
{
	u64	l;
	u64	x;

	if (w == 0 || w->v == 0)
		return (STATUS_FAILED);
	l = w->v->curr / (sizeof(int) / sizeof(u8));
	for (x = 0; x < l; x++)
	{
		_putnbr((i64) * ((int *)(w->v->data + (sizeof(int) * (l - 1 - x)))),
			STDOUT_FILENO);
		_print((u8 *) "\n", STDOUT_FILENO);
	}
	return (STATUS_OK);
}

/**
 * wrapper_pint - function
 * @w: *wrapper_t
 *
 * Return: status_t
 */
status_t	wrapper_pint(wrapper_t *w)
{
	if (w == 0 || w->v == 0)
		return (STATUS_FAILED);
	if (w->v->curr == 0)
	{
		_print_line(w->l, (u8 *) "can't pint, stack empty\n", STDERR_FILENO);
		return (STATUS_FAILED);
	}
	_putnbr((i64) * ((int *)(&w->v->data[w->v->curr - sizeof(int)])),
		STDOUT_FILENO);
	_print((u8 *) "\n", STDOUT_FILENO);
	return (STATUS_OK);
}

/**
 * wrapper_pop - function
 * @w: *wrapper_t
 *
 * Return: status_t
 */
status_t	wrapper_pop(wrapper_t *w)
{
	u8	*v;
	u64	p;
	u64	x;

	if (w == 0 || w->v == 0)
		return (STATUS_FAILED);
	if (w->v->curr == 0)
	{
		_print_line(w->l, (u8 *) "can't pop an empty stack\n",
			    STDERR_FILENO);
		return (STATUS_FAILED);
	}
	p = sizeof(int) / sizeof(u8);
	v = (u8 *) malloc(w->v->curr - p);
	if (v == 0)
	{
		_print((u8 *) "Error: malloc failed\n", STDERR_FILENO);
		return (STATUS_FAILED);
	}
	for (x = 0; x < (w->v->curr - p); x++)
		v[x] = w->v->data[x];
	free(w->v->data);
	w->v->data = v;
	w->v->curr = w->v->curr - p;
	return (STATUS_OK);
}

/**
 * wrapper_swap - function
 * @w: *wrapper_t
 *
 * Return: status_t
 */
status_t	wrapper_swap(wrapper_t *w)
{
	u64	p;
	int	v;
	int	*a;
	int	*b;

	if (w == 0 || w->v == 0)
		return (STATUS_FAILED);
	p = sizeof(int) / sizeof(u8);
	if (w->v->curr < (p * 2))
	{
		_print_line(w->l, (u8 *) "can't swap, stack too short\n",
			    STDERR_FILENO);
		return (STATUS_FAILED);
	}
	a = (int *) (&w->v->data[w->v->curr - (p * 2)]);
	b = (int *) (&w->v->data[w->v->curr - (p * 1)]);
	v = *a;
	*a = *b;
	*b = v;
	return (STATUS_OK);
}
