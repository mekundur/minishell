#include "mini.h"

static int	check_basic_cases(char **argv)
{
	if ((argv && !argv[1]) || (argv && argv[1]
			&& ft_strcmp(argv[1], "\n") == 0))
		return (0);
	if (argv && argv[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	return (-1);
}

static int	validate_exit_number(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '\0' || str[i] == '\n')
		return (ft_atoi(str));
	ft_putendl_fd(" numeric argument required", STDERR_FILENO);
	return (2);
}

void	ft_exit(char **argv, t_mini *mini)
{
	int		status;
	char	*str;

	status = check_basic_cases(argv);
	if (status >= 0)
		mini->exit_status = status;
	else if (argv && argv[1])
	{
		str = ft_remove_quotes(argv[1]);
		if (str)
			ft_remove_trailing_new_line(str);
		mini->exit_status = validate_exit_number(str);
		free(str);
	}
	gc_cleanup(mini);
	exit(mini->exit_status);
}
