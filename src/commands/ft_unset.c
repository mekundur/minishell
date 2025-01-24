/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:48:33 by lsasse            #+#    #+#             */
/*   Updated: 2025/01/13 18:03:04 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_strswap(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

void	ft_env_del(char **argv, int index, t_mini *mini)
{
	int	len;

	if (!argv || index < 0)
		panic("Env var deletion error. \
		Input empty or index out of bounds", mini);
	len = ft_2dstrlen(argv);
	if (index >= len)
		panic("Env var deletion error. Index out of bounds", mini);
	ft_strswap(&argv[index], &argv[len - 1]);
	free(argv[len]);
	free(argv[len - 1]);
	argv[len - 1] = NULL;
}

int	ft_varlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

void	ft_env_unset(char *var, t_mini *mini)
{
	int		j;
	char	**stored_var;
	int		cmp;

	if (!var)
		return ;
	j = 0;
	while (mini->env[j])
	{
		stored_var = ft_split(mini->env[j], '=');
		cmp = ft_strncmp(var, stored_var[0], ft_strlen(stored_var[0]));
		ft_2dstrfree(stored_var);
		if (cmp == 0)
		{
			ft_env_del(mini->env, j, mini);
			return ;
		}
		j++;
	}
}

void	ft_unset(char **cmd_and_args, t_mini *mini)
{
	int	len;
	int	i;

	i = 0;
	len = ft_2dstrlen(cmd_and_args);
	if (len >= 1)
	{
		if (ft_has_flags(cmd_and_args) == true)
			ft_putendl_fd("unset: flags not supported", STDERR_FILENO);
		while (++i < len)
			ft_env_unset(cmd_and_args[i], mini);
	}
	mini->exit_status = 0;
}
