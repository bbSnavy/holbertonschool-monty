#include "monty.h"

/**
 * runtime_opcode - function
 * @str: []u8
 *
 * Return: opcode_t
 */
opcode_t	runtime_opcode(u8 *str)
{
	if (str == 0)
		return (0);
	if (_strlen(str) == 4 && _strcmp(str, (u8 *) "push") == 0)
		return (OP_PUSH);
	if (_strlen(str) == 4 && _strcmp(str, (u8 *) "pall") == 0)
		return (OP_PALL);
	if (_strlen(str) == 4 && _strcmp(str, (u8 *) "pint") == 0)
		return (OP_PINT);
	if (_strlen(str) == 3 && _strcmp(str, (u8 *) "pop") == 0)
		return (OP_POP);
	if (_strlen(str) == 4 && _strcmp(str, (u8 *) "swap") == 0)
		return (OP_SWAP);
	if (_strlen(str) == 3 && _strcmp(str, (u8 *) "add") == 0)
		return (OP_ADD);
	if (_strlen(str) == 3 && _strcmp(str, (u8 *) "nop") == 0)
		return (OP_NOP);
	return (0);
}
