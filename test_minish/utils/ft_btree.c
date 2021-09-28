/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 15:13:12 by namenega          #+#    #+#             */
/*   Updated: 2021/09/28 12:00:06 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"
#include "../parser.h"

char	**cst_in_tab(t_cst *cst, char **tab, int i)
{
	tab[i] = cst->lexeme;
	if (cst->left && cst->left->type == CST_WORD)
		cst_in_tab(cst->left, tab, i + 1);
	if (cst->right && (cst->right->type == CST_WORD || cst->right->type == CST_CMD_LIST))
		cst_in_tab(cst->right, tab, i + 1);
	return (tab);
}

int	cst_search_type(t_cst *root, int data_ref, int (*cmpf)(int, int))
{
	if (!root || !data_ref)
		return (0);
	if (cmpf(data_ref, root->type) == 1)
		return (root->type);
	if (root->left)
		return (cst_search_type(root->left, data_ref, cmpf));
	if (root->right)
		return (cst_search_type(root->right, data_ref, cmpf));
	return (0);
}

static int	max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	btree_level_count(t_cst *root)
{
	int	i;

	i = 0;
	if (!root)
		return (0);
	if (root->left)
		i = max(i, btree_level_count(root->right));
	if (root->right)
		i = max(i, btree_level_count(root->right));
	return (i + 1);
}
