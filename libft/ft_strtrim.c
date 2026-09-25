/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:31:38 by dgaillet          #+#    #+#             */
/*   Updated: 2025/11/12 13:50:53 by dgaillet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	test_charset(char c, char const *set)
{
	if (!set[0])
		return (0);
	if (c == set[0])
		return (1);
	return (test_charset(c, set + 1));
}

static size_t	end_trim(char const *s1, char const *set)
{
	int	i;

	i = 0;
	if (!s1[0])
		return (0);
	while (s1[i])
		i++;
	i--;
	while (test_charset(s1[i], set))
		i--;
	return (i);
}

static size_t	start_trim(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (test_charset(s1[i], set))
		i++;
	return (i);
}

static int	is_empty(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (!test_charset(s1[i], set))
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	if (is_empty(s1, set))
		return (ft_calloc(1, sizeof(char)));
	start = start_trim(s1, set);
	end = end_trim(s1, set);
	str = malloc(sizeof(char) * (end - start + 2));
	if (!str)
		return (NULL);
	while (start + i <= end)
	{
		str[i] = s1[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}
