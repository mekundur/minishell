/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_str_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:57:18 by lsasse            #+#    #+#             */
/*   Updated: 2024/09/26 19:02:03 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/* Get len of a double pointer string */
int	ft_2dstrlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/* Free a double pointer string */
void	ft_2dstrfree(char **str)
{
	int	i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

/* Copy a double pointer string */
char	**ft_2dstrcpy(char **arg, int len, t_mini *mini)
{
	int		i;
	char	**temp;

	temp = ft_calloc(sizeof(char *), len + 1);
	if (!temp)
		panic("[ERROR]: Malloc failed", mini);
	i = 0;
	while (arg[i])
	{
		temp[i] = ft_strdup(arg[i]);
		if (!temp[i])
			panic("[ERROR]: Malloc failed", mini);
		i++;
	}
	return (temp);
}

/* Reallocate memory for a double pointer string */
char	**ft_2dstr_realloc(char **str, int size, t_mini *mini)
{
	char	**temp;
	int		i;

	i = 0;
	if (!str || !*str || size <= 0)
		return (NULL);
	temp = ft_calloc(sizeof(char *), size + 1);
	if (!temp)
		panic("[ERROR]: Calloc failed", mini);
	i = 0;
	while (str[i] && size >= 1)
	{
		temp[i] = ft_strdup(str[i]);
		if (!temp[i])
		{
			while (i > 0)
				free(temp[--i]);
			free(temp);
			return (NULL);
		}
		i++;
		size--;
	}
	ft_2dstrfree(str);
	return (temp);
}
