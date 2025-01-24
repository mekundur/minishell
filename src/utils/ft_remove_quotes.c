/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekundur <mekundur@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:39:57 by mekundur          #+#    #+#             */
/*   Updated: 2025/01/16 20:40:05 by mekundur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_result(char *str, char *result, char quote, bool in_quotes)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (!in_quotes && (str[i] == '"' || str[i] == '\''))
		{
			quote = str[i];
			in_quotes = true;
		}
		else if (in_quotes && str[i] == quote)
		{
			in_quotes = false;
			quote = '\0';
		}
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
}

// Removes any quote in the input if present
char	*ft_remove_quotes(char *str)
{
	char	*result;
	char	quote;
	bool	in_quotes;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	in_quotes = false;
	quote = '\0';
	ft_result(str, result, quote, in_quotes);
	return (result);
}
