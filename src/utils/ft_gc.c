/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:49:48 by pvasilan          #+#    #+#             */
/*   Updated: 2025/01/13 17:49:49 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	*gc_add(t_mini *mini, void *ptr)
{
	t_garbage	*new;

	if (!ptr)
		return (NULL);
	new = malloc(sizeof(t_garbage));
	if (!new)
	{
		free(ptr);
		return (NULL);
	}
	new->ptr = ptr;
	new->next = mini->gc_list;
	mini->gc_list = new;
	return (ptr);
}

void	gc_free(t_mini *mini, void *ptr)
{
	t_garbage	*current;
	t_garbage	*prev;

	if (!ptr || !mini->gc_list)
		return ;
	current = mini->gc_list;
	prev = NULL;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				mini->gc_list = current->next;
			free(current->ptr);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	gc_cleanup(t_mini *mini)
{
	t_garbage	*current;
	t_garbage	*next;

	ft_2dstrfree(mini->env);
	ft_2dstrfree(mini->env_backup);
	current = mini->gc_list;
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	mini->gc_list = NULL;
	clear_history();
}
