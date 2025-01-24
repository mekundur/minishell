/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_whitespace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:09:36 by pvasilan          #+#    #+#             */
/*   Updated: 2024/09/17 16:02:26 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_is_whitespace(char s)
{
	char	*whitespace;

	whitespace = " \t\r\n\v";
	if (ft_strchr(whitespace, s))
		return (1);
	return (0);
}
