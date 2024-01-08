/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 13:10:52 by apodader          #+#    #+#             */
/*   Updated: 2024/01/03 22:30:37 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_paths(t_tools *tools)
{
	char	*tmp;
	char	**argv;

	argv = ft_calloc(3, sizeof(char *));
	if (!argv)
		ft_exit(MALLOC, tools);
	argv[0] = ft_strdup("42");
	tmp = getcwd(NULL, 0);
	if (!tmp)
		ft_exit(MALLOC, tools);
	argv[1] = ft_strjoin("PWD=", tmp);
	if (!argv[1])
		ft_exit(MALLOC, tools);
	free(tmp);
	ms_export(tools, argv);
	free(argv[1]);
	argv[1] = ft_strjoin("OLDPWD=", tools->pwd);
	if (!argv[1])
		ft_exit(MALLOC, tools);
	ms_export(tools, argv);
	free_arr(argv);
}

int	ms_cd(t_tools *tools, t_simple_cmd *cmd)
{
	int		err;

	g_status = 0;
	if (cmd->na - cmd->nr > 2)
		return (ft_error(CD));
	if (!cmd->arg[1])
		err = chdir(tools->home);
	else if (cmd->arg[1][0] == '-')
	{
		if (chdir(tools->old_pwd) == -1)
			return (ft_error(OLDPWD));
	}
	else
		err = chdir(cmd->arg[1]);
	if (err == -1)
		return (ft_error(NO_DIR));
	update_paths(tools);
	return (0);
}

int	ms_export(t_tools *tools, char **arg)
{
	int	i;
	int	x;

	i = 0;
	g_status = 0;
	if (!arg[1])
		return (ms_env(tools, 0));
	while (arg[++i])
	{
		x = var_exists(tools->envp, arg[i]);
		if (!ft_isalpha(arg[i][0]))
		{
			g_status = 1;
			printf("export: %s: not a valid identifier\n", arg[i]);
		}
		else if (x > 0)
			change_var(tools, arg[i], x);
		else if (x == 0)
			add_var(tools, arg[i]);
	}
	return (0);
}

int	ms_unset(t_tools *tools, t_simple_cmd *cmd)
{
	int	i;
	int	len;
	int	j;

	i = 0;
	g_status = 0;
	if (!cmd->arg[1])
		return (0);
	while (cmd->arg[++i])
	{
		len = 0;
		while (cmd->arg[i][len])
			len++;
		j = -1;
		while (tools->envp[++j])
		{
			if (!ft_strncmp(tools->envp[j], cmd->arg[i], len)
				&& tools->envp[j][len] == '=')
				rm_var(tools, j);
		}
	}
	return (0);
}
