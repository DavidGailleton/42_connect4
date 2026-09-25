/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:26:10 by dgaillet          #+#    #+#             */
/*   Updated: 2025/11/12 17:05:12 by dgaillet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*all_mem;

	if (size && nmemb > SIZE_MAX / size)
		return (NULL);
	all_mem = malloc(size * nmemb);
	if (!all_mem)
		return (NULL);
	ft_bzero(all_mem, nmemb * size);
	return (all_mem);
}
