/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsasse <lsasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:08:10 by lsasse            #+#    #+#             */
/*   Updated: 2023/11/30 20:53:50 by lsasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numlen(long num, int len)
{
	while (num)
	{
		len++;
		num = num / 10;
	}
	return (len);
}

static void	*writenum(char *nbr, long num, int len)
{
	while (num)
	{
		nbr[len] = (char)('0' + num % 10);
		len--;
		num = num / 10;
	}
	return (0);
}

char	*ft_itoa(int n)
{
	int		len;
	long	num;
	char	*nbr;

	len = 0;
	num = n;
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
		len++;
	len = numlen(num, len);
	nbr = (char *)malloc((len + 1) * sizeof(char));
	if (!nbr)
		return (NULL);
	num = n;
	if (n < 0)
	{
		nbr[0] = '-';
		num = -num;
	}
	nbr[len] = '\0';
	len--;
	writenum(nbr, num, len);
	return (nbr);
}
