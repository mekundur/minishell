/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_slice.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:18:52 by lsasse            #+#    #+#             */
/*   Updated: 2024/09/16 16:37:10 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//receives a string and the starting index and the ending index
//returns a string including the starting index and excluding the ending index
char	*ft_slice(char *str, int start, int end)
{
	int		len;
	char	*sliced;
	size_t	str_len;

	str_len = strlen(str);
	if (!str || start < 0 || end <= start || (size_t)start >= str_len)
		return (NULL);
	if ((size_t)end > str_len)
		end = str_len;
	len = end - start;
	sliced = malloc(len + 1);
	if (!sliced)
		return (NULL);
	ft_strlcpy(sliced, str + start, len);
	sliced[len] = '\0';
	str = ft_strcpy(str, sliced);
	free(sliced);
	return (str);
}
