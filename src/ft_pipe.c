/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:41:09 by pvasilan          #+#    #+#             */
/*   Updated: 2025/01/24 15:52:12 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_process_heredocs(t_cmd *cmd, t_mini *mini)
{
	t_pipecmd	*pcmd;
	t_rdcmd		*rcmd;

	if (!cmd)
		return ;
	if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		ft_process_heredocs(pcmd->left, mini);
		ft_process_heredocs(pcmd->right, mini);
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_rdcmd *)cmd;
		if (rcmd->delim)
		{
			ft_heredoc(rcmd, mini);
			rcmd->delim = NULL;
		}
		ft_process_heredocs(rcmd->cmd, mini);
	}
}

void	ft_pipe(t_cmd *cmd, t_mini *mini)
{
	int			p[2];
	t_pipecmd	*pcmd;
	pid_t		pid_l;
	pid_t		pid_r;

	pcmd = (t_pipecmd *)cmd;
	ft_process_heredocs(cmd, mini);
	if (pipe(p) == -1)
		panic("[ERROR]: Pipe did not run correctly", mini);
	pid_l = fork();
	if (pid_l == 0)
		ft_fork_l(pcmd->left, p, mini);
	pid_r = fork();
	if (pid_r == 0)
		ft_fork_r(pcmd->right, p, mini);
	close(p[0]);
	close(p[1]);
	if (pid_l > 0 || pid_r > 0)
		signal(SIGINT, SIG_IGN);
	waitpid(pid_l, &mini->exit_status, 0);
	waitpid(pid_r, &mini->exit_status, 0);
	ft_exit_status_child(mini);
	standard_signal_setup();
	exit(mini->exit_status);
}

void	ft_fork_l(t_cmd *left, int *p, t_mini *mini)
{
	signal(SIGQUIT, SIG_DFL);
	dup2(p[1], STDOUT_FILENO);
	close(p[0]);
	close(p[1]);
	cmd_run(left, mini);
	exit(mini->exit_status);
}

void	ft_fork_r(t_cmd *right, int *p, t_mini *mini)
{
	signal(SIGQUIT, SIG_DFL);
	dup2(p[0], STDIN_FILENO);
	close(p[0]);
	close(p[1]);
	cmd_run(right, mini);
	exit(mini->exit_status);
}
