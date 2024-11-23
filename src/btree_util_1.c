/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_util_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_btree	*insert_into_btree(t_btree *root, int item, char *content)
{
	t_btree	*new;

	if (root == NULL)
	{
		new = (t_btree *)malloc(sizeof(t_btree));
		new->content = split_2(content, ' ');
		new->item = item;
		new->left = NULL;
		new->right = NULL;
		free(content);
		return (new);
	}
	else
	{
		if (item < root->item)
			root->left = insert_into_btree(root->left, item, content);
		if (item > root->item)
			root->right = insert_into_btree(root->right, item, content);
		return (root);
	}
}

t_btree	*remove_tree_leaf(t_btree *root)
{
	t_btree	*aux;

	if (root->left != NULL)
		aux = root->left;
	else
		aux = root->right;
	if (root->content)
		free_matrix(root->content);
	free(root);
	return (aux);
}

t_btree	*remove_tree_trunk(t_btree *root, int item)
{
	t_btree	*aux;

	aux = root->left;
	while (aux->right != NULL)
		aux = aux->right;
	root->item = aux->item;
	aux->item = item;
	root->left = remove_tree(root->left, item);
	return (root);
}

t_btree	*remove_tree(t_btree *root, int item)
{
	if (root == NULL)
		return (NULL);
	if (root->item == item)
	{
		if (!root->left && !root->right)
		{
			if (root->content)
				free_matrix(root->content);
			free(root);
			return (NULL);
		}
		else if (!root->left || !root->right)
			return (remove_tree_leaf(root));
		else
			return (remove_tree_trunk(root, item));
	}
	else
	{
		if (root->item < item)
			root->left = remove_tree(root->left, item);
		else
			root->right = remove_tree(root->right, item);
		return (root);
	}
}
