#include "monty.h"

/**
 * wrapper_new - function
 * @w: *wrapper_t
 *
 * Return: *wrapper_t
 */
wrapper_t	*wrapper_new(wrapper_t *w)
{
	w = wrapper_free(w);
	w = (wrapper_t *) malloc(sizeof(wrapper_t));
	if (w == 0)
		return (0);
	w->v = vector_new(0);
	w->l = 0;
	if (w->v == 0)
	{
		free(w);
		return (0);
	}
	return (w);
}

/**
 * wrapper_free - function
 * @w: *wrapper_t
 *
 * Return: *wrapper_t
 */
wrapper_t	*wrapper_free(wrapper_t *w)
{
	if (w == 0)
		return (0);
	if (w->v)
		vector_free(w->v);
	free(w);
	return (0);
}
