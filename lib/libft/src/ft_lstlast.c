/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsasse <lsasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:20:15 by lsasse            #+#    #+#             */
/*   Updated: 2023/12/03 17:16:04 by lsasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptr;
	t_list	*prioptr;

	if (!lst)
		return (NULL);
	ptr = lst;
	prioptr = lst;
	while (ptr != NULL)
	{
		prioptr = ptr;
		ptr = ptr->next;
	}
	return (prioptr);
}
