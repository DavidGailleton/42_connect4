/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:07:51 by dgaillet          #+#    #+#             */
/*   Updated: 2025/11/12 14:17:18 by dgaillet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long int	str_to_ll(const char *nptr)
{
	int				i;
	long long int	res;

	i = 0;
	res = 0;
	while (ft_isdigit(nptr[i]))
	{
		if (res * 10 < res && res > 0)
			return (-1);
		res = (10 * res) + nptr[i] - 48;
		i++;
	}
	return (res);
}

static long long int	ft_atoll(const char *nptr)
{
	int				i;
	long long int	res;

	i = 0;
	res = 0;
	if (!nptr[0])
		return (0);
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' && ft_isdigit(nptr[i + 1]))
	{
		res = -1 * ft_atoll(&nptr[i] + 1);
		if ((nptr[i + 1] != '1' && res == 1)
			|| (nptr[i + 1] == '1' && ft_isdigit(nptr[i + 2]) && res == 1))
			return (0);
		return (res);
	}
	else if (nptr[i] == '+' && ft_isdigit(nptr[i + 1]))
		i++;
	return (str_to_ll(&nptr[i]));
}

int	ft_atoi(const char *nptr)
{
	int	res;

	res = (int) ft_atoll(nptr);
	return (res);
}
