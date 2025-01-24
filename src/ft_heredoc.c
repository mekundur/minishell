/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:22:48 by pvasilan          #+#    #+#             */
/*   Updated: 2025/01/24 13:24:43 by mekundur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	setup_heredoc_temp(char *file, int *fd_w)
{
	*fd_w = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (*fd_w == -1)
	{
		perror(file);
		return ;
	}
}

static void	process_line(char *line, const char *delimiter, 
	int fd_w, bool *should_break)
{
	if (!line)
	{
		ft_putendl_fd("warning: here-document delimited by end-of-file", 
			STDERR_FILENO);
		*should_break = true;
		return ;
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		*should_break = true;
		return ;
	}
	write(fd_w, line, ft_strlen(line));
	write(fd_w, "\n", 1);
	free(line);
}

void	ft_heredoc(t_rdcmd *rcmd, t_mini *mini)
{
	char	*line;
	int		fd_w;
	char	delimiter[100];
	char	file[100];
	bool	should_break;

	should_break = false;
	ft_strcpy(delimiter, rcmd->delim);
	setup_heredoc_signals();
	ft_generate_file_names(file);
	setup_heredoc_temp(file, &fd_w);
	while (!should_break)
	{
		line = readline("> ");
		process_line(line, delimiter, fd_w, &should_break);
	}
	close(fd_w);
	rcmd->file = ft_strdup(file);
	gc_add(mini, rcmd->file);
	rcmd->mode = O_RDONLY;
	rcmd->fd = 0;
}

void	heredoc_handler_coda(pid_t pid, t_mini *mini)
{
	waitpid(pid, &mini->exit_status, 0);
	standard_signal_setup();
	ft_exit_status_parent(mini);
}
