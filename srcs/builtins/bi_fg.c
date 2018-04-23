#include "sh21.h"
#include "libft.h"
#include "builtins.h"
#include "env.h"

int		check_jobs(int tague)
{
	t_list	*tmp;
	t_jc	*jobs_struct;

	jobs_struct = jc_get();
	tmp = jobs_struct->job_list;
	while (tmp != NULL)
	{
		if (tague == ((t_jc_job*)(tmp->content))->tag)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int					bi_fg(int argc, char **argv, char ***environ, t_ast_node *root)
{
	(void)environ;
	(void)root;
	if (argc == 1)
	{
		if (!(check_jobs(get_last_jobs())))
			ft_fprintf(2, "42sh: fg: No current job\n");
		jc_set(get_last_jobs(), FG);
	}
	else if (argc > 2)
		ft_fprintf(2, "42sh: fg: Too much arguments\n");
	else
	{
		if (argv[1][0] != '%' || !argv[1][1])
			ft_fprintf(2, "42sh: fg: %s: no such job\n", argv[1]);
		else if (argv[1][1] == '%' || argv[1][1] == '+')
		{
			if (!(check_jobs(get_last_jobs())))
				ft_fprintf(2, "42sh: fg: %s: no such job\n", argv[1]);
			jc_set(get_last_jobs(), FG);
		}
		else if (argv[1][1] == '-')
		{
			if (!(check_jobs(get_last_last_jobs())))
				ft_fprintf(2, "42sh: fg: %s: no such job\n", argv[1]);
			jc_set(get_last_last_jobs(), FG);
		}
		else
		{
			if (!(check_jobs(ft_atoi(argv[1] + 1))))
				ft_fprintf(2, "42sh: fg: %s: no such job\n", argv[1]);
			jc_set(ft_atoi(argv[1] + 1), FG);
		}
	}
	return (0);
}