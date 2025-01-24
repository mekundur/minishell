/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 21:35:21 by pvasilan          #+#    #+#             */
/*   Updated: 2025/01/15 14:51:20 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	handle_status_variable(t_exbuffer *buff, const char **s, 
	const char *start, t_mini *mini)
{
	put_nbr_to_buffer(buff, mini->exit_status);
	*s += 2;
	while (start[1] && start[1] != ' ' && start[1] != '$'
		&& start[1] != '\'' && start[1] != '\"')
	{
		char_copy(buff, start[1]);
		(*s)++;
		start++;
	}
}

char	*get_curly_var_name(const char **s)
{
	const char	*var_start = *s + 2;
	char		*var_name;
	size_t		var_len;

	while (**s && **s != '}')
		(*s)++;
	if (**s != '}')
		return (NULL);
	var_len = *s - var_start;
	var_name = malloc(var_len + 1);
	if (!var_name)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(var_name, var_start, var_len + 1);
	return (var_name);
}

void	expand_simple_variable(const char **s, t_exbuffer *buff, 
			char **this_env, t_mini *mini)
{
	const char	*start = *s + 1;
	char		*var_name;
	char		*var_val;
	size_t		var_len;

	if (*start == '?')
	{
		handle_status_variable(buff, s, start, mini);
		return ;
	}
	var_name = extract_var_name_len(start, &var_len);
	if (!var_name)
		return ;
	var_val = ft_getenv(var_name, this_env);
	if (var_val)
	{
		copy_value_to_buffer(buff, var_val);
		free(var_val);
	}
	else
		mini->exit_status = 0;
	free(var_name);
	*s += var_len + 1;
}

static void	handle_dollar_sign(const char **s, t_exbuffer *buff, 
		char **this_env, t_mini *mini)
{
	if (*(*s + 1) == '{')
	{
		expand_curly_variable(s, buff, this_env);
		(*s)++;
	}
	else if (*(*s + 1) && (ft_isalpha(*(*s + 1)) || *(*s + 1) == '_'
			|| *(*s + 1) == '?'))
		expand_simple_variable(s, buff, this_env, mini);
	else
	{
		char_copy(buff, **s);
		(*s)++;
	}
}

void	process_input_str(const char *s, t_exbuffer *buff,
			char **this_env, t_mini *mini)
{
	bool	in_single_quote;
	bool	in_double_quote;

	in_single_quote = false;
	in_double_quote = false;
	while (*s)
	{
		if (*s == '\'' && !in_double_quote)
			handle_quote(&s, &in_single_quote, buff);
		else if (*s == '\"' && !in_single_quote)
			handle_quote(&s, &in_double_quote, buff);
		else if (*s == '$' && !in_single_quote)
			handle_dollar_sign(&s, buff, this_env, mini);
		else
		{
			char_copy(buff, *s);
			s++;
		}
	}
	*(buff->p) = '\0';
}
