#include "mini.h"

void	ft_exit_status_parent(t_mini *mini)
{
	int	signal;

	if (WIFSIGNALED(mini->exit_status))
	{
		signal = WTERMSIG(mini->exit_status);
		if (signal == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
		else if (signal == SIGINT)
			ft_putchar_fd('\n', STDERR_FILENO);
		mini->exit_status = 128 + signal;
	}
	else if (WIFEXITED(mini->exit_status))
	{
		mini->exit_status = WEXITSTATUS(mini->exit_status);
	}
	return ;
}

void	ft_exit_status_child(t_mini *mini)
{
	int	signal;

	if (WIFSIGNALED(mini->exit_status))
	{
		signal = WTERMSIG(mini->exit_status);
		if (signal == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
		mini->exit_status = 128 + signal;
	}
	else if (WIFEXITED(mini->exit_status))
	{
		mini->exit_status = WEXITSTATUS(mini->exit_status);
	}
	return ;
}
