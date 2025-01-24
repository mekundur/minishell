/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsasse <lsasse@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 09:27:50 by lsasse            #+#    #+#             */
/*   Updated: 2023/11/28 12:55:09 by lsasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	char	chr;
	size_t	i;

	tmp = 0;
	i = 0;
	chr = c;
	while (s[i] != '\0')
	{
		if (s[i] == chr)
			tmp = (char *)s + i;
		i++;
	}
	if (s[i] == 0)
		if (s[i] == chr)
			return ((char *)s + i);
	return (tmp);
}
