/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:32:26 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/27 10:43:23 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"

void	we_word_expansion(t_msh *msh)
{
	t_we	we;

	if (!msh->root)
		return ;
	we.msh = msh;
	we.curr = NULL;
	we.type = TYPE_CMD;
	we.old = NULL;
	we.buff = ft_new_vec(DFLT_VEC_SIZE);
	if (!we.buff)
		we_error(&we, ERR_MALLOC);
	we.ifs = utils_env_get_ifs(msh->env);
	if (!we.ifs)
		we_error(&we, ERR_MALLOC);
	we_cst_traversal(&we, msh->root);
	ft_free_vec(we.buff);
}

void	we_cst_traversal(t_we *we, t_cst *curr)
{
	t_cst	*right_branch;
	t_cst	*left_branch;

	we->curr = curr;
	left_branch = we->curr->left;
	right_branch = we->curr->right;
	if (we->curr->type == CST_IO_REDIR)
		we->type = TYPE_IO;
	if (we->curr->lex)
	{
		we->old = we->curr->lex;
		we->curr->lex = NULL;
		we_lexeme_formating(we);
		free(we->old);
		we->old = NULL;
	}
	if (left_branch)
		we_cst_traversal(we, left_branch);
	if (right_branch)
		we_cst_traversal(we, right_branch);
	we->type = TYPE_CMD;
}

void	we_lexeme_formating(t_we *we)
{
	char	*lex;
	int		state;

	lex = we->old;
	state = WE_ST_FREE;
	if (ft_check_vec(we->buff, lex))
		we_error(we, ERR_MALLOC);
	while (*lex)
	{
		if (*lex == '$' && state != WE_ST_SQUOTE)
			lex = we_param_expansion(we, lex, state);
		else if (*lex == '\'' && state == WE_ST_FREE)
			state = WE_ST_SQUOTE;
		else if (*lex == '\'' && state == WE_ST_SQUOTE)
			state = WE_ST_FREE;
		else if (*lex == '\"' && state == WE_ST_FREE)
			state = WE_ST_DQUOTE;
		else if (*lex == '\"' && state == WE_ST_DQUOTE)
			state = WE_ST_FREE;
		else
			*we->buff->ptr++ = *lex;
		lex++;
	}
	we_add_word(we, we->buff);
}

char	*we_param_expansion(t_we *we, char *lex, int state)
{
	char	*ptr;
	char	*param;

	ptr = utils_env_check_name(lex + 1);
	if (ptr)
	{
		param = utils_env_get_param(we->msh->env, lex + 1, ptr - lex - 1);
		lex = ptr - 1;
		if (param)
			we_param_substitution(we, param, state);
	}
	else if (*(lex + 1) == '?' )
	{
		ptr++;
		we_param_substitution(we, we->msh->ret, state);
	}
	else if (!(*(lex + 1) == '\"' || *(lex + 1) == '\''))
		*we->buff->ptr++ = *lex;
	return (lex);
}

void	we_param_substitution(t_we *we, char *param, int state)
{
	int		len;
	int		do_ifs;

	if (ft_check_vec(we->buff, param))
		we_error(we, ERR_MALLOC);
	do_ifs = (we->type == TYPE_CMD && state == WE_ST_FREE);
	len = ft_strlen(param);
	while (*param)
	{
		if (do_ifs && ft_strchr(we->ifs, *param))
		{
			if (*we->buff->str)
				we_add_word(we, we->buff);
			param++;
		}
		else
			*we->buff->ptr++ = *param++;
	}
}