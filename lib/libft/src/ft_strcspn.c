/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:52:55 by rmei              #+#    #+#             */
/*   Updated: 2024/09/16 16:30:29 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Count how long can a substr of `s` be without matching any `reject` char */
size_t	ft_strcspn(const char *s, const char *reject)
{
	char	*reject_ptr;
	size_t	count;

	count = 0;
	while (*s)
	{
		reject_ptr = (char *)reject;
		while (*reject_ptr)
		{
			if (*s == *reject_ptr)
				return (count);
			reject_ptr++;
		}
		count++;
		s++;
	}
	return (count);
}
