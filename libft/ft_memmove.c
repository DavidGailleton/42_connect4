/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:17:42 by dgaillet          #+#    #+#             */
/*   Updated: 2025/11/09 20:15:29 by dgaillet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_rev_memcpy(void *dest, const void *src, size_t n)
{
	if ((!dest && !src) || n == 0)
		return (dest);
	n--;
	while (n > 0)
	{
		((unsigned char *) dest)[n] = ((unsigned char *) src)[n];
		n--;
	}
	((unsigned char *) dest)[n] = ((unsigned char *) src)[n];
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	return (ft_rev_memcpy(dest, src, n));
}
