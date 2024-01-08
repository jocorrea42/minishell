/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:33:42 by jocorrea          #+#    #+#             */
/*   Updated: 2024/01/03 22:56:51 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_builtin(t_tools *tools, t_simple_cmd *cmd)
{
	int	len;

	if (cmd->arg[0])
	{
		len = ft_strlen(cmd->arg[0]);
		if (ft_strchr(cmd->arg[0], '/'))
			execve(cmd->arg[0], cmd->arg, tools->envp);
		else if (!ft_strncmp(cmd->arg[0], "echo", len))
			ms_echo(cmd, tools);
		else if (!ft_strncmp(cmd->arg[0], "pwd", len))
			ms_pwd(tools);
		else if (!ft_strncmp(cmd->arg[0], "env", len))
			ms_env(tools, 1);
	}
}

void	command_exec(t_tools *tools, t_simple_cmd *cmd)
{
	int		i;
	char	*mycmd;

	i = -1;
	is_builtin(tools, cmd);
	while (tools->paths[++i])
	{
		mycmd = ft_strjoin(tools->paths[i], cmd->arg[0]);
		if (access(mycmd, F_OK) == 0)
		{
			if (access(mycmd, X_OK) != 0)
			{
				free(mycmd);
				exec_err(cmd->arg[0], 126, tools);
			}
			execve(mycmd, cmd->arg, tools->envp);
		}
		free(mycmd);
	}
	exec_err(cmd->arg[0], 127, tools);
}

void	ft_child(t_tools *tools, t_simple_cmd *cmd, int fd[2])
{
	if (cmd->next)
	{
		if (dup2(fd[1], STDOUT_FILENO) < 0)
		{
			close(fd[0]);
			close(fd[1]);
			ft_exit(DUP, tools);
		}
		close(fd[1]);
		close(fd[0]);
	}
	if (cmd->rd)
		redir_driver(cmd, tools);
	if (cmd->arg[0])
		command_exec(tools, cmd);
	flush(tools, 1);
	exit(0);
}

void	ft_fork(t_tools *tools, t_simple_cmd *cmd)
{
	int	fd[2];

	if (cmd->next)
	{
		if (pipe(fd) < 0)
			ft_exit(PIPE_ERR, tools);
	}
	tools->pid = fork();
	if (tools->pid < 0)
		ft_exit(FORK, tools);
	if (tools->pid == 0)
		ft_child(tools, cmd, fd);
	waitpid(0, &g_status, 0);
	g_status = WEXITSTATUS(g_status);
	if (cmd->next)
	{
		if (dup2(fd[0], STDIN_FILENO) < 0)
		{
			close(fd[0]);
			close(fd[1]);
			ft_exit(DUP, tools);
		}
		close(fd[1]);
		close(fd[0]);
	}
}

int	executor(t_tools *tools)
{
	t_simple_cmd	*tmp;

	tmp = tools->cmds;
	tools->fd_in = dup(STDIN_FILENO);
	tools->fd_out = dup(STDOUT_FILENO);
	while (tmp)
	{
		if (pre_exec(tools))
			return (0);
		if (check_heredoc(tmp, tools) == -1)
			return (0);
		ft_fork(tools, tmp);
		tmp = tmp->next;
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	dup2(tools->fd_in, STDIN_FILENO);
	dup2(tools->fd_out, STDOUT_FILENO);
	close(tools->fd_in);
	close(tools->fd_out);
	return (EXIT_SUCCESS);
}
