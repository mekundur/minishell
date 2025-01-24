/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsasse <lsasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:31:13 by lsasse            #+#    #+#             */
/*   Updated: 2024/02/12 16:01:39 by lsasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *str)
{
	int	count;

	count = 0;
	if (!str)
	{
		count += ft_putstr("(null)");
		return (count);
	}
	while (str[count])
		count += ft_putchar(str[count]);
	return (count);
}

int	ft_putnbr(int n)
{
	int	count;

	count = 0;
	if (n > 9)
		count += ft_putnbr(n / 10);
	if (n < -9)
		count += ft_putnbr(n / 10);
	else if (n < 0)
		count += ft_putchar('-');
	count += ft_putchar('0' + n % 10 * ((n > 0) - (n < 0)));
	return (count);
}

int	ft_putunbr(long long unsigned int nbr)
{
	int	count;

	count = 0;
	if (nbr > 9)
	{
		count += ft_putunbr(nbr / 10);
		count += ft_putchar(nbr % 10 + '0');
	}
	else
		count += ft_putchar(nbr % 10 + '0');
	return (count);
}

int	ft_puthex(long long unsigned int nbr, int uppercase)
{
	int	digit;
	int	count;

	count = 0;
	if (nbr < 16)
	{
		if (uppercase)
			count += ft_putchar(UHEX_DIGITS[nbr]);
		else
			count += ft_putchar(HEX_DIGITS[nbr]);
		return (count);
	}
	if (uppercase)
		digit = UHEX_DIGITS[nbr % 16];
	else
		digit = HEX_DIGITS[nbr % 16];
	nbr /= 16;
	count += ft_puthex(nbr, uppercase);
	count += ft_putchar((char)digit);
	return (count);
}

int	ft_putptr(void *nbr)
{
	int	count;

	count = 0;
	if (!nbr)
		return (ft_putstr("(nil)"));
	else
	{
		count += ft_putstr("0x");
		count += ft_puthex((long unsigned int)nbr, 0);
	}
	return (count);
}
