/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:03:19 by dgaillet          #+#    #+#             */
/*   Updated: 2025/11/11 15:18:37 by dgaillet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	size_t	size;
	size_t	i;

	if (!lst)
		return (NULL);
	size = ft_lstsize(lst);
	i = 1;
	while (i < size)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}
