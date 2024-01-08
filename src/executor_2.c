/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:53:33 by apodader          #+#    #+#             */
/*   Updated: 2024/01/03 22:53:19 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	infile(t_simple_cmd *cmd, t_tools *tools)
{
	int	fd;

	fd = 0;
	if (cmd->rd->tk == LESS_LESS)
		fd = cmd->rd->fd;
	else if (cmd->rd->tk == LESS)
		fd = open(cmd->rd->arg, O_RDONLY);
	if (fd > 0 && dup2(fd, STDIN_FILENO) < 0)
		ft_exit(DUP, tools);
	if (fd > 0)
		close(fd);
}

void	redir_driver(t_simple_cmd *cmd, t_tools *tools)
{
	int		fd;

	fd = 0;
	while (cmd->rd)
	{
		if (cmd->rd->tk == GREAT_GREAT)
		{
			fd = open(cmd->rd->arg, O_CREAT | O_RDWR | O_APPEND, 0644);
			if (fd < 0)
				ft_exit(OPEN, tools);
		}
		else if (cmd->rd->tk == GREAT)
		{
			fd = open(cmd->rd->arg, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (fd < 0)
				ft_exit(OPEN, tools);
		}
		if (fd > 0 && dup2(fd, STDOUT_FILENO) < 0)
			ft_exit(DUP, tools);
		if (fd > 0)
			close(fd);
		infile(cmd, tools);
		cmd->rd = cmd->rd->next;
	}
}

int	pre_exec(t_tools *tools)
{
	if (tools->cmds->arg[0] && !ft_strncmp(tools->cmds->arg[0], "exit", 4)
		&& !tools->cmds->arg[0][4])
		ms_exit(tools, tools->cmds);
	else if (tools->cmds->arg[0]
		&& !ft_strncmp(tools->cmds->arg[0], "export", 6)
		&& !tools->cmds->arg[0][6])
		ms_export(tools, tools->cmds->arg);
	else if (tools->cmds->arg[0] && !ft_strncmp(tools->cmds->arg[0], "unset", 5)
		&& !tools->cmds->arg[0][5])
		ms_unset(tools, tools->cmds);
	else if (tools->cmds->arg[0] && !ft_strncmp(tools->cmds->arg[0], "cd", 2)
		&& !tools->cmds->arg[0][2])
		ms_cd(tools, tools->cmds);
	else
		return (0);
	return (1);
}
