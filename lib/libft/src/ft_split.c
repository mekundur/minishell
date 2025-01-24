/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsasse <lsasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 14:36:32 by lsasse            #+#    #+#             */
/*   Updated: 2023/12/03 14:36:58 by lsasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(const char *str, char chr)
{
	int	c;
	int	isword;

	c = 0;
	isword = 0;
	while (*str)
	{
		if (*str != chr)
		{
			if (!isword)
				c++;
			isword = 1;
		}
		else
			isword = 0;
		str++;
	}
	return (c);
}

static char	**ft_free(char **s, int i)
{
	while (i > 0)
		free(s[--i]);
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int			i;
	const char	*start;
	char		**str;
	int			wordcount;

	i = 0;
	wordcount = ft_count(s, c);
	str = (char **)malloc(sizeof(char *) * (wordcount + 1));
	if (!str)
		return (NULL);
	while (*s && i < wordcount)
	{
		while (*s == c)
			s++;
		start = s;
		while (*s && *s != c)
			s++;
		str[i++] = ft_substr(start, 0, s - start);
		if (!str[i - 1])
			return (ft_free(str, i));
	}
	str[i] = NULL;
	return (str);
}
