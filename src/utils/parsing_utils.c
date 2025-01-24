/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:44:34 by rmei              #+#    #+#             */
/*   Updated: 2025/01/22 15:37:09 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/* Finds end of the string (?) */
int	peek(char **ps, char *es, char *tokens)
{
	char	*s;

	s = *ps;
	while (s < es && ft_is_whitespace(*s))
		s++;
	*ps = s;
	return (*s && ft_strchr(tokens, *s));
}

/* Parse the input command */
t_cmd	*cmd_parse(char *s, t_mini *mini)
{
	char	*es;
	t_cmd	*cmd;

	while (s && ft_is_whitespace(*s))
		s++;
	if (*s == '#')
		return (NULL);
	es = s + ft_strlen(s);
	cmd = ft_line_parse(&s, es, mini);
	peek(&s, es, "");
	if (s != es)
	{
		ft_putstr_fd(s, STDERR_FILENO);
		return (ft_putendl_fd(": command not found", STDERR_FILENO), NULL);
	}
	str_null_terminate(cmd);
	return (cmd);
}

static void	terminate_single_cmd(t_cmd *cmd)
{
	t_rdcmd		*rcmd;
	t_backcmd	*bcmd;

	if (cmd->type == REDIR)
	{
		rcmd = (t_rdcmd *)cmd;
		str_null_terminate(rcmd->cmd);
		*rcmd->efile = 0;
	}
	else if (cmd->type == BACK)
	{
		bcmd = (t_backcmd *)cmd;
		str_null_terminate(bcmd->cmd);
	}
}

static void	handle_cmd_type(t_cmd *cmd)
{
	t_execcmd	*ecmd;
	int			i;

	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		i = 0;
		while (ecmd->argv[i])
			*ecmd->eargv[i++] = 0;
	}
	else if (cmd->type == PIPE)
	{
		str_null_terminate(((t_pipecmd *)cmd)->left);
		str_null_terminate(((t_pipecmd *)cmd)->right);
	}
	else
		terminate_single_cmd(cmd);
}

t_cmd	*str_null_terminate(t_cmd *cmd)
{
	if (cmd == 0)
		return (0);
	handle_cmd_type(cmd);
	return (cmd);
}
