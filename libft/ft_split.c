/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:44:42 by apodader          #+#    #+#             */
/*   Updated: 2023/01/25 15:11:40 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	w_count(const char *s, char c)
{
	int	count;
	int	x;

	count = 0;
	x = 0;
	while (*s)
	{
		if (*s == c)
		{
			x = 0;
		}
		else if (x == 0)
		{
			x = 1;
			count++;
		}
		s++;
	}
	return (count);
}

int	w_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

void	free_arr(char **split_arr)
{
	int	i;

	i = 0;
	while (split_arr[i])
	{
		free(split_arr[i]);
		i++;
	}
	free(split_arr);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;

	i = 0;
	tab = (char **)ft_calloc((w_count(s, c) + 1), sizeof(*tab));
	if (!tab)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			tab[i] = ft_substr(s, 0, w_len(s, c));
			if (!tab[i])
			{
				free_arr(tab);
				return (NULL);
			}
			i++;
			s += w_len(s, c);
		}
	}
	return (tab);
}
