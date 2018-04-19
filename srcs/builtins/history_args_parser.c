#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sh21.h"

#define AF			1 << 0
#define WF			1 << 1
#define RF			1 << 2
#define NF			1 << 3
#define D_ERR		1 << 4
#define AWRN_ERR	1 << 5
#define INVARG		1 << 6

// t_hist_args		*args_create(void)
// {
// 	t_hist_args *args = malloc(sizeof(t_hist_args));
// 	args->c = 0;
// 	args->d = 0;
// 	args->d_val = 0;
// 	args->p = 0;
// 	args->s = 0;
// 	args->awrn = 0;
// 	args->err = 0;
// 	return (args);
// }

#define MULTIPLE_AWRN -1
#define INVALID_CHAR -42
#define INVALID_OFFSET 15

static void		awrn_handle(t_hist_args *args, char *str)
{
	if (*str == 'a' && !args->awrn)
		args->awrn = 'a';
	else if (*str == 'w' && !args->awrn)
		args->awrn = 'w';
	else if (*str == 'r' && !args->awrn)
		args->awrn = 'r';
	else if (*str == 'n' && !args->awrn)
		args->awrn = 'n';
}

int				handle_arg(t_hist_args *args, char **arg)
{
	char *str = *arg;
	while (*str)
	{
		if (!ft_strchr("awrncdps", *str))
			return ((args->err = INVALID_CHAR));
		if (*str == 'c')
			args->c = 1;
		else if (*str == 'p')
			args->p = 1;
		else if (*str == 's')
			args->s = 1;
		else if (strchr("awrn", *str) != NULL)
		{
			if (args->awrn != 0)
				return ((args->err = MULTIPLE_AWRN));
			awrn_handle(args, str);
		}
		else
			return ((args->d = (*str == 'd')) ? 'd' : INVALID_OFFSET);
		++*arg;
		++str;
	}
	return (0);
}

void			read_args(t_hist_args *args, int argc, char **argv)
{
	int idx;
	int err;

	idx = 1;
	while (idx < argc)
	{
		char  *arg = argv[idx];
		if (*arg == '-')
		{
			++arg;
			if ((err = handle_arg(args, &arg)) == 'd')
			{
				++arg;
				if (*arg && isdigit(*arg))
					args->d_val = atoi(arg);
				else if (idx < argc - 1)
				{
					arg = argv[++idx];
					if (*arg && isdigit(*arg))
						args->d_val = atoi(arg);
					else
						args->err = D_ERR;
				}
				else
					args->err = D_ERR;
			}
			else if (err == -1)
			{
				args->err = AWRN_ERR;
				return;
			}
			else if (err < 0)
				return;
		}
		else
			return;
		++idx;
	}
}

// void			pargs(t_hist_args *args)
// {
// 	args->c ? printf("C\n") : (0);
// 	args->p ? printf("P\n") : (0);
// 	args->s ? printf("S\n") : (0);
// 	args->d ? printf("D:%i\n", args->d_val) : (0);
// 	args->awrn ? printf("AWRN:%c\n", args->awrn) : (0);
// }

// int				main(void)
// {
// 	t_hist_args *args = args_create();
// 	char *v[] = {"test", "-cnd", "4", "-a", NULL};
// 	read_args(args, 4, v);
// 	pargs(args);
// 	return 0;
// }
