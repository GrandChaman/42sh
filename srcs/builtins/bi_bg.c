#include "builtins.h"

int					bi_bg(int argc, char **argv, char ***environ, t_ast_node *root)
{
	int i;

	i = 1;
	(void)environ;
	(void)root;
	if (argc == 1)
	{
		if (!(check_jobs(get_last_jobs())))
			ft_fprintf(2, "42sh: bg: No current job\n");
		jc_set(get_last_jobs(), BG);
	}
	else
	{
		while (i < argc)
		{
			if (argv[i][0] != '%' || !argv[i][1])
				ft_fprintf(2, "42sh: bg: %s: no such job\n", argv[i]);
			else if (argv[i][1] == '%' || argv[i][1] == '+')
			{
				if (!(check_jobs(get_last_jobs())))
					ft_fprintf(2, "42sh: bg: %s: no such job\n", argv[i]);
				jc_set(get_last_jobs(), BG);
			}
			else if (argv[i][1] == '-')
			{
				if (!(check_jobs(get_last_last_jobs())))
					ft_fprintf(2, "42sh: bg: %s: no such job\n", argv[i]);
				jc_set(get_last_last_jobs(), BG);
			}
			else
			{
				if (!(check_jobs(ft_atoi(argv[i] + 1))))
					ft_fprintf(2, "42sh: bg: %s: no such job\n", argv[i]);
				jc_set(ft_atoi(argv[i] + 1), BG);
			}
			i++;
		}
	}
	return (0);
}