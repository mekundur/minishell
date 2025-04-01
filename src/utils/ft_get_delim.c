/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_delim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:55:45 by pvasilan          #+#    #+#             */
/*   Updated: 2025/01/24 15:45:10 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	init_info(t_delim_info *info)
{
	info->start = 0;
	info->end = 0;
	info->in_quotes = false;
	info->found_start = false;
	info->quote_char = '\0';
	info->i = 0;
	info->j = 0;
}

static void	shift_start(char *file, t_delim_info *info, int *retflag)
{
	*retflag = 1;
	if ((file[info->i] == '"' || file[info->i] == '\'') && (!info->in_quotes))
	{
		info->in_quotes = true;
		info->quote_char = file[info->i];
		if (!info->found_start)
			info->start = info->i + 1;
		info->found_start = true;
		info->i++;
		*retflag = 3;
		return ;
	}
}

static void	delim_util(char *file, t_delim_info *info)
{
	int	retflag;

	while (file[info->i])
	{
		shift_start(file, info, &retflag);
		if (retflag == 3)
			continue ;
		if (file[info->i] == info->quote_char && info->in_quotes)
		{
			info->in_quotes = false;
			break ;
		}
		if (!info->in_quotes && (file[info->i] == '<' 
				|| file[info->i] == '>' || file[info->i] == '|'))
			break ;
		if (!info->in_quotes && !info->found_start
			&& !ft_is_whitespace(file[info->i]))
			info->found_start = true;
		if (!info->in_quotes && info->found_start
			&& ft_is_whitespace(file[info->i]))
			break ;
		info->i++ ;
	}
}

char	*ft_get_delim(char *file)
{
	t_delim_info	info;

	init_info(&info);
	while (file[info.i] && ft_is_whitespace(file[info.i]))
		info.i++;
	info.start = info.i;
	delim_util(file, &info);
	info.end = info.i;
	if (info.in_quotes)
		while (file[info.end] && file[info.end] != info.quote_char)
			info.end++;
	if (!info.in_quotes)
		while (info.end > info.start && ft_is_whitespace(file[info.end - 1]))
			info.end--;
	if (file[info.start] == '"' || file[info.start] == '\'')
		info.start++;
	info.delim = (char *)malloc((info.end - info.start + 1) * sizeof(char));
	if (!info.delim)
		return (NULL);
	while (info.start < info.end)
		info.delim[info.j++] = file[info.start++];
	info.delim[info.j] = '\0';
	return (info.delim);
}
