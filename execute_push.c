#include "monty.h"

/**
 * runtime_execute_push - function
 * @w: *wrapper_t
 * @v: [][]u8
 *
 * Return: status_t
 */
status_t	runtime_execute_push(wrapper_t *w, u8 **v)
{
	if (w == 0 || w->v == 0 || v == 0)
		return (STATUS_FAILED);
	if ((len_string_array(v) < 2) || (is_number(v[1]) != 1))
	{
		_print_line(w->l, (u8 *) "usage: push integer\n",
			    STDERR_FILENO);
		return (STATUS_FAILED);
	}
	return (wrapper_push(w, atoi((char *) v[1])));
}
