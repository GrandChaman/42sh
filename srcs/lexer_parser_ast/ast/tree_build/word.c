#include "sh21.h"

char			*word(char **argv)
{
	char	*ret;
	int		i;
	char	quote;
	int		flag;

	ret = NULL;
	i = 0;
	flag = 0;
	while ((*argv)[i] && ft_isprint((*argv)[i]) && !is_whitespace((*argv)[i]))
	{
		if ((*argv)[i] == (char)'\'' || (*argv)[i] == (char)'\"')
		{
			quote = (*argv)[i];
			ft_memmove(*argv + i, *argv + i + 1, ft_strlen(*argv + i + 1));
			while ((*argv)[i] && (*argv)[i] != quote)
				++i;
			ft_memmove(*argv + i, *argv + i + 1, ft_strlen(*argv + i));
		}
		else
			i++;
	}
	ret = ft_strndup(*argv, i + 1);
	*argv += i;
	return (ret);
}
