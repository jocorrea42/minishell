/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:20:41 by apodader          #+#    #+#             */
/*   Updated: 2023/12/28 11:20:41 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clearlist(t_scanner *lst)
{
	t_scanner	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst->next;
		if (lst->str)
			free(lst->str);
		free(lst);
		lst = tmp;
	}
}

t_scanner	*ft_lastlist(t_scanner *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_redir	*redir_init(t_scanner *slist, t_tools *tools)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		ft_exit(MALLOC, tools);
	redir->tk = slist->token;
	redir->arg = slist->next->str;
	redir->next = NULL;
	return (redir);
}
