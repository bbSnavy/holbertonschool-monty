#include "monty.h"

status_t	runtime_execute_pall(wrapper_t *w, u8 **v)
{
	if (w == 0 || w->v == 0 || v == 0)
		return (STATUS_FAILED);
	return (wrapper_pall(w));
}

status_t	runtime_line(wrapper_t *w, u8 *s)
{
	status_t 	r;
	u8		**v;
	opcode_t	o;

	v = _strsplit(s, (u8 *) " \t\r");
	if (v == 0)
	{
		_print((u8 *) "Error: malloc failed\n", STDERR_FILENO);
		return (STATUS_FAILED);
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

int	runtime(wrapper_t *w, char *p)
{
	vector_t	*v;
	int		f;
	char 		c;
	i64		l;
	u8		*s;

	v = vector_new(0);
	if (v == 0)
	{
		_print((u8 *) "Error: malloc failed\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	f = open(p, O_RDONLY);
	if (f == -1)
	{
		_print((u8 *) "Error: Can't open file ", STDERR_FILENO);
		_print((u8 *) p, STDERR_FILENO);
		_print((u8 *) "\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (1)
	{
		l = read(f, &c, 1);
		if (l == -1)
		{
			close(f);
			vector_free(v);
			return (EXIT_FAILURE);
		}
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
			{
				close(f);
				vector_free(v);
				_print((u8 *) "Error: malloc failed\n",
				       STDERR_FILENO);
				return (EXIT_FAILURE);
			}
			if (_strlen(s) > 0)
				if (runtime_line(w, s) == STATUS_FAILED)
				{
					free(s);
					vector_free(v);
					close(f);
					return (EXIT_FAILURE);
				}
			free(s);
			w->l = w->l + 1;
		}
		else if (vector_write(v, &c, 1) == 0)
		{
			close(f);
			_print((u8 *) "Error: malloc failed\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	s = vector_consume(v);
	if (_strlen(s) > 0)
		if (runtime_line(w, s) == STATUS_FAILED)
		{
			free(s);
			close(f);
			return (EXIT_FAILURE);
		}
	free(s);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	int		r;
	wrapper_t	*w;

	r = EXIT_SUCCESS;
	w = wrapper_new(0);
	if (w == 0)
	{
		_print((u8 *) "Error: malloc failed\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (argc != 2)
	{
		wrapper_free(w);
		_print((u8 *) "USAGE: monty file\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	r = runtime(w, argv[1]);
	wrapper_free(w);
	return (r);
}
