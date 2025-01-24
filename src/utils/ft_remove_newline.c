/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_newline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekundur <mekundur@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:34:21 by mekundur          #+#    #+#             */
/*   Updated: 2025/01/16 20:34:24 by mekundur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// Remove trailing newline if present
void	ft_remove_trailing_new_line(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}
