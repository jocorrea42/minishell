/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:23:02 by apodader          #+#    #+#             */
/*   Updated: 2023/11/17 14:23:02 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_lvl(t_tools	*tools, int i)
{
	int		lvl;
	char	*tmp;

	lvl = ft_atoi(&tools->envp[i][6]) + 1;
	free(tools->envp[i]);
	tmp = ft_itoa(lvl);
	tools->envp[i] = ft_strjoin("SHLVL=", tmp);
	free(tmp);
	return (0);
}

int	find_pwd(t_tools *tools)
{
	int	i;

	i = 0;
	tools->home = NULL;
	tools->pwd = NULL;
	tools->old_pwd = NULL;
	while (tools->envp[i])
	{
		if (!tools->reset && !ft_strncmp(tools->envp[i], "SHLVL=", 6))
			add_lvl(tools, i);
		else if (!ft_strncmp(tools->envp[i], "PWD=", 4))
			tools->pwd = ft_strdup(&tools->envp[i][4]);
		else if (!ft_strncmp(tools->envp[i], "OLDPWD=", 7))
			tools->old_pwd = ft_strdup(&tools->envp[i][7]);
		else if (!ft_strncmp(tools->envp[i], "HOME=", 5))
			tools->home = ft_strdup(&tools->envp[i][5]);
		i++;
	}
	return (0);
}

char	*find_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
		i++;
	}
	return (ft_strdup(""));
}

int	parse_envp(t_tools *tools)
{
	char	*path_from_envp;
	int		i;
	char	*tmp;

	path_from_envp = find_path(tools->envp);
	tools->paths = ft_split(path_from_envp, ':');
	free(path_from_envp);
	i = 0;
	while (tools->paths[i])
	{
		if (ft_strncmp(&tools->paths[i][ft_strlen(tools->paths[i]) - 1],
			"/", 1) != 0)
		{
			tmp = ft_strjoin(tools->paths[i], "/");
			free(tools->paths[i]);
			tools->paths[i] = tmp;
		}
		i++;
	}
	return (0);
}
