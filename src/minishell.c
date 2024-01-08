/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:32:47 by apodader          #+#    #+#             */
/*   Updated: 2023/11/17 14:32:47 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tools_init(t_tools *tools)
{
	tools->slist = NULL;
	tools->cmds = NULL;
	tools->pid = 0;
	tools->rd = 0;
	tools->reset = 1;
	parse_envp(tools);
	return (1);
}

void	free_cmd(t_simple_cmd *cmd)
{
	t_redir			*rd;
	t_simple_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->arg)
			free(cmd->arg);
		while (cmd->rd)
		{
			rd = cmd->rd->next;
			free(cmd->rd);
			cmd->rd = rd;
		}
		free(cmd);
		cmd = tmp;
	}
}

int	flush(t_tools *tools, int x)
{
	if (x && tools->envp)
	{
		clear_history();
		free_arr(tools->envp);
	}
	if (tools->paths)
		free_arr(tools->paths);
	if (tools->pwd)
		free(tools->pwd);
	if (tools->old_pwd)
		free(tools->old_pwd);
	if (tools->home)
		free(tools->home);
	if (tools->args)
		free(tools->args);
	if (tools->cmds)
		free_cmd(tools->cmds);
	if (tools->slist)
		ft_clearlist(tools->slist);
	return (0);
}

int	expander(t_scanner *lst, t_tools *tools)
{
	int			i;

	while (lst)
	{
		i = 0;
		while (lst->str && lst->str[i])
		{
			if (lst->str[i] == 34 || lst->str[i] == 39)
				i = handle_quotes(lst, i, lst->str[i], tools);
			else if (lst->str[i] == '$')
				i = dollar_sign(lst, i, 0, tools);
			else
				i++;
			if (i == -1)
				return (-1);
		}
		lst = lst->next;
	}
	return (0);
}

int	minishell(t_tools *tools)
{
	t_redir	*tmp;

	tools_init(tools);
	tools->args = readline("\033[1;32mminishell> \033[0m");
	if (tools->args == NULL)
		ms_exit(tools, tools->cmds);
	if (!tools->args[0])
		return (0);
	add_history(tools->args);
	if (scanner(tools->args, tools) == -1)
		return (0);
	if (expander(tools->slist, tools) == -1)
		return (0);
	if (parser(&tools) == -1)
		return (0);
	if (tools->rd)
	{
		tmp = tools->cmds->rd;
		tools->cmds->rd = tmp;
	}
	executor(tools);
	return (0);
}
