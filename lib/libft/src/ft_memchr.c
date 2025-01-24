/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsasse <lsasse@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:39:54 by lsasse            #+#    #+#             */
/*   Updated: 2023/11/28 13:30:56 by lsasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	chr;
	unsigned char	*ptr;

	i = 0;
	chr = (unsigned char)c;
	ptr = (unsigned char *)s;
	if (n == 0)
		return (NULL);
	while (i < (n - 1))
	{
		if (ptr[i] == chr)
			return ((void *)s + i);
		i++;
	}
	if (ptr[i] == chr)
		return ((void *)(s + i));
	return (NULL);
}
