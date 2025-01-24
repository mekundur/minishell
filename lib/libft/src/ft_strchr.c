/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsasse <lsasse@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 06:59:13 by lsasse            #+#    #+#             */
/*   Updated: 2023/11/28 12:40:37 by lsasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	chr;

	i = 0;
	chr = c;
	while (s[i])
	{
		if (s[i] == chr)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == chr)
		return ((char *)s + i);
	return (0);
}
