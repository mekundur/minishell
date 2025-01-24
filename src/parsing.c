/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:51:14 by lsasse            #+#    #+#             */
/*   Updated: 2025/01/20 20:29:26 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_cmd	*ft_line_parse(char **ps, char *es, t_mini *mini)
{
	t_cmd	*cmd;

	cmd = ft_pipe_parse(ps, es, mini);
	while (peek(ps, es, "&"))
	{
		token_get(ps, es, 0, 0);
		cmd = back_cmd(mini, cmd);
	}
	return (cmd);
}

t_cmd	*ft_pipe_parse(char **ps, char *es, t_mini *mini)
{
	t_cmd	*cmd;

	cmd = ft_exec_parse(ps, es, mini, 0);
	if (peek(ps, es, "|"))
	{
		token_get(ps, es, 0, 0);
		cmd = pipe_cmd(mini, cmd, ft_pipe_parse(ps, es, mini));
	}
	return (cmd);
}

t_cmd	*ft_block_parse(char **ps, char *es, t_mini *mini)
{
	t_cmd	*cmd;

	if (!peek(ps, es, "("))
		return (NULL);
	token_get(ps, es, 0, 0);
	cmd = ft_line_parse(ps, es, mini);
	if (!peek(ps, es, ")"))
		return (NULL);
	token_get(ps, es, 0, 0);
	cmd = ft_redirs_parse(cmd, ps, es, mini);
	return (cmd);
}

t_cmd	*ft_exec_parse(char **ps, char *es, t_mini *mini, int argc)
{
	char		*q;
	char		*eq;
	int			tok;
	t_cmd		*ret;
	t_execcmd	*cmd;

	if (peek(ps, es, "("))
		return (ft_block_parse(ps, es, mini));
	ret = exec_cmd(mini);
	cmd = (t_execcmd *)ret;
	ret = ft_redirs_parse(ret, ps, es, mini);
	while (!peek(ps, es, "|)&"))
	{
		tok = token_get(ps, es, &q, &eq);
		if (!tok)
			break ;
		cmd->argv[argc] = q;
		cmd->eargv[argc] = eq;
		argc++;
		ret = ft_redirs_parse(ret, ps, es, mini);
	}
	cmd->argv[argc] = 0;
	cmd->eargv[argc] = 0;
	return (ret);
}
