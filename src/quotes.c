/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:57:03 by apodader          #+#    #+#             */
/*   Updated: 2023/12/30 13:00:03 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	s_quotes(char *str, int i, int j, int quotes)
{
	j++;
	while (str[i + j])
	{
		if (str[i + j] == quotes)
			return (j);
		j++;
	}
	return (quote_error(quotes));
}

void	rm_quote(t_scanner *lst, int i, t_tools *tools)
{
	char	*sub;
	char	*sub2;
	char	*new;

	sub = ft_substr(lst->str, 0, i);
	if (!sub)
		ft_exit(MALLOC, tools);
	sub2 = ft_substr(lst->str, i + 1, ft_strlen(lst->str));
	if (!sub)
	{
		free(sub);
		ft_exit(MALLOC, tools);
	}
	new = ft_strjoin(sub, sub2);
	free(sub);
	free(sub2);
	if (!new)
		ft_exit(MALLOC, tools);
	free(lst->str);
	lst->str = new;
}

int	handle_quotes(t_scanner *lst, int i, int quotes, t_tools *tools)
{
	rm_quote(lst, i, tools);
	while (lst->str[i])
	{
		if (lst->str[i] == quotes)
		{
			rm_quote(lst, i, tools);
			return (i);
		}
		else if (lst->str[i] == '$' && quotes == 34)
			i = dollar_sign(lst, i, quotes, tools);
		else
			i++;
		if (i == -1)
			return (-1);
	}
	return (i);
}
