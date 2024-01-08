/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:37:10 by apodader          #+#    #+#             */
/*   Updated: 2023/12/23 14:37:10 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_exit(char **envp, t_tools *tools)
{
	free_arr(envp);
	ft_exit(MALLOC, tools);
}

int	var_exists(char **envp, char *var)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (var[len] && var[len] != '=')
		len++;
	if (!var[len])
		return (-1);
	len++;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], var, len))
			return (i);
	}
	return (0);
}

void	change_var(t_tools *tools, char *new, int i)
{
	char	*tmp;

	tmp = tools->envp[i];
	tools->envp[i] = ft_strdup(new);
	if (!tools->envp[i])
		ft_exit(MALLOC, tools);
	free(tmp);
}

void	add_var(t_tools *tools, char *new_var)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (tools->envp[i])
		i++;
	new_envp = ft_calloc(i + 2, sizeof(char *));
	if (!new_envp)
		ft_exit(MALLOC, tools);
	i = 0;
	while (tools->envp[i])
	{
		new_envp[i] = ft_strdup(tools->envp[i]);
		if (!new_envp[i])
			free_and_exit(new_envp, tools);
		i++;
	}
	new_envp[i] = ft_strdup(new_var);
	if (!new_envp[i])
		free_and_exit(new_envp, tools);
	free_arr(tools->envp);
	tools->envp = new_envp;
}

void	rm_var(t_tools *tools, int j)
{
	char	**new_envp;
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (tools->envp[i])
		i++;
	new_envp = ft_calloc(i + 1, sizeof(char *));
	if (!new_envp)
		ft_exit(MALLOC, tools);
	i = -1;
	while (tools->envp[++i])
	{
		if (i == j)
		{
			x = 1;
			continue ;
		}
		new_envp[i - x] = ft_strdup(tools->envp[i]);
		if (!new_envp[i - x])
			free_and_exit(new_envp, tools);
	}
	free_arr(tools->envp);
	tools->envp = new_envp;
}
