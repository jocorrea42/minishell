/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:15:00 by apodader          #+#    #+#             */
/*   Updated: 2024/01/03 23:05:49 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"

extern int	g_status;

typedef enum s_error
{
	ENV,
	MALLOC,
	SYNTAX,
	FORK,
	PIPE_ERR,
	DUP,
	OPEN,
	CD,
	NO_DIR,
	OLDPWD
}	t_error;

typedef enum s_tokens
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS
}	t_tokens;

typedef struct s_redir
{
	char			*arg;
	t_tokens		tk;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_scanner
{
	char				*str;
	t_tokens			token;
	struct s_scanner	*next;
	struct s_scanner	*prev;
}	t_scanner;

typedef struct s_simple_cmd
{
	char				**arg;
	int					na;
	int					nr;
	t_redir				*rd;
	struct s_simple_cmd	*next;
	struct s_simple_cmd	*prev;
}	t_simple_cmd;

typedef struct s_tools
{
	char			*args;
	char			**paths;
	char			**envp;
	t_scanner		*slist;
	t_simple_cmd	*cmds;
	char			*pwd;
	char			*old_pwd;
	char			*home;
	pid_t			pid;
	int				rd;
	int				fd_in;
	int				fd_out;
	int				reset;
}	t_tools;

int			scanner(char *str, t_tools *tools);
int			is_space(char c);
int			s_quotes(char *str, int i, int j, int quotes);
t_scanner	*ft_lastlist(t_scanner *lst);
void		ft_clearlist(t_scanner *lst);
int			handle_quotes(t_scanner *lst, int i, int quotes, t_tools *tools);
int			safe_init(t_tools *tools, t_scanner *list, char *tmp[3], int ij[3]);
void		safe_qm_init(t_scanner *lst, int i, char *tmp[4], t_tools *tools);
int			parser(t_tools **tools);
int			parse_envp(t_tools *tools);
char		*find_path(char **envp);
int			find_pwd(t_tools *tools);
int			tools_init(t_tools *tools);
int			dollar_sign(t_scanner *lst, int i, int quotes, t_tools *tools);
int			dollar_len(char *str, int i);
void		handle_sigint(int sig);
int			check_heredoc(t_simple_cmd *cmd, t_tools *tools);
char		**ft_arrdup(char **arr);
int			minishell(t_tools *tools);
int			executor(t_tools *tools);
int			flush(t_tools *tools, int x);
void		free_cmd(t_simple_cmd *cmd);
t_redir		*redir_init(t_scanner *slist, t_tools *tools);
void		redir_driver(t_simple_cmd *cmd, t_tools *tools);
int			var_exists(char **envp, char *var);
void		change_var(t_tools *tools, char *new, int i);
void		add_var(t_tools *tools, char *new_var);
void		rm_var(t_tools *tools, int j);
int			pre_exec(t_tools *tools);
// builtins
void		ms_echo(t_simple_cmd *cmd, t_tools *tools);
int			ms_cd(t_tools *tools, t_simple_cmd *cmd);
void		ms_pwd(t_tools *tools);
int			ms_export(t_tools *tools, char **arg);
int			ms_unset(t_tools *tools, t_simple_cmd *cmd);
int			ms_env(t_tools *tools, int x);
int			ms_exit(t_tools *tools, t_simple_cmd *cmd);
// errors
void		ft_exit(t_error err, t_tools *tools);
int			ft_error(t_error err);
void		exec_err(char *cmd, int status, t_tools *tools);
int			quote_error(int quote);

#endif
