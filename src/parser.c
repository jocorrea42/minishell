/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:41:30 by jocorrea          #+#    #+#             */
/*   Updated: 2024/01/03 22:46:50 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_simple_cmd	*new_cmd_node(t_tools **tools)
{
	t_simple_cmd	*node;
	t_simple_cmd	*tmp;

	node = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	if (!node)
		ft_exit(MALLOC, *tools);
	node->arg = NULL;
	node->rd = NULL;
	node->na = 0;
	node->nr = 0;
	node->next = NULL;
	node->prev = NULL;
	if ((*tools)->cmds == NULL)
		(*tools)->cmds = node;
	else
	{
		tmp = (*tools)->cmds;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = node;
		node->prev = tmp;
	}
	return (node);
}

int	arg_count(t_scanner *scanner, t_simple_cmd *cmd)
{
	int			arg;
	t_scanner	*tmp;

	arg = 0;
	tmp = scanner;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->token)
		{
			if (tmp->next && tmp->next->str)
			{
				cmd->nr += 2;
				tmp = tmp->next;
				arg++;
			}
			else
				return (-1);
		}
		tmp = tmp->next;
		arg++;
	}
	return (arg);
}

int	new_redir(t_scanner **tmp, t_simple_cmd **cmd, t_tools **tools)
{
	t_redir	*redir;
	t_redir	*iter;

	if ((*tmp)->next && (*tmp)->next->token == 0)
	{
		redir = redir_init(*tmp, *tools);
		if (!(*cmd)->rd)
		{
			(*cmd)->rd = redir;
			(*tools)->rd++;
		}
		else
		{
			iter = (*cmd)->rd;
			while (iter && iter->next)
				iter = iter->next;
			iter->next = redir;
		}
	}
	else
		return (ft_error(SYNTAX));
	return (0);
}

int	command_built(t_scanner **tmp, t_tools **tools)
{
	t_simple_cmd	*cmd;
	int				i;

	i = -1;
	cmd = new_cmd_node(tools);
	cmd->na = arg_count(*tmp, cmd);
	if (cmd->na < 0)
		return (-1);
	cmd->arg = (char **)malloc((cmd->na - cmd->nr + 1) * sizeof(char *));
	if (!cmd->arg)
		ft_exit(MALLOC, *tools);
	cmd->arg[cmd->na - cmd->nr] = NULL;
	while (*tmp && (*tmp)->token != PIPE)
	{
		if ((*tmp)->str)
			cmd->arg[++i] = (*tmp)->str;
		else
		{
			if (new_redir(tmp, &cmd, tools) == -1)
				return (-1);
			(*tmp) = (*tmp)->next;
		}
		(*tmp) = (*tmp)->next;
	}
	return (0);
}

int	parser(t_tools **tools)
{
	t_scanner	*tmp;

	tmp = (*tools)->slist;
	while (tmp)
	{
		if (tmp->token != PIPE)
		{
			if (command_built(&tmp, tools) == -1)
				return (-1);
		}
		else if (tmp->prev && tmp->token == PIPE
			&& tmp->next && tmp->next->token != PIPE)
			tmp = tmp->next;
		else
			return (ft_error(SYNTAX));
	}
	return (EXIT_SUCCESS);
}
