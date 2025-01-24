/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:43:45 by pvasilan          #+#    #+#             */
/*   Updated: 2025/01/22 15:36:28 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_rdcmd	*create_base_redircmd(t_cmd *subcmd,
	char *file, char *efile)
{
	t_rdcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	memset(cmd, 0, sizeof(*cmd));
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->efile = efile;
	return (cmd);
}

t_cmd	*heredoc_cmd(t_mini *mini, t_cmd *subcmd, char *file, char *efile)
{
	t_rdcmd	*cmd;

	cmd = create_base_redircmd(subcmd, file, efile);
	if (!cmd)
		return (NULL);
	cmd->type = REDIR;
	cmd->mode = 0;
	cmd->fd = 0;
	cmd->delim = ft_get_delim(file);
	gc_add(mini, cmd->delim);
	return ((t_cmd *)gc_add(mini, cmd));
}

t_cmd	*ft_redirs_parse(t_cmd *cmd, char **ps, char *es, t_mini *mini)
{
	int		tok;
	char	*q;
	char	*eq;

	while (peek(ps, es, "<>"))
	{
		tok = token_get(ps, es, 0, 0);
		if (token_get(ps, es, &q, &eq) != 'a')
		{
			ft_putstr_fd(" syntax error near unexpected token ", STDERR_FILENO);
			ft_putchar_fd(tok, STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
			mini->exit_status = 2;
			return (NULL);
		}
		if (tok == '<')
			cmd = redircmd_in(mini, cmd, q, eq);
		else if (tok == '>')
			cmd = redircmd_out(mini, cmd, q, eq);
		else if (tok == '+')
			cmd = redircmd_append(mini, cmd, q, eq);
		else if (tok == '~')
			cmd = heredoc_cmd(mini, cmd, q, eq);
	}
	return (cmd);
}
