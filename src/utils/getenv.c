/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:06:10 by lsasse            #+#    #+#             */
/*   Updated: 2025/01/13 17:48:57 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static	char	*get_var_name(char *variable)
{
	if (*variable == '$')
		return (variable + 1);
	return (variable);
}

//TODO:the comparison needs to consider that the first char of the variable is $
// which needs to be skipped. either in this function or in the inputadress
char	*ft_getenv(char *variable, char **env)
{
	char	**temp_arg;
	int		j;
	int		cmp;
	char	*var_name;
	char	*value;

	j = 0;
	var_name = get_var_name(variable);
	while (env[j])
	{
		temp_arg = ft_split(env[j], '=');
		if (!temp_arg)
			return (NULL);
		cmp = ft_strncmp(var_name, temp_arg[0], ft_strlen(var_name));
		if (cmp == 0 && ft_strlen(var_name) == ft_strlen(temp_arg[0]))
		{
			value = ft_strdup(temp_arg[1]);
			ft_2dstrfree(temp_arg);
			return (value);
		}
		ft_2dstrfree(temp_arg);
		j++;
	}
	return (NULL);
}
