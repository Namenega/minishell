/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 18:53:24 by pyg               #+#    #+#             */
/*   Updated: 2021/09/28 14:24:13 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/msh.h"

void	is_quote(t_token *tok)
{
	char	quote;

	quote = tok->tmp[tok->pos];
	tok->pos++;
	while (tok->tmp[tok->pos] && tok->tmp[tok->pos] != quote)
		tok->pos++;
	tok->pos++;
}
