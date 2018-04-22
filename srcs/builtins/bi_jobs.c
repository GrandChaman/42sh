#include "sh21.h"
#include "libft.h"
#include "builtins.h"
#include "env.h"

int					bi_jobs(int argc, char **argv, char ***environ, t_ast_node *root)
{
	t_jc *jobs_struct;
	t_list	*tmp;

	(void)argc;
	(void)argv;
	(void)environ;
	(void)root;
	jobs_struct = jc_get();
	tmp = jobs_struct->job_list;
	while (tmp != NULL)
	{
		ft_printf("[%d] %s  PGID:%d\n", ((t_jc_job*)(tmp->content))->tag, g_jc_status_string[((t_jc_job*)(tmp->content))->status], ((t_jc_job*)(tmp->content))->pgid);
		tmp = tmp->next;
	}
	return (0);
}