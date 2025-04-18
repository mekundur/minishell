/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_whitespace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:09:36 by pvasilan          #+#    #+#             */
/*   Updated: 2025/01/24 15:44:50 by pvasilan         ###   ########.fr       */
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
