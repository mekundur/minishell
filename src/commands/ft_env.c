#include "mini.h"

void	ft_env(char **argv, t_mini *mini)
{
	int	i;
	int	len;

	len = ft_2dstrlen(argv);
	if ((len == 1 || *argv[1] == '\n') 
		|| (argv[1] && argv[1][0] == '#'))
	{
		len = ft_2dstrlen(mini->env);
		i = 0;
		while (len--)
		{
			if (ft_strchr(mini->env[i], '='))
				printf("%s\n", mini->env[i++]);
			else
				i++;
		}
	}
	else
		ft_putendl_fd("env: invalid number of options or arguments", 2);
	mini->exit_status = 0;
}

void	ft_export_print(char **argv, t_mini *mini)
{
	int		i;
	int		len;
	char	**tmp;

	len = ft_2dstrlen(argv);
	if ((len == 1 || *argv[1] == '\n') 
		|| (argv[1] && argv[1][0] == '#'))
	{
		len = ft_2dstrlen(mini->env);
		i = 0;
		while (len--)
		{
			tmp = ft_split(mini->env[i], '=');
			if (ft_strchr(mini->env[i], '=') && tmp && tmp[1])
				printf("declare -x %s=\"%s\"\n", tmp[0], tmp[1]);
			else if (ft_strchr(mini->env[i], '=') && tmp && !tmp[1])
				printf("declare -x %s=\"\"\n", tmp[0]);
			else if (!ft_strchr(mini->env[i], '=') && tmp && !tmp[1])
				printf("declare -x %s\n", tmp[0]);
			ft_2dstrfree(tmp);
			i++;
		}
	}
	else
		ft_putendl_fd("export: invalid number of options or arguments", 2);
}
