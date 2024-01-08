/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:30:48 by apodader          #+#    #+#             */
/*   Updated: 2023/01/19 15:03:59 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int val, size_t n)
{
	size_t	i;

	i = 0;
	while (n-- > 0)
	{
		((char *)dest)[i] = val;
		i++;
	}
	return (dest);
}
