/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:35:42 by apodader          #+#    #+#             */
/*   Updated: 2023/11/20 19:35:42 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_join(t_tools *tools, t_scanner *list, int d_len, int i[2])
{
	char	*tmp[3];
	int		ij[3];
	int		len;

	ij[0] = i[0];
	ij[1] = i[1];
	ij[2] = d_len;
	len = safe_init(tools, list, tmp, ij);
	tmp[0] = ft_substr(list->str, i[0] + d_len + 1,
			ft_strlen(list->str) - i[0] - d_len - 1);
	if (!tmp[0])
	{
		free(tmp[1]);
		free(tmp[2]);
		ft_exit(MALLOC, tools);
	}
	free(list->str);
	list->str = ft_strjoin(tmp[2], tmp[0]);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	if (!tools->slist->str)
		ft_exit(MALLOC, tools);
	return (len);
}

int	handle_dollar(t_tools *tools, t_scanner *lst, int j)
{
	int	i[2];
	int	d_len;

	i[0] = j;
	i[1] = 0;
	while (tools->envp[i[1]])
	{
		d_len = dollar_len(lst->str, i[0]);
		if (!ft_strncmp(&lst->str[i[0] + 1],
				tools->envp[i[1]], d_len))
			return (dollar_join(tools, lst, d_len, i));
		i[1]++;
	}
	return (ft_error(ENV));
}

int	question_mark(t_scanner *lst, int i, t_tools *tools)
{
	char	*tmp[4];

	safe_qm_init(lst, i, tmp, tools);
	tmp[3] = ft_strjoin(tmp[2], tmp[1]);
	i = ft_strlen(tmp[2]);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	if (!tmp[3])
		ft_exit(MALLOC, tools);
	free(lst->str);
	lst->str = tmp[3];
	return (i);
}

int	dollar_sign(t_scanner *lst, int i, int quotes, t_tools *tools)
{
	while (lst->str[i] && lst->str[i] != quotes)
	{
		if (!quotes && (lst->str[i] == 34 || lst->str[i] == 39))
			i = handle_quotes(lst, i, lst->str[i], tools);
		else if (lst->str[i] == '$' && lst->str[i + 1] == '?')
			i = question_mark(lst, i, tools);
		else if (lst->str[i] == '$'
			&& !(lst->str[i + 1] == '|' || lst->str[i + 1] == ' '
				|| lst->str[i + 1] == '\0'))
			i = handle_dollar(tools, lst, i);
		else
			i++;
		if (i == -1)
			return (-1);
	}
	return (i);
}
