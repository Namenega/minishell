/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tderwedu <tderwedu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 12:29:08 by tderwedu          #+#    #+#             */
/*   Updated: 2021/09/02 12:16:36 by tderwedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
// # include "libft.h"
# include "../includes/libft/libft.h"


# define PIPE 10
# define GREAT 11
# define LESS 12
# define DGREAT 13
# define DLESS 14
# define WORD 15
# define IO_NUMBER 16

typedef struct	s_tok t_tok;

enum	e_separators
{
	CHR_BLANK = ' ',
	CHR_LESS = '<',
	CHR_DQUOTE = '\"',
	CHR_QOUTE = '\'',
	CHR_GREAT = '>',
	CHR_PIPE = '|'
};

struct	s_tok
{
	char	*lexeme;
	int		type;
	t_tok	*next;
};

typedef struct	s_lexer
{
	int		i;
	int		i_p;
	t_tok	*first;
	t_tok	*last;
	char	*line;
}				t_lexer;

t_tok*	lexer(char *line);
void	lexer_print_tokens(t_tok *token);

#endif