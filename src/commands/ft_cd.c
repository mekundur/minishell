/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:08:27 by lsasse            #+#    #+#             */
/*   Updated: 2025/01/13 18:01:57 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	*preprocess_path(const char *path, t_mini *mini)
{
	char	*home;
	char	*processed_path;

	while (path && (*path == ' ' || *path == '\n'))
		path++;
	if (!path || (path && ft_strcmp(path, "~") == 0))
		return (ft_getenv("HOME", mini->env_backup));
	if (path && *path == '~')
	{
		home = ft_getenv("HOME", mini->env_backup);
		if (!home)
			return (NULL);
		processed_path = malloc(strlen(home) + strlen(path));
		if (!processed_path)
		{
			free(home);
			return (NULL);
		}
		ft_strcpy(processed_path, home);
		ft_strcat(processed_path, path + 1);
		free(home);
		return (processed_path);
	}
	return (strdup(path));
}

static int	update_pwd_vars(t_mini *mini, char *old_cwd)
{
	char	new_cwd[100];

	if (!getcwd(new_cwd, 100))
		return (1);
	ft_set_oldpwd_var(mini, old_cwd);
	ft_set_pwd_var(mini, new_cwd);
	return (0);
}

int	ft_change_directory(char *path, t_mini *mini)
{
	int		status;
	char	cwd[100];
	char	err_str[100];
	char	*final_path;

	if (!getcwd(cwd, 100))
		return (1);
	final_path = preprocess_path(path, mini);
	if (!final_path)
		return (1);
	status = chdir(final_path);
	if (status == -1)
	{
		strcpy(err_str, "cd: ");
		strcat(err_str, path);
		perror(err_str);
		status = 1;
	}
	else
		status = update_pwd_vars(mini, cwd);
	free(final_path);
	return (status);
}

void	ft_cd(char **argv, t_mini *mini)
{
	char	*path;

	path = argv[1];
	if (argv[2])
	{
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
		mini->exit_status = 1;
		return ;
	}
	mini->exit_status = ft_change_directory(path, mini);
}
