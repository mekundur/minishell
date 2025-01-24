/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:26:29 by pvasilan          #+#    #+#             */
/*   Updated: 2025/01/22 15:37:46 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// don't remember why i added this function
// we don't use is currently
// we can delete it in the end if we won't need it
void	valid_file(t_cmd *cmd)
{
	t_cmd		*tcmd;
	t_rdcmd		*trcmd;

	tcmd = cmd;
	while (tcmd->type == 2)
	{
		trcmd = (t_rdcmd *)tcmd;
		if (access(trcmd->file, F_OK) == 0)
		{
			if (access(trcmd->file, W_OK) == -1)
			{
				perror(trcmd->file);
				exit (1);
			}
		}
		else
		{
			perror(trcmd->file);
			exit (1);
		}
		tcmd = trcmd->cmd;
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
	int	fd;
	char		*tmp;

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
