#include "mini.h"

// -n flag search
static bool	ft_n_flag(char *argv)
{
	bool	n_flag;
	int		j;

	j = 0;
	n_flag = false;
	if (!argv)
		return (n_flag);
	else if (argv[j] && argv[j] == '-' && argv[j + 1] && argv[j + 1] == 'n')
	{
		j++;
		while (argv[j] == 'n')
			j++;
		if (!argv[j] || argv[j] == '\n')
			n_flag = true;
	}
	return (n_flag);
}

// Process arguments (in the loop)
void	ft_echo(char **argv, t_mini *mini)
{
	int		i;
	bool	n_flag;
	char	*str;

	i = 1;
	n_flag = ft_n_flag(argv[i]);
	if (n_flag)
		i++;
	while (argv[i])
	{
		str = ft_remove_quotes(argv[i]);
		if (str)
			ft_remove_trailing_new_line(str);
		ft_putstr_fd(str, STDOUT_FILENO);
		free(str);
		i++;
		if (argv[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	mini->exit_status = 0;
}
