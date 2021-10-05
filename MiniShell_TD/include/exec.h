/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:13:49 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/05 15:21:29 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <fcntl.h>
# include "utils.h"
# include "parser.h"
# include "minishell.h"
# include "error_messages.h"

/* TODO: all ERR in ine header */
// # define ERR_MALLOC		"Malloc error."

typedef struct s_io		t_io;
typedef struct s_exec	t_exec;
typedef struct s_tok	t_tok;
typedef struct s_ast	t_ast;
typedef struct s_msh	t_msh;

struct s_io
{
	int		fd;
	int		heredoc_fd;
	int		oflag;
	char	*filename;
	t_io	*next;
};

struct s_exec
{
	t_msh	*msh;
	char	*cmdpath;
	int		size;
	char	**tab;
	t_io	*io;
	char	**env;
};

typedef struct s_cmd
{
	t_msh	*msh;
	t_exec	*exec;
	t_io	*tail;
	int		i;
}				t_cmd;

/* ================================= Command =============================== */

/* FILE: src/exec/command1.c */

t_exec	*cmd_get(t_msh *msh, t_ast *ast);
void	cmd_add_word(t_cmd *cmd, t_ast *ast);
void	cmd_ast_traversal(t_msh *msh, t_cmd *cmd, t_ast *ast);
void	cmd_add_io(t_msh *msh, t_cmd *cmd, t_ast *ast);

/* FILE: src/exec/command2.c */

int		cmd_word_count(t_ast *ast);
void	cmd_free(t_exec *exec);
void	cmd_error(t_cmd *cmd, char *msg);
void	cmd_print(t_exec *exec);

/* FILE: src/exec/command3.c */

void	simple_redirection(t_msh *msh, t_exec *ex);
void	list_redirection(t_exec *exec, int entry_file);

/* FILE: src/exec/heredoc.c */

int		heredoc(t_msh *msh, t_ast *ast);

/* ================================= Builtins =============================== */

void	which_cmd(t_msh *msh, t_exec *exe);
int		msh_echo(t_msh *msh, t_exec *exec);
int		msh_cd(t_msh *msh, t_exec *exec);
int		msh_unset(t_msh *msh, t_exec *exe);
int		msh_pwd(t_msh *msh, t_exec *exe);
int		msh_env(t_msh *msh, t_exec *exe);
int		msh_export(t_exec *exec);

int		msh_export_var(t_msh *msh, char *exp);
void	exec_error(t_exec *exec, char *msg);

#endif
