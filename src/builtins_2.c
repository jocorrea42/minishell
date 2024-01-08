/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:11:42 by apodader          #+#    #+#             */
/*   Updated: 2024/01/03 23:02:43 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_pwd(t_tools *tools)
{
	printf("%s\n", tools->pwd);
	flush(tools, 1);
	exit(0);
}

int	ms_env(t_tools *tools, int x)
{
	int	i;

	i = -1;
	while (tools->envp[++i])
		ft_putendl_fd(tools->envp[i], 1);
	if (x == 0)
		return (0);
	flush(tools, 1);
	exit(0);
}

void	ms_echo(t_simple_cmd *cmd, t_tools *tools)
{
	int	i;

	i = 1;
	if (!cmd->arg[1])
	{
		ft_putchar_fd('\n', 1);
		flush(tools, 1);
		exit(0);
	}
	if (!ft_strncmp(cmd->arg[i], "-n", 2))
		i++;
	while (cmd->arg[i])
	{
		ft_putstr_fd(cmd->arg[i], 1);
		if (cmd->arg[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (ft_strncmp(cmd->arg[1], "-n", 2))
		ft_putchar_fd('\n', 1);
	flush(tools, 1);
	exit(0);
}

int	ms_exit(t_tools *tools, t_simple_cmd *cmd)
{
	int	i;

	i = -1;
	g_status = 0;
	if (cmd && (cmd->na - cmd->nr > 2))
	{
		ft_putendl_fd("exit: Too many arguments", 1);
		return (g_status = 1);
	}
	else if (cmd && (cmd->na - cmd->nr == 2))
	{
		while (cmd->arg[1][++i])
		{
			if (!ft_isdigit(cmd->arg[1][i]))
			{
				printf("exit: Numeric argument required\n");
				flush(tools, 1);
				exit(2);
			}
		}
		g_status = ft_atoi(cmd->arg[1]);
	}
	flush(tools, 1);
	exit(g_status);
}
