/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:40:45 by lsasse            #+#    #+#             */
/*   Updated: 2025/04/01 18:06:13 by mekundur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_file_access(char *file, char **args)
{
	if (access(file, X_OK) == -1)
		perror(args[0]);
	else
	{
		execve(file, args, NULL);
		perror(file);
	}
	exit(126);
}

void	ft_dir_check(char *file, char **args, t_mini *mini)
{
	DIR		*dirptr;
	char	*home;

	if (!ft_strcmp(file, "~") || !ft_strcmp(file, "~\n"))
	{
		home = ft_getenv("HOME", mini->env_backup);
		ft_strcpy(file, home);
		free(home);
	}
	dirptr = NULL;
	dirptr = opendir(file);
	if (dirptr)
	{
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
		closedir(dirptr);
		exit(126);
	}
	if (access(file, F_OK) == 0)
		ft_file_access(file, args);
	else
		perror(file);
	exit(127);
}

char	*set_full_path(char *dir, char *file, char *path)
{
	char	*full_path;

	full_path = malloc(ft_strlen(dir) + ft_strlen(file) + 2);
	if (!full_path)
	{
		free(path);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		exit(127);
	}
	ft_strcpy(full_path, dir);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, file);
	return (full_path);
}

void	execve_run(char *file, char **args, char *path, t_mini *mini)
{
	char	*dir;
	char	*full_path;

	dir = ft_strtok(path, ":");
	while (dir)
	{
		full_path = set_full_path(dir, file, path);
		if (access(full_path, F_OK) == 0)
		{
			if (access(full_path, X_OK) == -1)
				perror(args[0]);
			else
				execve(full_path, args, mini->env);
		}
		free(full_path);
		dir = ft_strtok(NULL, ":");
	}
	free(path);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	exit(127);
}

void	ft_execvp(char *file, char **args, t_mini *mini)
{
	char	*path;
	char	*path_env;

	if (ft_strchr(file, '/') \
		|| !ft_strcmp(file, "~") || !ft_strcmp(file, "~\n"))
		ft_dir_check(file, args, mini);
	path_env = ft_getenv("PATH", mini->env);
	if (!path_env)
	{
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		exit(127);
	}
	path = ft_strdup(path_env);
	free(path_env);
	if (!path)
	{
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		exit(127);
	}
	execve_run(file, args, path, mini);
}
