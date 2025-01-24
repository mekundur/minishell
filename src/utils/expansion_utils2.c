/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:26:02 by pvasilan          #+#    #+#             */
/*   Updated: 2025/01/15 14:51:22 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	expand_curly_variable(const char **s, t_exbuffer *buff, char **this_env)
{
	char	*var_name;
	char	*var_val;

	var_name = get_curly_var_name(s);
	if (!var_name)
		return ;
	var_val = ft_getenv(var_name, this_env);
	if (var_val)
		copy_value_to_buffer(buff, var_val);
	else
	{
		ft_putstr_fd("Variable ", STDERR_FILENO);
		ft_putstr_fd(var_name, STDERR_FILENO);
		ft_putendl_fd(" not found", STDERR_FILENO);
	}
	free(var_name);
	(*s)++;
	(*s)--;
}

char	*extract_var_name_len(const char *start, size_t *var_len)
{
	*var_len = 0;
	while (start[*var_len] && !(start[*var_len] == ' ') 
		&& start[*var_len] != '$'
		&& start[*var_len] != '\'' && start[*var_len] != '\"')
		(*var_len)++;
	return (ft_substr(start, 0, *var_len));
}

void	put_nbr_to_buffer(t_exbuffer *buff, int n)
{
	if (n < 0)
	{
		char_copy(buff, '-');
		n = -n;
	}
	if (n > 9)
	{
		put_nbr_to_buffer(buff, n / 10);
		char_copy(buff, (n % 10) + '0');
	}
	else
		char_copy(buff, n + '0');
}
