/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstnew_util_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_lstnew_addback(t_new_list **lst, t_new_list *new)
{
	t_new_list	*aux;

	if (lst)
	{
		if (new)
		{
			if (*lst == NULL)
				*lst = new;
			else
			{
				aux = *lst;
				while (aux->next)
					aux = aux->next;
				aux->next = new;
			}
		}
	}
}

void    ft_lstnew_addfront(t_new_list **lst, t_new_list *new)
{
	if (lst)
	{
		if (*lst)
			new->next = *lst;
		*lst = new;
	}
}

t_new_list  *ft_lstnew_new(char **content)
{
	t_new_list	*new;

	new = (t_new_list *)malloc(sizeof(t_new_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

int     ft_lstnew_size(t_new_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
