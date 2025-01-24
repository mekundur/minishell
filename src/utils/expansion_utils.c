/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:16:20 by pvasilan          #+#    #+#             */
/*   Updated: 2025/01/15 14:40:33 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

bool	buffer_ensure_capacity(t_exbuffer *buffer, size_t needed_space)
{
	size_t	offset;

	if (buffer->p >= buffer->expanded + buffer->buffersize - needed_space)
	{
		offset = buffer->p - buffer->expanded;
		buffer->buffersize *= 2;
		buffer->expanded = ft_realloc(buffer->expanded, buffer->buffersize);
		if (!buffer->expanded)
		{
			perror("realloc");
			exit(EXIT_FAILURE);
		}
		buffer->p = buffer->expanded + offset;
	}
	return (true);
}

void	char_copy(t_exbuffer *buffer, char c)
{
	if (buffer_ensure_capacity(buffer, 1))
	{
		*(buffer->p) = c;
		buffer->p++;
	}
}

void	copy_value_to_buffer(t_exbuffer *buff, const char *value)
{
	size_t	value_len;

	value_len = ft_strlen(value);
	if (buffer_ensure_capacity(buff, value_len))
	{
		ft_strlcpy(buff->p, value, value_len + 1);
		buff->p += value_len;
	}
}

void	handle_quote(const char **s, bool *in_quote, t_exbuffer *buff)
{
	*in_quote = !*in_quote;
	char_copy(buff, **s);
	(*s)++;
}

char	*ft_expand_vars(const char *s, t_mini *mini)
{
	size_t		buffersize;
	t_exbuffer	buffer;

	buffer.expanded = buffer_alloc(&buffersize);
	buffer.p = buffer.expanded;
	buffer.buffersize = buffersize;
	process_input_str(s, &buffer, mini->env, mini);
	return (buffer.expanded);
}
