/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:54:38 by dgaillet          #+#    #+#             */
/*   Updated: 2025/11/10 18:19:21 by dgaillet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*temp_lst;
	void	*temp_content;

	if (!lst)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		temp_content = f(lst->content);
		temp_lst = ft_lstnew(temp_content);
		if (!temp_lst)
		{
			del(temp_content);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, temp_lst);
		lst = lst->next;
	}
	return (new_lst);
}
