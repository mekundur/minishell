/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsasse <lsasse@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:25:07 by lsasse            #+#    #+#             */
/*   Updated: 2023/11/27 14:41:04 by lsasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*p;
	const unsigned char	*s;

	p = dest;
	s = src;
	if ((void *)dest == 0 && (void *)src == 0)
		return (0);
	while (n > 0)
	{
		*p = *s;
		p++;
		s++;
		n--;
	}
	return (dest);
}
