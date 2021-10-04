/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 09:56:00 by tderwedu          #+#    #+#             */
/*   Updated: 2021/10/04 19:45:38 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <fcntl.h>
# include "utils.h"
# include "parser.h"
# include "minishell.h"

/* TODO: all ERR in ine header */
# define ERR_MALLOC		"Malloc error."

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

/* FILE: src/exec/heredoc.c */

int		heredoc(t_msh *msh, t_ast *ast);

/* ================================= Builtins =============================== */

void	which_cmd(t_exec *exec, char **env, t_msh *msh);
void	msh_echo(t_msh *msh, t_exec *exec);
int		msh_cd(t_msh *msh, t_exec *exec);
void	msh_unset(char **env, t_exec *exec);
void	msh_pwd(char **env, t_msh *msh);
int		msh_env(t_msh *msh, char **argv, char **env);

#endif
