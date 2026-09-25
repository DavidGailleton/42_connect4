/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:43:22 by dgaillet          #+#    #+#             */
/*   Updated: 2025/11/11 11:31:23 by dgaillet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*first_node;

	if (!lst)
		return (0);
	first_node = lst;
	i = 1;
	while (lst->next)
	{
		lst = lst->next;
		if (lst == first_node)
			break ;
		i++;
	}
	return (i);
}
