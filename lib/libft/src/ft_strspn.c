/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:56:22 by rmei              #+#    #+#             */
/*   Updated: 2024/09/16 16:30:49 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Count how long can a substr of `s` while matching any `accept` char */
size_t	ft_strspn(const char *s, const char *accept)
{
	int		match;
	char	*accept_ptr;
	size_t	count;

	match = 0;
	count = 0;
	while (*s)
	{
		accept_ptr = (char *)accept;
		while (*accept_ptr)
		{
			if (*s == *accept_ptr)
			{
				match = 1;
				break ;
			}
			accept_ptr++;
		}
		if (!match)
			break ;
		count++;
		s++;
	}
	return (count);
}
