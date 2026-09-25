/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:54:17 by dgaillet          #+#    #+#             */
/*   Updated: 2025/11/12 13:56:15 by dgaillet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	void	*ptr;

	ptr = (void *) s;
	while (n > 0)
	{
		if (*((unsigned char *) ptr) == (unsigned char) c)
			return (ptr);
		ptr++;
		n--;
	}
	return (NULL);
}
