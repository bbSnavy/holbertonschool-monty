#include "monty.h"

/**
 * runtime_execute_pall
 * @w: *wrapper_t
 * @v: [][]u8
 *
 * Return: status_t
 */
status_t	runtime_execute_pall(wrapper_t *w, u8 **v)
{
	if (w == 0 || w->v == 0 || v == 0)
		return (STATUS_FAILED);
	return (wrapper_pall(w));
}
