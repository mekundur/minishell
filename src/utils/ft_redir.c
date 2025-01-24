/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:49:03 by pvasilan          #+#    #+#             */
/*   Updated: 2025/01/22 15:37:32 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	process_heredocs(t_list *rcmd_lst, t_mini *mini)
{
	t_rdcmd		*lcmd;
	t_list		*tmp;

	tmp = rcmd_lst;
	while (tmp)
	{
		lcmd = (t_rdcmd *)tmp->content;
		if (lcmd->delim)
			handle_heredoc(lcmd, mini);
		tmp = tmp->next;
	}
}

static void	process_redirections(t_cmd **cmd, t_list *rcmd_lst)
{
	t_rdcmd	*lcmd;
	t_rdcmd	*rcmd;

	while ((*cmd)->type == REDIR || (*cmd)->type == HEREDOC)
	{
		lcmd = (t_rdcmd *)rcmd_lst->content;
		ft_redir_file(lcmd);
		rcmd = (t_rdcmd *)*cmd;
		rcmd_lst = rcmd_lst->next;
		*cmd = rcmd->cmd;
	}
}

void	ft_redir(t_cmd *cmd, t_mini *mini)
{
	t_list	*rcmd_lst;

	signal(SIGQUIT, SIG_DFL);
	rcmd_lst = rev_redir_lst(cmd, mini);
	process_heredocs(rcmd_lst, mini);
	process_redirections(&cmd, rcmd_lst);
	cmd_run(cmd, mini);
	exit(mini->exit_status);
}
