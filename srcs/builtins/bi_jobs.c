#include "sh21.h"
#include "libft.h"
#include "builtins.h"
#include "env.h"

static void			print_jobs()
{
	t_list	*tmp;
	t_jc	*jobs_struct;

	jobs_struct = jc_get();
	tmp = jobs_struct->job_list;
	while (tmp != NULL)
	{
		ft_printf("[%d] %s  PGID:%d\n", ((t_jc_job*)(tmp->content))->tag,
			g_jc_status_string[((t_jc_job*)(tmp->content))->status],
			((t_jc_job*)(tmp->content))->pgid);
		tmp = tmp->next;
	}
}

static int		print_one_jobs(int tague)
{
	t_list	*tmp;
	t_jc	*jobs_struct;

	jobs_struct = jc_get();
	tmp = jobs_struct->job_list;
	while (tmp != NULL)
	{
		if (tague == ((t_jc_job*)(tmp->content))->tag)
		{
			ft_printf("[%d] %s  PGID:%d\n", ((t_jc_job*)(tmp->content))->tag,
				g_jc_status_string[((t_jc_job*)(tmp->content))->status],
				((t_jc_job*)(tmp->content))->pgid);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int		get_last_jobs()
{
	t_list	*tmp;
	t_jc	*jobs_struct;
	int		tague;

	tague = -1;
	jobs_struct = jc_get();
	tmp = jobs_struct->job_list;
	while (tmp != NULL)
	{
		tague = ((t_jc_job*)(tmp->content))->tag;
		tmp = tmp->next;
	}
	return (tague);
}

int		get_last_last_jobs()
{
	t_list	*tmp;
	t_jc	*jobs_struct;
	int tague;
	int stock;

	tague = -1;
	stock = -1;
	jobs_struct = jc_get();
	tmp = jobs_struct->job_list;
	while (tmp != NULL)
	{
		stock = tague;
		tague = ((t_jc_job*)(tmp->content))->tag;
		tmp = tmp->next;
	}
	return (stock);
}

int					bi_jobs(int argc, char **argv, char ***environ, t_ast_node *root)
{
	int i;

	i = 1;
	(void)environ;
	(void)root;
	if (argc == 1)
	{
		print_jobs();
		return (0);
	}
	while (i < argc)
	{
		if (argv[i][0] != '%' || !argv[i][1])
			ft_fprintf(2, "42sh: jobs: %s: no such job\n", argv[i]);
		else if (argv[i][1] == '%' || argv[i][1] == '+')
		{
			if (!(print_one_jobs(get_last_jobs())))
				ft_fprintf(2, "42sh: jobs: %s: no such job\n", argv[i]);
		}
		else if (argv[i][1] == '-')
		{
			if (!(print_one_jobs(get_last_last_jobs())))
				ft_fprintf(2, "42sh: jobs: %s: no such job\n", argv[i]);
		}
		else
		{
			if (!(print_one_jobs(ft_atoi(argv[i] + 1))))
				ft_fprintf(2, "42sh: jobs: %s: no such job\n", argv[i]);
		}
		i++;
	}
	return (0);
}