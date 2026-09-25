/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:02:58 by dgaillet          #+#    #+#             */
/*   Updated: 2025/11/12 13:30:49 by dgaillet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	strs_size(const char *s, unsigned char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[j])
	{
		if ((s[j] != c && j == 0) || (s[j] != c && s[j - 1] == c))
			i++;
		j++;
	}
	return (i);
}

static int	next_match(char	*str, unsigned char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static void	clear_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	strs = ft_calloc(sizeof(char *), strs_size(s, c) + 1);
	if (!strs)
		return (NULL);
	i = 0;
	j = 0;
	while (s[j])
	{
		if ((s[j] != c && j == 0) || (s[j] != c && s[j - 1] == c))
		{
			strs[i] = ft_substr(&s[j], 0, next_match((char *) &s[j], c));
			if (!strs[i++])
			{
				clear_strs(strs);
				return (NULL);
			}
		}
		j++;
	}
	return (strs);
}
