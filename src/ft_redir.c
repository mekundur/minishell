/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:49:03 by pvasilan          #+#    #+#             */
/*   Updated: 2025/01/24 14:11:01 by mekundur         ###   ########.fr       */
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
			ft_heredoc(lcmd, mini);
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

t_list	*rev_redir_lst(t_cmd *cmd, t_mini *mini)
{
	t_cmd		*tcmd;
	t_rdcmd		*trcmd;
	t_list		*rcmd_lst;
	t_list		*new;

	rcmd_lst = NULL;
	tcmd = cmd;
	while (tcmd->type == 2)
	{
		trcmd = (t_rdcmd *)tcmd;
		if (!rcmd_lst)
			rcmd_lst = ft_lstnew(tcmd);
		else
		{
			new = ft_lstnew(tcmd);
			ft_lstadd_front(&rcmd_lst, new);
		}
		tcmd = trcmd->cmd;
	}
	gc_add(mini, rcmd_lst);
	return (rcmd_lst);
}

void	ft_redir_file(t_rdcmd *rcmd)
{
	int		fd;
	char	*tmp;

	tmp = ft_remove_quotes(rcmd->file);
	ft_strcpy(rcmd->file, tmp);
	free(tmp);
	fd = open(rcmd->file, rcmd->mode, 0644);
	if (fd < 0)
	{
		perror(rcmd->file);
		exit(1);
	}
	if (dup2(fd, rcmd->fd) < 0)
	{
		perror("dup2");
		exit(1);
	}
	close(fd);
	if (rcmd->mode == O_RDONLY && rcmd->delim)
		unlink(rcmd->file);
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
