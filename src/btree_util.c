/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
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
		new->content = ft_split(content, ' ');
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




int	search_btree(t_btree *root, int item)
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

void	show_btree(t_btree *root)
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
