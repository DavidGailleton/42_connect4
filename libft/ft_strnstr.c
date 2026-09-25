/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:05:52 by dgaillet          #+#    #+#             */
/*   Updated: 2025/11/12 13:42:42 by dgaillet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;
	size_t	big_len;
	size_t	i;

	i = 0;
	little_len = ft_strlen(little);
	big_len = ft_strlen(big);
	if (!little[0])
		return ((char *) big);
	while ((little_len + i) <= len && (little_len + i) <= big_len)
	{
		if (!ft_strncmp(&big[i], little, little_len))
			return ((char *) &big[i]);
		i++;
	}
	return (NULL);
}
