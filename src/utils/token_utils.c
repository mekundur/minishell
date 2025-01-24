/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:20:22 by pvasilan          #+#    #+#             */
/*   Updated: 2025/01/13 14:27:11 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	token_init(t_tokenizer *t, char **ps, char *es)
{
	t->start = *ps;
	t->end = es;
	t->in_single = false;
	t->in_double = false;
	t->symbols = "<|>&()";
	while (t->start < t->end && ft_is_whitespace(*t->start))
		t->start++;
	t->tok_start = t->start;
}

static int	handle_special_char(t_tokenizer *t, char first, 
	char second, char ret)
{
	if (*t->start == first && t->start + 1 < t->end && t->start[1] == second)
	{
		t->start += 2;
		t->tok_end = t->start;
		return (ret);
	}
	if (*t->start == first)
	{
		t->start++;
		t->tok_end = t->start;
		return (first);
	}
	return (-1);
}

static int	token_special(t_tokenizer *t)
{
	char	c;
	int		ret;

	c = *t->start;
	if (c == 0)
		return (0);
	if (c == '|' || c == '(' || c == ')' || c == '&')
	{
		t->start++;
		t->tok_end = t->start;
		return (c);
	}
	ret = handle_special_char(t, '>', '>', '+');
	if (ret != -1)
		return (ret);
	return (handle_special_char(t, '<', '<', '~'));
}

static int	handle_word(t_tokenizer *t, char **ps, char **eq)
{
	while (t->start < t->end)
	{
		if (*t->start == '"' && !t->in_single)
			t->in_double = !t->in_double;
		else if (*t->start == '\'' && !t->in_double)
			t->in_single = !t->in_single;
		if (!t->in_single && !t->in_double && 
			(ft_is_whitespace(*t->start) || ft_strchr(t->symbols, *t->start)))
			break ;
		t->start++;
	}
	if (eq)
		*eq = t->start;
	*ps = t->start;
	return ('a');
}

int	token_get(char **ps, char *es, char **q, char **eq)
{
	t_tokenizer	t;
	int			ret;

	token_init(&t, ps, es);
	if (q)
		*q = t.tok_start;
	ret = token_special(&t);
	if (ret != -1)
	{
		if (eq) 
			*eq = t.tok_end;
		*ps = t.start;
		return (ret);
	}
	return (handle_word(&t, ps, eq));
}
