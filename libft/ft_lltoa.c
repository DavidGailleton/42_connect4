/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:06:35 by dgaillet          #+#    #+#             */
/*   Updated: 2025/12/07 12:29:25 by dgaillet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digits(long long n)
{
	size_t	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static void	insert_char(char *str, unsigned long long nbr, size_t index)
{
	while (nbr)
	{
		str[index--] = nbr % 10 + '0';
		nbr /= 10;
	}
}

char	*ft_lltoa(long long n)
{
	unsigned long long	nbr;
	char			*str;
	size_t			size;

	nbr = n;
	if (n < 0)
		nbr = n * -1;
	size = count_digits(n);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	if (nbr == 0)
		str[0] = '0';
	else
	{
		if (n < 0)
			str[0] = '-';
		insert_char(str, nbr, size - 1);
	}
	return (str);
}
