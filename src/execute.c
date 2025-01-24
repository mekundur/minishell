/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:55:58 by lsasse            #+#    #+#             */
/*   Updated: 2025/01/24 14:09:44 by mekundur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_builtin_exec(char **argv, t_mini *mini)
{
	if (!ft_strcmp(argv[0], "exit") || !ft_strcmp(argv[0], "exit\n"))
		ft_exit(argv, mini);
	else if (!ft_strcmp(argv[0], "cd\n") || !ft_strcmp(argv[0], "cd"))
		ft_cd(argv, mini);
	else if (!ft_strcmp(argv[0], "echo") || !ft_strcmp(argv[0], "echo\n"))
		ft_echo(argv, mini);
	else if (!ft_strcmp(argv[0], "env") || !ft_strcmp(argv[0], "env\n"))
		ft_env(argv, mini);
	else if (!ft_strcmp(argv[0], "pwd") || !ft_strcmp(argv[0], "pwd\n"))
		ft_pwd(mini);
	else if (!ft_strcmp(argv[0], "export") || !ft_strcmp(argv[0], "export\n"))
		ft_export(argv, mini);
	else if (!ft_strcmp(argv[0], "unset") || !ft_strcmp(argv[0], "unset\n"))
		ft_unset(argv, mini);
}

bool	is_builtin(char **argv)
{
	if (ft_strcmp(argv[0], "echo") == 0
		|| ft_strcmp(argv[0], "echo\n") == 0
		|| ft_strcmp(argv[0], "env") == 0
		|| ft_strcmp(argv[0], "env\n") == 0
		|| ft_strcmp(argv[0], "export") == 0
		|| ft_strcmp(argv[0], "export\n") == 0
		|| ft_strcmp(argv[0], "unset") == 0
		|| ft_strcmp(argv[0], "unset\n") == 0
		|| ft_strcmp(argv[0], "pwd") == 0
		|| ft_strcmp(argv[0], "pwd\n") == 0
		|| ft_strcmp(argv[0], "cd") == 0
		|| ft_strcmp(argv[0], "cd\n") == 0
		|| ft_strcmp(argv[0], "exit") == 0
		|| ft_strcmp(argv[0], "exit\n") == 0)
		return (true);
	else
		return (false);
}

void	ft_exec_run(t_execcmd *ecmd, t_mini *mini)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (ecmd->argv && ecmd->argv[i])
		i++;
	if (is_builtin(ecmd->argv))
		ft_builtin_exec(ecmd->argv, mini);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			ft_execvp(ecmd->argv[0], ecmd->argv, mini);
		}
		if (pid > 0)
			signal(SIGINT, SIG_IGN);
		waitpid(pid, &mini->exit_status, 0);
		ft_exit_status_parent(mini);
		standard_signal_setup();
	}
}

void	ft_exec(t_cmd *cmd, t_mini *mini)
{
	t_execcmd	*ecmd;
	char		*tmp;
	int			i;

	ecmd = (t_execcmd *)cmd;
	if (ecmd->argv[0] == 0)
		return ;
	i = 0;
	while (ecmd->argv[i])
	{
		tmp = ft_remove_quotes(ecmd->argv[i]);
		ft_strcpy(ecmd->argv[i], tmp);
		free(tmp);
		if (ft_strcmp(ecmd->argv[i], "echo") == 0)
			break ;
		i++;
	}
	ft_exec_run(ecmd, mini);
}

/* Execute cmd. Check if command is a builtin */
void	cmd_run(t_cmd *cmd, t_mini *mini)
{
	pid_t		pid;

	if (cmd == 0)
		return ;
	if (cmd->type == EXEC)
		ft_exec(cmd, mini);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (cmd->type == REDIR)
				ft_redir(cmd, mini);
			else if (cmd->type == PIPE)
				ft_pipe(cmd, mini);
			else
				panic("[ERROR]: Issue with cmd_run", mini);
			exit(mini->exit_status);
		}
		if (pid > 0)
			signal(SIGINT, SIG_IGN);
		waitpid(pid, &mini->exit_status, 0);
		ft_exit_status_child(mini);
		standard_signal_setup();
	}
}
