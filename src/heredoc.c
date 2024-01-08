/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 13:26:44 by jocorrea          #+#    #+#             */
/*   Updated: 2023/12/04 22:30:05 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_doc(char *end, int fd[2], t_tools *tools)
{
	char	*line;

	if (dup2(tools->fd_in, STDIN_FILENO) < 0)
		ft_exit(DUP, tools);
	signal(SIGINT, SIG_DFL);
	line = readline("> ");
	while (line && ft_strncmp(end, line, ft_strlen(end)))
	{
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	close(fd[0]);
	close(fd[1]);
	free(line);
	ft_exit(-1, tools);
}

int	heredoc(char *end, t_tools *tools)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		ft_exit(PIPE_ERR, tools);
	signal(SIGINT, SIG_IGN);
	if (!isatty(STDIN_FILENO))
		close(STDIN_FILENO);
	pid = fork();
	if (pid < 0)
		ft_exit(FORK, tools);
	if (pid == 0)
		get_doc(end, fd, tools);
	waitpid(pid, &g_status, 0);
	close(fd[1]);
	signal(SIGINT, handle_sigint);
	if (g_status == 2)
	{
		g_status = 1;
		close(fd[0]);
		return (-1);
	}
	g_status = 0;
	return (fd[0]);
}

int	check_heredoc(t_simple_cmd *cmd, t_tools *tools)
{
	t_redir	*tmp;

	tmp = cmd->rd;
	while (cmd->rd)
	{
		if (cmd->rd->tk == LESS_LESS)
			cmd->rd->fd = heredoc(cmd->rd->arg, tools);
		if (cmd->rd->fd == -1)
			return (-1);
		cmd->rd = cmd->rd->next;
	}
	cmd->rd = tmp;
	return (0);
}
