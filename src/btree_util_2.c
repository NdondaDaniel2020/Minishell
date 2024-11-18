/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_util_2c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_btree(t_btree *root, int item) /* apagar */
{
	if (root != NULL)
	{
		if (item == root->item)
			return (root->item);
		if (item < root->item)
			return search_btree(root->left, item);
		if (item > root->item)
			return search_btree(root->right, item);
	}
	return (-999);
}

void	show_btree(t_btree *root)  /* apagar */
{
	if (root != NULL)
	{
		int	i;

		i = 0;
		ft_printf("[%i]-", root->item);
		while (root->content[i])
		{
			ft_printf("[%s]", root->content[i]);
			i++;
		}
		ft_printf("\n");
		show_btree(root->left);
		show_btree(root->right);
	}
	return ;
}

int	len_btree(t_btree *root)
{
	if (root == NULL)
		return (0);
	else
		return (1 + len_btree(root->left) + len_btree(root->right));
}

t_btree	*remove_all_tree(t_btree *root)
{
	int	i;
	int	len;

	i = 0;
	len = len_btree(root);
	while (i < len)
	{
		root = remove_tree(root, i);
		i++;
	}
	return (root);
}
