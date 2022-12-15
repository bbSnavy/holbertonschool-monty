#ifndef MONTY_H
# define MONTY_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <fcntl.h>

# define i8  int8_t
# define u8  uint8_t
# define i32 int32_t
# define u32 uint32_t
# define i64 int64_t
# define u64 uint64_t

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int		n;
	struct stack_s	*prev;
	struct stack_s	*next;
}	stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct	instruction_s
{
	char	*opcode;
	void	(*f)(stack_t **stack, unsigned int line_number);
}	instruction_t;

/**
 * struct vector_s - struct
 * @data: []u8
 * @size: u64
 * @curr: u64
*/
typedef struct	vector_s
{
	u8	*data;
	u64	size;
	u64	curr;
}	vector_t;

/**
 * struct wrapper_s - struct
 * @v: *vector_t
 * @l: u64
*/
typedef struct	wrapper_s
{
	vector_t	*v;
	u64		l;
}	wrapper_t;

typedef int	status_t;
# define STATUS_OK      (1)
# define STATUS_WARNING (2)
# define STATUS_FAILED  (3)

typedef int	opcode_t;
# define OP_PUSH (1)
# define OP_PALL (2)
# define OP_PINT (3)
# define OP_POP  (4)
# define OP_SWAP (5)

vector_t	*vector_new(vector_t *);
vector_t	*vector_free(vector_t *);
vector_t	*vector_write(vector_t *, void *src, u64 len);
vector_t	*vector_read(vector_t *, void *dst, u64 size);
u8		*vector_consume(vector_t *);
wrapper_t	*wrapper_new(wrapper_t *);
wrapper_t	*wrapper_free(wrapper_t *);
status_t	wrapper_push(wrapper_t *, int v);
status_t	wrapper_pall(wrapper_t *);
int		runtime(wrapper_t *, char *p);
status_t	runtime_line(wrapper_t *, u8 *s);
opcode_t	runtime_opcode(u8 *str);
status_t	runtime_execute_push(wrapper_t *, u8 **v);
status_t	runtime_execute_pall(wrapper_t *, u8 **v);
u64		_strlen(u8 *);
i32		_strcmp(u8 *, u8 *);
u8		*_strchr(u8 *, u8);
u8		**_strsplit(u8 *str, u8 *lim);
u8		is_number(u8 *str);
void		*free_string_array(u8 **v);
u64		len_string_array(u8 **v);
u8		is_number(u8 *str);
void		_putnbr(i64 v, int f);
void		_print(u8 *s, int f);
void		_print_line(u64 l, u8 *s, int f);
int		main(int argc, char **argv);

#endif
