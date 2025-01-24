/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redir_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:33:11 by pvasilan          #+#    #+#             */
/*   Updated: 2025/01/22 15:37:59 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_cmd	*redircmd_in(t_mini *mini, t_cmd *subcmd, char *file, char *efile)
{
	t_rdcmd	*cmd;

	cmd = create_base_redircmd(subcmd, file, efile);
	if (!cmd)
		return (NULL);
	cmd->type = REDIR;
	cmd->mode = O_RDONLY;
	cmd->fd = 0;
	cmd->delim = NULL;
	return ((t_cmd *)gc_add(mini, cmd));
}

t_cmd	*redircmd_out(t_mini *mini, t_cmd *subcmd, char *file, char *efile)
{
	t_rdcmd	*cmd;

	cmd = create_base_redircmd(subcmd, file, efile);
	if (!cmd)
		return (NULL);
	cmd->type = REDIR;
	cmd->mode = O_WRONLY | O_CREAT | O_TRUNC;
	cmd->fd = 1;
	cmd->delim = NULL;
	return ((t_cmd *)gc_add(mini, cmd));
}

t_cmd	*redircmd_append(t_mini *mini, t_cmd *subcmd, char *file, char *efile)
{
	t_rdcmd	*cmd;

	cmd = create_base_redircmd(subcmd, file, efile);
	if (!cmd)
		return (NULL);
	cmd->type = REDIR;
	cmd->mode = O_WRONLY | O_CREAT | O_APPEND;
	cmd->fd = 1;
	cmd->delim = NULL;
	return ((t_cmd *)gc_add(mini, cmd));
}
