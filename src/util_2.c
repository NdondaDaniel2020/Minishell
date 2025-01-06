/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_realloc(void *ptr, size_t original_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
	{
		return (malloc(new_size));
	}
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
	{
		return (NULL);
	}
	if (original_size > new_size)
	{
		original_size = new_size;
	}
	ft_memmove(new_ptr, ptr, original_size);
	free(ptr);
	return (new_ptr);
}

int	len_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

int	list_builtins(char *command)
{
	if (ft_strncmp(command, "echo", 4) == 0 && ft_strlen(command) == 4)
		return (1);
	else if (ft_strncmp(command, "cd", 2) == 0 && ft_strlen(command) == 2)
		return (1);
	else if (ft_strncmp(command, "pwd", 3) == 0 && ft_strlen(command) == 3)
		return (1);
	else if (ft_strncmp(command, "export", 6) == 0 && ft_strlen(command) == 6)
		return (1);
	else if (ft_strncmp(command, "unset", 5) == 0 && ft_strlen(command) == 5)
		return (1);
	else if (ft_strncmp(command, "env", 3) == 0 && ft_strlen(command) == 3)
		return (1);
	else if (ft_strncmp(command, "exit", 4) == 0 && ft_strlen(command) == 4)
		return (1);
	return (0);
}

int	get_last_position(t_new_list *aux)
{
	int	i;

	i = 0;
	while (aux->content[i])
	{
		if (ft_strlen(aux->content[i]) == 0)
		{
			i++;
			continue ;
		}
		i++;
	}
	if (ft_strlen(aux->content[i - 1]) == 0)
		return (i - 2);
	return (i - 1);
}

bool	is_other_file(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str[len - 1] != '/' && ft_strchr(str, '/'))
	{
		while ((len - 1) >= 0 && str[len - 1] && str[len - 1] != '/')
		{
			if (!ft_isalpha(str[len - 1]) && str[len - 1] != '/')
				return (true);
			len--;
		}
	}
	return (false);
}
