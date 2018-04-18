#include "sh21.h"

int						ast_is_shell_cmd(t_token_type type)
{
	if (type == WORD)
		return (1);
	else if (type == ASSIGNMENT_WORD)
		return (2);
	else if (type == PIPE)
		return (3);
	else if (type == While)
		return (4);
	else if (type == If)
		return (5);
	else
		return (0);
}
