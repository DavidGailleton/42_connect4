/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:31:17 by dgaillet          #+#    #+#             */
/*   Updated: 2025/11/12 17:07:13 by dgaillet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*next;

	if (!lst || !*lst)
		return ;
	temp = *lst;
	next = temp->next;
	while (next)
	{
		del(temp->content);
		free(temp);
		temp = next;
		next = temp->next;
	}
	del(temp->content);
	free(temp);
	*lst = NULL;
}
