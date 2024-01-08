/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:52:47 by anyela            #+#    #+#             */
/*   Updated: 2024/01/03 22:33:55 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_token(char *str, t_tokens token, t_tools *tools)
{
	t_scanner	*new;
	t_scanner	*last;

	new = (t_scanner *)malloc(sizeof(t_scanner));
	if (!new)
		ft_exit(MALLOC, tools);
	new->str = NULL;
	new->token = token;
	new->next = NULL;
	if (str)
		new->str = str;
	if (!tools->slist)
	{
		tools->slist = new;
		new->prev = NULL;
		return (0);
	}
	last = ft_lastlist(tools->slist);
	new->prev = last;
	last->next = new;
	return (0);
}

t_tokens	minishell_token(char c)
{
	static int	tokens[3][2] = {{'|', PIPE}, {'>', GREAT}, {'<', LESS}};
	int			i;

	i = -1;
	while (++i < 3)
		if (tokens[i][0] == c)
			return (tokens[i][1]);
	return (0);
}

int	no_token_push(char *str, int i, t_tools *tools)
{
	int	j;

	j = 0;
	while (str[i + j] && !(minishell_token(str[i + j])))
	{
		if (str[i + j] == 34 || str[i + j] == 39)
		{
			j = s_quotes(str, i, j, str[i + j]);
			if (j == -1)
				return (-1);
		}
		if (is_space(str[i + j]))
		{
			add_token(ft_substr(str, i, j), 0, tools);
			return (i + j);
		}
		else
			j++;
	}
	add_token(ft_substr(str, i, j), 0, tools);
	return (i + j);
}

int	token_push(char *str, int i, t_tools *tools)
{
	int	err;

	if (str[i] == '>' && str[i + 1] == '>')
	{
		err = add_token(NULL, GREAT_GREAT, tools);
		i += 2;
	}
	else if (str[i] == '<' && str[i + 1] == '<')
	{
		err = add_token(NULL, LESS_LESS, tools);
		i += 2;
	}
	else
	{
		err = add_token(NULL, minishell_token(str[i]), tools);
		i++;
	}
	if (err == -1)
		return (-1);
	return (i);
}

int	scanner(char *str, t_tools *tools)
{
	int			i;

	i = 0;
	while (str && str[i])
	{
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (minishell_token(str[i]))
			i = token_push(str, i, tools);
		else if (str[i])
			i = no_token_push(str, i, tools);
		if (i == -1)
			return (-1);
	}
	return (0);
}
