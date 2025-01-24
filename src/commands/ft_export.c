/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:37:52 by lsasse            #+#    #+#             */
/*   Updated: 2025/01/15 14:49:41 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static bool	ft_is_var_valid(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = 0;
		if (argv[i][0] == '=')
			return (false);
		while (argv[i][j] && argv[i][j] != '=')
		{
			if (!((argv[i][j] >= 'A' && argv[i][j] <= 'Z') 
				|| (argv[i][j] >= 'a' && argv[i][j] <= 'z'))
				&& argv[i][j] != '_' && argv[i][j] != '=')
				return (false);
			j++;
		}
	}
	return (true);
}

static char	*extract_var_name(const char *var)
{
	char	*equals_pos;

	equals_pos = ft_strchr(var, '=');
	if (!equals_pos)
		return (NULL);
	return (ft_substr(var, 0, equals_pos - var));
}

static int	find_existing_var(char **env, const char *var_name)
{
	int		i;
	size_t	name_len;

	i = 0;
	if (!var_name)
		return (-1);
	name_len = ft_strlen(var_name);
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, name_len) == 0
			&& env[i][name_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static void	ft_export_vars(char *var, t_mini *mini)
{
	char	*var_name;
	int		var_index;
	int		len;
	char	*trimmed_var;

	var_name = extract_var_name(var);
	var_index = find_existing_var(mini->env, var_name);
	if (var_index >= 0)
	{
		trimmed_var = ft_strtrim(var, "\n");
		free(mini->env[var_index]);
		mini->env[var_index] = trimmed_var;
	}
	else
	{
		len = ft_2dstrlen(mini->env);
		mini->env = ft_2dstr_realloc(mini->env, len + 1, mini);
		mini->env[len] = ft_strtrim(var, "\n");
		if (!mini->env[len])
			mini->env = ft_2dstr_realloc(mini->env, len, mini);
	}
	free(var_name);
}

void	ft_export(char **cmd_and_args, t_mini *mini)
{
	int	len;
	int	i;

	i = 0;
	len = ft_2dstrlen(cmd_and_args);
	if ((len == 1 || *cmd_and_args[1] == '\n') 
		|| (cmd_and_args[1] && cmd_and_args[1][0] == '#'))
		ft_export_print(cmd_and_args, mini);
	else if (ft_has_flags(cmd_and_args))
		ft_putendl_fd("export: flags not supported", STDERR_FILENO);
	else if (!ft_is_var_valid(cmd_and_args))
	{
		ft_putstr_fd("export: '", STDERR_FILENO);
		ft_putstr_fd(cmd_and_args[1], STDERR_FILENO);
		ft_putendl_fd("' : not a valid identifier", STDERR_FILENO);
		mini->exit_status = 1;
		return ;
	}
	else
		while (++i < len)
			ft_export_vars(cmd_and_args[i], mini);
	mini->exit_status = 0;
}
