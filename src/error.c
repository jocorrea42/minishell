/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:17:58 by apodader          #+#    #+#             */
/*   Updated: 2024/01/03 22:57:13 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_error err, t_tools *tools)
{
	if (err == MALLOC)
		printf("Error: Failed to allocate memory\n");
	else if (err == FORK)
		printf("Error: Failed to fork a process\n");
	else if (err == PIPE_ERR)
		printf("Error: Failed to create a pipe\n");
	else if (err == DUP)
		printf("Error: Failed to duplicate a file\n");
	else if (err == OPEN)
		printf("Error: Failed to open a file\n");
	flush(tools, 1);
	exit(1);
}

int	ft_error(t_error err)
{
	g_status = 1;
	if (err == ENV)
		printf("Error: Invalid environment variable\n");
	else if (err == SYNTAX)
		printf("Error: Invalid syntax\n");
	else if (err == CD)
		printf("cd: Too many arguments\n");
	else if (err == NO_DIR)
		printf("cd: No such file or directory\n");
	else if (err == OLDPWD)
		printf("cd: OLDPWD not set\n");
	return (-1);
}

int	quote_error(int quote)
{
	if (quote == 34)
		printf("Error: unclosed dquotes\n");
	else
		printf("Error: unclosed quotes\n");
	g_status = 1;
	return (-1);
}

void	exec_err(char *cmd, int status, t_tools *tools)
{
	if (status == 127)
		printf("%s: Command not found\n", cmd);
	else
		printf("%s: Permission denied\n", cmd);
	flush(tools, 1);
	exit(status);
}
