#include "monty.h"

/**
 * runtime_execute_pop - function
 * @w: *wrapper_t
 * @v: [][]u8
 *
 * Return: status_t
 */
status_t	runtime_execute_pop(wrapper_t *w, u8 **v)
{
	if (w == 0 || w->v == 0 || v == 0)
		return (STATUS_FAILED);
	return (wrapper_pop(w));
}
