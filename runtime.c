#include "monty.h"

/**
 * runtime_line - function
 * @w: *wrapper_t
 * @s: []u8
 *
 * Return: status_t
 */
status_t	runtime_line(wrapper_t *w, u8 *s)
{
	status_t	r;
	u8		**v;
	opcode_t	o;

	v = _strsplit(s, (u8 *) " \t\r");
	if (v == 0)
	{
		_print((u8 *) "Error: malloc failed\n", STDERR_FILENO);
		return (STATUS_FAILED);
	}
	if (len_string_array(v) < 1)
	{
		free_string_array(v);
		return (STATUS_OK);
	}
	r = STATUS_FAILED;
	o = runtime_opcode(v[0]);
	if (o == 0)
	{
		_print_line(w->l, (u8 *) "unknown instruction ",
			    STDERR_FILENO);
		_print(v[0], STDERR_FILENO);
		_print((u8 *) "\n", STDERR_FILENO);
	}
	else if (o == OP_PUSH)
		r = runtime_execute_push(w, v);
	else if (o == OP_PALL)
		r = runtime_execute_pall(w, v);
	free_string_array(v);
	return (r);
}

/**
 * runtime_init - function
 * @v: **vector_t
 * @f: *int
 * @p: *[]char
 *
 * Return: status_t
 */
status_t	runtime_init(vector_t **v, int *f, char **p)
{
	*v = vector_new(0);
	if ((*v) == 0)
	{
		_print((u8 *) "Error: malloc failed\n", STDERR_FILENO);
		return (STATUS_FAILED);
	}
	*f = open(*p, O_RDONLY);
	if ((*f) == -1)
	{
		_print((u8 *) "Error: Can't open file ", STDERR_FILENO);
		_print((u8 *) (*p), STDERR_FILENO);
		_print((u8 *) "\n", STDERR_FILENO);
		return (STATUS_FAILED);
	}
	return (STATUS_OK);
}

/**
 * runtime - function
 * @w: *wrapper_t
 * @p: []char
 *
 * Return: int
 */
int	runtime(wrapper_t *w, char *p)
{
	vector_t	*v;
	int		f;
	char		c;
	i64		l;
	u8		*s;

	if (runtime_init(&v, &f, &p) == STATUS_FAILED)
		return (EXIT_FAILURE);
	while (1)
	{
		l = read(f, &c, 1);
		if (l == -1)
			return (runtime_close_v(f, v));
		if (l < 1)
		{
			v = vector_free(v);
			break;
		}
		if (_strchr((u8 *) "\n", c) != 0)
		{
			s = vector_consume(v);
			v = vector_new(0);
			if (s == 0 || v == 0)
				return (runtime_close_v(runtime_error_f(f, "Error: malloc failed\n"), v));
			if ((_strlen(s) > 0) && (runtime_line(w, s) == STATUS_FAILED))
				return (runtime_close_s_v(f, s, v));
			free(s);
			w->l = w->l + 1;
		}
		else if (vector_write(v, &c, 1) == 0)
			return (runtime_close(runtime_error_f(f, "Error: malloc failed\\n")));
	}
	s = vector_consume(v);
	if (_strlen(s) > 0)
		if (runtime_line(w, s) == STATUS_FAILED)
			return (runtime_close_s(f, s));
	free(s);
	return (EXIT_SUCCESS);
}
