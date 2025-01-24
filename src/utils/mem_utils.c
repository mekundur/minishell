/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:01:52 by rmei              #+#    #+#             */
/*   Updated: 2024/09/17 16:00:43 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*temp;

	if (size <= 0)
	{
		free(ptr);
		return (NULL);
	}
	temp = malloc(size);
	if (temp == NULL)
		return (NULL);
	if (ptr == NULL)
		return (temp);
	ft_memcpy(temp, ptr, size);
	free(ptr);
	return (temp);
}

char	*buffer_alloc(size_t *buffer_size)
{
	char	*expanded;

	*buffer_size = BUFFERSIZE;
	expanded = malloc(*buffer_size);
	if (!expanded)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (expanded);
}
