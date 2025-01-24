/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsasse <lsasse@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:08:40 by lsasse            #+#    #+#             */
/*   Updated: 2024/03/16 11:08:56 by lsasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_get_decimal(char *str, double *decimal)
{
	double	factor;

	factor = 1;
	if (*str == '.')
		str++;
	while (*str)
	{
		*decimal = *decimal * 10 + (*str - '0');
		factor *= 10;
		str++;
	}
	*decimal /= factor;
}

double	ft_atod(char *str)
{
	double	result;
	double	decimal;
	int		sign;

	result = 0;
	decimal = 0;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str && *str != '.')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	ft_get_decimal(str, &decimal);
	return (sign * (result + decimal));
}
