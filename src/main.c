/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:41:32 by lsasse            #+#    #+#             */
/*   Updated: 2025/01/20 15:48:02 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int		*g_exit_status;

/* Add cmd to the buffer and history */
int	get_cmd(char *buff, int n_buff, t_mini *mini)
{
	char	*res;
	int		len;

	if (isatty(0))
		ft_memset(buff, 0, n_buff);
	res = ft_fgets(buff, n_buff, mini, stdin);
	if (res == NULL || !*buff)
		return (-1);
	len = ft_strlen(buff);
	buff[len - 1] = 0;
	add_history(buff);
	return (0);
}

void	minishell(char *buf, t_mini *mini)
{
	char	**cmd_and_args;
	char	*expanded_buf;
	t_cmd	*cmd;

	expanded_buf = ft_expand_vars(buf, mini);
	cmd_and_args = ft_split(expanded_buf, ' ');
	cmd = cmd_parse(expanded_buf, mini);
	if (cmd && cmd_and_args && cmd_and_args[0])
		cmd_run(cmd, mini);
	free(expanded_buf);
	ft_2dstrfree(cmd_and_args);
}

void	set_shell_var(t_mini *mini)
{
	char	cwd[100];
	char	shell_var[200];
	char	*tmp;
	char	**args;

	getcwd(cwd, 100);
	tmp = NULL;
	args = NULL;
	ft_strcpy(shell_var, "SHELL=");
	ft_strcat(shell_var, cwd);
	ft_strcat(shell_var, "/minishell");
	tmp = ft_strjoin("export ", shell_var);
	if (tmp)
	{
		args = ft_split(tmp, ' ');
		if (args)
		{
			ft_export(args, mini);
			ft_2dstrfree(args);
		}
		free(tmp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	static char		buf[CMD_BUFFER];
	int				n_envp;
	t_mini			mini;

	mini.env = NULL;
	mini.env_backup = NULL;
	mini.gc_list = NULL;
	mini.exit_status = 0;
	g_exit_status = &mini.exit_status;
	if (argc > 1 || argv[1])
		panic("usage: ./minishell", &mini);
	standard_signal_setup();
	n_envp = ft_2dstrlen(envp);
	mini.env = ft_2dstrcpy(envp, n_envp, &mini);
	mini.env_backup = ft_2dstrcpy(envp, n_envp, &mini);
	set_shell_var(&mini);
	while (get_cmd(buf, sizeof(buf), &mini) == 0)
		minishell(buf, &mini);
	gc_cleanup(&mini);
	return (0);
}
