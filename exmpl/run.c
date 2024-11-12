#include <stdio.h>
#include <stdlib.h>

typedef struct		s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	int				item;
}					t_btree;

t_btree	*remove_tree_trunk(t_btree *root, int item);
t_btree	*remove_tree_leaf(t_btree *root, int item);
t_btree	*remove_tree(t_btree *root, int item);

t_btree	*insert_into_btree(t_btree *root, int item);
int	search_btree(t_btree *root, int item);
void	show_btree(t_btree *root);
int	len_btree(t_btree *root);


// binary tree

t_btree	*insert_into_btree(t_btree *root, int item)
{
	if (root == NULL)
	{
		t_btree	*new;

		new = (t_btree *)malloc(sizeof(t_btree));
		new->item = item;
		new->left = NULL;
		new->right = NULL;
		return (new);
	}
	else
	{
		if (item < root->item)
			root->left = insert_into_btree(root->left, item);
		if (item > root->item)
			root->right = insert_into_btree(root->right, item);
		return (root);
	}
}

t_btree	*remove_tree_leaf(t_btree *root, int item)
{
	t_btree	*aux;

	if (root->left != NULL)
		aux = root->left;
	else
		aux = root->right;
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
	else
	{
		if (root->item == item)
		{
			if (!root->left && !root->right)
			{
				free(root);
				return (NULL);
			}
			else if (!root->left || !root->right)
				return (remove_tree_leaf(root, item));
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
	else
		return (-999);
}

void	show_btree(t_btree *root)
{
	if (root != NULL)
	{
		printf("%i ", root->item);
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
	int	len;

	len = len_btree(root);
	while (len > 0)
	{
		root = remove_tree(root, len);
		len = len_btree(root);
	}
	return (NULL);
}

int main(void)
{
	t_btree	*tree;

	tree = NULL;
	tree = insert_into_btree(tree, 0);
	tree = insert_into_btree(tree, 1);
	tree = insert_into_btree(tree, 2);
	tree = insert_into_btree(tree, 3);

	show_btree(tree);
	printf("\n");

	int i = 0, len = 0;
	len = len_btree(tree);
	while (i  < len)
	{
		tree = remove_tree(tree, i);
		i++;
	}
	show_btree(tree);

	
}