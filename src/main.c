/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:25:08 by apodader          #+#    #+#             */
/*   Updated: 2023/12/24 18:47:28 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;

	if (argc != 1)
	{
		printf("Error: No arguments accepted\n");
		return (0);
	}
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	g_status = 0;
	tools.reset = 0;
	tools.envp = ft_arrdup(envp);
	while (argv)
	{
		find_pwd(&tools);
		minishell(&tools);
		flush(&tools, 0);
	}
	return (0);
}
