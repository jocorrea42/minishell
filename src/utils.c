/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:26:45 by apodader          #+#    #+#             */
/*   Updated: 2024/01/03 22:33:18 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

char	**ft_arrdup(char **arr)
{
	char	**rtn;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 1);
	if (!rtn)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		rtn[i] = ft_strdup(arr[i]);
		if (rtn[i] == NULL)
		{
			free_arr(rtn);
			return (rtn);
		}
		i++;
	}
	return (rtn);
}

void	safe_qm_init(t_scanner *lst, int i, char *tmp[4], t_tools *tools)
{
	tmp[0] = ft_itoa(g_status);
	if (!tmp[0])
		ft_exit(MALLOC, tools);
	tmp[1] = ft_substr(lst->str, 0, i);
	if (!tmp[1])
	{
		free(tmp[0]);
		ft_exit(MALLOC, tools);
	}
	tmp[2] = ft_strjoin(tmp[1], tmp[0]);
	free(tmp[1]);
	if (!tmp[2])
	{
		free(tmp[0]);
		free(tmp[2]);
		ft_exit(MALLOC, tools);
	}
	tmp[1] = ft_substr(lst->str, i + 2, ft_strlen(lst->str));
	if (!tmp[1])
	{
		free(tmp[0]);
		free(tmp[2]);
		ft_exit(MALLOC, tools);
	}
}

int	safe_init(t_tools *tools, t_scanner *list, char *tmp[3], int ij[3])
{
	int	len;

	tmp[0] = ft_substr(list->str, 0, ij[0]);
	if (!tmp[0])
		ft_exit(MALLOC, tools);
	tmp[1] = ft_substr(tools->envp[ij[1]], ij[2] + 1,
			(ft_strlen(tools->envp[ij[1]]) - ij[2] - 1));
	if (!tmp[1])
	{
		free(tmp[0]);
		ft_exit(MALLOC, tools);
	}
	tmp[2] = ft_strjoin(tmp[0], tmp[1]);
	len = ft_strlen(tmp[2]);
	free(tmp[0]);
	if (!tmp[2])
	{
		free(tmp[1]);
		ft_exit(MALLOC, tools);
	}
	return (len);
}

int	dollar_len(char *str, int i)
{
	int	j;

	j = 0;
	i++;
	while (str[i] && str[i] != '$' && str[i] != ' '
		&& str[i] != 34 && str[i] != 39
		&& str[i] != '=' && str[i] != '-'
		&& str[i] != ':')
	{
		i++;
		j++;
	}
	return (j);
}
