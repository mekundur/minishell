/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:00:07 by pvasilan          #+#    #+#             */
/*   Updated: 2024/09/25 16:02:29 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	check_merged_arg(char **merged_arg, char *part)
{
	char	*temp;

	if (*merged_arg == NULL)
		*merged_arg = ft_strdup(part);
	else
	{
		temp = ft_strjoin(*merged_arg, " ");
		free(*merged_arg);
		*merged_arg = ft_strjoin(temp, part);
		free(temp);
	}
}

void	check_quotes(char *arg, bool in_single_quote, \
		bool in_double_quote, char *part)
{
	size_t	j;
	size_t	k;
	char	ch;

	j = 0;
	k = 0;
	while (arg[j])
	{
		ch = arg[j];
		if (ft_is_single_quote(ch) && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			j++;
			continue ;
		}
		if (ft_is_double_quote(ch) && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			j++;
			continue ;
		}
		part[k++] = ch;
		j++;
	}
	part[k] = '\0';
}

int	main_quote_handler(int i, char **argv, char **merged_arg)
{
	char	*arg;
	char	*part;
	bool	in_single_quote;
	bool	in_double_quote;

	in_single_quote = false;
	in_double_quote = false;
	while (argv[i] != NULL)
	{
		arg = argv[i];
		part = malloc(strlen(arg) + 1);
		check_quotes(arg, in_single_quote, in_double_quote, part);
		check_merged_arg(merged_arg, part);
		free(part);
		if (!in_single_quote && !in_double_quote)
			break ;
		i++;
	}
	return (i);
}

char	*handle_quotes(char **argv)
{
	int		i;
	char	*merged_arg;

	i = 1;
	merged_arg = NULL;
	if (ft_strcmp(argv[1], "-n") != 0)
		i = 1;
	else
		i = 2;
	i = main_quote_handler(i, argv, &merged_arg);
	return (merged_arg);
}
