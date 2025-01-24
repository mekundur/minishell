/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:24:26 by pvasilan          #+#    #+#             */
/*   Updated: 2024/09/17 14:52:36 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_is_single_quote(char c)
{
	return (c == 39);
}

int	ft_is_double_quote(char c)
{
	return (c == 34);
}

void	toggle_quotes(bool *in_single_quote, bool *in_double_quote, char quote)
{
	if (quote == '\'' && !*in_double_quote)
		*in_single_quote = !*in_single_quote;
	else if (quote == '\"' && !*in_single_quote)
		*in_double_quote = !*in_double_quote;
}
