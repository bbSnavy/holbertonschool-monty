#include "monty.h"

/**
 * wrapper_add - function
 * @w: *wrapper_t
 *
 * Return: status_t
 */
status_t	wrapper_add(wrapper_t *w)
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
		_print_line(w->l, (u8 *) "can't add, stack too short\n",
			    STDERR_FILENO);
		return (STATUS_FAILED);
	}
	a = (int *) (&w->v->data[w->v->curr - (p * 2)]);
	b = (int *) (&w->v->data[w->v->curr - (p * 1)]);
	v = *a + *b;
	if (wrapper_pop(w) == STATUS_FAILED)
		return (STATUS_FAILED);
	if (wrapper_pop(w) == STATUS_FAILED)
		return (STATUS_FAILED);
	return (wrapper_push(w, v));
}
