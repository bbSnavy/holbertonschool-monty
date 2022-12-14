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

vector_t	*vector_new(vector_t *);
vector_t	*vector_free(vector_t *);
vector_t	*vector_write(vector_t *, void *src, u64 len);
vector_t	*vector_read(vector_t *, void *dst, u64 size);
u8		*vector_consume(vector_t *);
u64		_strlen(u8 *);
i32		_strcmp(u8 *, u8 *);
u8		*_strchr(u8 *, u8);
u8		**_strsplit(u8 *str, u8 *lim);
void		free_string_array(u8 **v);
u64		len_string_array(u8 **v);
void		putnbr(i64 v, int f);
void		print_char(char);
void		print_string(char *);
void		print_error(char *);
void		print_error_n(u64 v);
int		open_file(char *path, int mode);
u8		*read_file(int f);
u8		execute_opcode(u8 *);
u8		execute_push(u8 **line, u64 index, vector_t *stack);
u8		execute_pall(u8 **line, u64 index, vector_t *stack);
int		main(int argc, char **argv);

# define BUFFER_SIZE (1024)
# define OP_PUSH (1)
# define OP_PALL (2)

#endif
