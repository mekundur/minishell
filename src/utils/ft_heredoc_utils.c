/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:20:06 by pvasilan          #+#    #+#             */
/*   Updated: 2025/01/24 13:42:13 by mekundur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	heredoc_signal_handler(int sig)
{
	(void) sig;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = heredoc_signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

char	*ft_generate_file_names(char file[100])
{
	int		i;
	char	*num;
	char	*tmp;

	i = 1;
	ft_strcpy(file, "/tmp/heredoc");
	num = ft_itoa(i);
	ft_strcat(file, num);
	ft_strcat(file, "\0");
	while (access(file, F_OK) == 0)
	{
		tmp = ft_strtrim(file, num);
		ft_strcpy(file, tmp);
		free(tmp);
		free(num);
		i++;
		num = ft_itoa(i);
		ft_strcat(file, num);
		ft_strcat(file, "\0");
	}
	free(num);
	return (file);
}
