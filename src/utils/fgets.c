/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fgets.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:12:04 by lsasse            #+#    #+#             */
/*   Updated: 2025/01/16 19:08:53 by mekundur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	home_in_cwd(char *home, char prompt[200], char *cwd)
{
	char	tmp[100];

	ft_strcpy(tmp, cwd);
	ft_memmove(tmp, tmp + ft_strlen(home), ft_strlen(tmp) - ft_strlen(home));
	tmp[ft_strlen(tmp) - ft_strlen(home)] = 0;
	ft_strcat(prompt, "~");
	ft_strcat(prompt, tmp);
}

static char	*get_user_info(t_mini *mini, char **host, 
	char **home, char **env_home)
{
	char	*user;

	*host = ft_getenv("NAME", mini->env_backup);
	user = ft_getenv("USER", mini->env_backup);
	*home = ft_getenv("HOME", mini->env_backup);
	*env_home = ft_getenv("HOME", mini->env);
	return (user);
}

static void	build_base_prompt(char prompt[200], 
	const char *user, const char *host)
{
	if (user)
		ft_strcpy(prompt, user);
	else
		ft_strcpy(prompt, "user");
	ft_strcat(prompt, "@");
	if (host)
		ft_strcat(prompt, host);
	else
		ft_strcat(prompt, "minishell");
	ft_strcat(prompt, ":");
}

void	set_prompt(char prompt[200], t_mini *mini)
{
	char	cwd[100];
	char	*user;
	char	*host;
	char	*home;
	char	*env_home;

	user = get_user_info(mini, &host, &home, &env_home);
	if (!getcwd(cwd, 100))
	{
		ft_multi_free(host, user, home, env_home);
		return ;
	}
	build_base_prompt(prompt, user, host);
	if (env_home && home && !strcmp(home, env_home) 
		&& ft_strnstr(cwd, home, ft_strlen(cwd)))
		home_in_cwd(home, prompt, cwd);
	else
		ft_strcat(prompt, cwd);
	ft_strcat(prompt, "$ ");
	ft_multi_free(host, user, home, env_home);
}

// Only stdin is supported for this implementation
// Copy the input to the provided buffer
// Ensure the buffer is null-terminated
// Free the memory allocated by readline
// Find the length of the string
// If the string is shorter than n-1 and doesn't end with a newline,
// append a newline character to mimic fgets behavior.

char	*ft_fgets(char *str, int n, t_mini *mini, FILE *stream)
{
	int		len;
	char	prompt[200];
	char	*input;

	if (stream != stdin)
		return (NULL);
	set_prompt(prompt, mini);
	input = readline(prompt);
	if (input == NULL)
		return (NULL);
	ft_strlcpy(str, input, n - 1);
	str[n - 1] = '\0';
	free(input);
	len = ft_strlen(str);
	if (len < n - 1 && str[len - 1] != '\n')
	{
		str[len] = '\n';
		str[len + 1] = '\0';
	}
	return (str);
}
