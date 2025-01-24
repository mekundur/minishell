/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:46:50 by rmei              #+#    #+#             */
/*   Updated: 2024/09/16 16:31:54 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Tokenize a string based on the given delimeter  */
char	*ft_strtok(char *s, const char *delim)
{
	static char	*olds;
	char		*end;

	if (!s)
		s = olds;
	if (*s == '\0')
	{
		olds = s;
		return (NULL);
	}
	s += ft_strspn (s, delim);
	if (*s == '\0')
	{
		olds = s;
		return (NULL);
	}
	end = s + ft_strcspn(s, delim);
	if (*end == '\0')
	{
		olds = end;
		return (s);
	}
	*end = '\0';
	olds = end + 1;
	return (s);
}
