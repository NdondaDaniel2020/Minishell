/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstnew_util_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstnew_free(char **matrix, t_new_list *removed)
{
	if (matrix)
		free_matrix(matrix);
	if (removed)
	{
		free(removed);
		removed = NULL;
	}
}

void	ft_lstnew_delfront(t_new_list **list)
{
	t_new_list	*removed;

	if (!list || !*list)
		return ;
	removed = *list;
	*list = removed->next;
	free_matrix(removed->content);
	free(removed);
	removed = NULL;
}

void	ft_lstnew_delback(t_new_list **list)
{
	t_new_list	*aux;
	t_new_list	*removed;

	if (!list || !*list)
		return ;
	if (!(*list)->next)
	{
		ft_lstnew_free((*list)->content, *list);
		*list = NULL;
		return ;
	}
	aux = *list;
	while (aux->next->next)
		aux = aux->next;
	if (aux->next)
	{
		removed = aux->next;
		aux->next = removed->next;
		ft_lstnew_free(removed->content, removed);
	}
}

/* remover mais tarde */
void	ft_show_lstnew(t_new_list *list)
{
	int	i;

	while (list)
	{
		if (!list->content)
		{
			list = list->next;
			continue ;
		}
		i = 0;
		while (list->content[i])
		{
			printf("[%d]: %s ", i, list->content[i]);
			i++;
		}
		printf("\n");
		list = list->next;
	}
}
