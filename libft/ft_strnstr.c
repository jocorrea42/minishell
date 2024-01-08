/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:01:01 by apodader          #+#    #+#             */
/*   Updated: 2023/01/19 18:24:34 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *str, char *to_find, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!ft_strncmp(to_find, "", 1))
		return (str);
	while (str[i] && i < len)
	{
		while (str[i + j] == to_find[j] && i + j < len)
		{
			j++;
			if (j == (unsigned int)ft_strlen(to_find))
				return (&str[i]);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
